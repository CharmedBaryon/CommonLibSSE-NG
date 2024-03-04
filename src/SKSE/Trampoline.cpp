#include "SKSE/Trampoline.h"

#include "SKSE/Logger.h"

#include "REX/W32/KERNEL32.h"

// xbyak brings in <Windows.h>
#ifdef SKSE_SUPPORT_XBYAK
#	include <xbyak/xbyak.h>
#	undef max
#	undef MEM_COMMIT
#	undef MEM_FREE
#	undef MEM_RELEASE
#	undef MEM_RESERVE
#	undef PAGE_EXECUTE_READWRITE
#endif

namespace SKSE
{
	namespace detail
	{
		[[nodiscard]] constexpr std::size_t roundup(std::size_t a_number, std::size_t a_multiple) noexcept
		{
			if (a_multiple == 0)
				return 0;

			const auto remainder = a_number % a_multiple;
			return (remainder == 0) ? a_number : (a_number + a_multiple - remainder);
		}

		[[nodiscard]] constexpr std::size_t rounddown(std::size_t a_number, std::size_t a_multiple) noexcept
		{
			if (a_multiple == 0)
				return 0;

			const auto remainder = a_number % a_multiple;
			return (remainder == 0) ? a_number : (a_number - remainder);
		}
	}

	void Trampoline::create(std::size_t a_size, void* a_module)
	{
		if (a_size == 0) {
			stl::report_and_fail("cannot create a trampoline with a zero size"sv);
		}

		if (!a_module) {
			const auto text = REL::Module::get().segment(REL::Segment::textx);
			a_module = text.pointer<std::byte>() + text.size();
		}

		auto mem = do_create(a_size, reinterpret_cast<std::uintptr_t>(a_module));
		if (!mem) {
			stl::report_and_fail("failed to create trampoline"sv);
		}

		set_trampoline(mem, a_size, [](void* a_mem, std::size_t) {
			REX::W32::VirtualFree(a_mem, 0, REX::W32::MEM_RELEASE);
		});
	}

#ifdef SKSE_SUPPORT_XBYAK
	void* Trampoline::allocate(Xbyak::CodeGenerator& a_code)
	{
		auto result = do_allocate(a_code.getSize());
		log_stats();
		std::memcpy(result, a_code.getCode(), a_code.getSize());
		return result;
	}
#endif

	// https://stackoverflow.com/a/54732489
	void* Trampoline::do_create(std::size_t a_size, std::uintptr_t a_address)
	{
		constexpr std::size_t    gigabyte = static_cast<std::size_t>(1) << 30;
		constexpr std::size_t    minRange = gigabyte * 2;
		constexpr std::uintptr_t maxAddr = (std::numeric_limits<std::uintptr_t>::max)();

		REX::W32::SYSTEM_INFO si;
		REX::W32::GetSystemInfo(&si);
		const std::uint32_t granularity = si.allocationGranularity;

		std::uintptr_t       min = a_address >= minRange ? detail::roundup(a_address - minRange, granularity) : 0;
		const std::uintptr_t max = a_address < (maxAddr - minRange) ? detail::rounddown(a_address + minRange, granularity) : maxAddr;

		REX::W32::MEMORY_BASIC_INFORMATION mbi;
		do {
			if (!REX::W32::VirtualQuery(reinterpret_cast<void*>(min), std::addressof(mbi), sizeof(mbi))) {
				log::error("VirtualQuery failed with code: 0x{:08X}"sv, REX::W32::GetLastError());
				return nullptr;
			}

			const auto baseAddr = reinterpret_cast<std::uintptr_t>(mbi.baseAddress);
			min = baseAddr + mbi.regionSize;

			if (mbi.state == REX::W32::MEM_FREE) {
				const std::uintptr_t addr = detail::roundup(baseAddr, granularity);

				// if rounding didn't advance us into the next region and the region is the required size
				if (addr < min && (min - addr) >= a_size) {
					const auto mem = REX::W32::VirtualAlloc(
						reinterpret_cast<void*>(addr), a_size, REX::W32::MEM_COMMIT | REX::W32::MEM_RESERVE, REX::W32::PAGE_EXECUTE_READWRITE);
					if (mem) {
						return mem;
					}
					log::warn("VirtualAlloc failed with code: 0x{:08X}"sv, REX::W32::GetLastError());
				}
			}
		} while (min < max);

		return nullptr;
	}

	void* Trampoline::do_allocate(std::size_t a_size)
	{
		if (a_size > free_size()) {
			stl::report_and_fail("Failed to handle allocation request"sv);
		}

		auto mem = _data + _size;
		_size += a_size;

		return mem;
	}

	void Trampoline::write_5branch(std::uintptr_t a_src, std::uintptr_t a_dst, std::uint8_t a_opcode)
	{
#pragma pack(push, 1)
		struct SrcAssembly
		{
			// jmp/call [rip + imm32]
			std::uint8_t opcode;  // 0 - 0xE9/0xE8
			std::int32_t disp;    // 1
		};
		static_assert(offsetof(SrcAssembly, opcode) == 0x0);
		static_assert(offsetof(SrcAssembly, disp) == 0x1);
		static_assert(sizeof(SrcAssembly) == 0x5);

		// FF /4
		// JMP r/m64
		struct TrampolineAssembly
		{
			// jmp [rip]
			std::uint8_t  jmp;    // 0 - 0xFF
			std::uint8_t  modrm;  // 1 - 0x25
			std::int32_t  disp;   // 2 - 0x00000000
			std::uint64_t addr;   // 6 - [rip]
		};
		static_assert(offsetof(TrampolineAssembly, jmp) == 0x0);
		static_assert(offsetof(TrampolineAssembly, modrm) == 0x1);
		static_assert(offsetof(TrampolineAssembly, disp) == 0x2);
		static_assert(offsetof(TrampolineAssembly, addr) == 0x6);
		static_assert(sizeof(TrampolineAssembly) == 0xE);
#pragma pack(pop)

		TrampolineAssembly* mem = nullptr;
		if (const auto it = _5branches.find(a_dst); it != _5branches.end()) {
			mem = reinterpret_cast<TrampolineAssembly*>(it->second);
		} else {
			mem = allocate<TrampolineAssembly>();
			_5branches.emplace(a_dst, reinterpret_cast<std::byte*>(mem));
		}

		const auto disp =
			reinterpret_cast<const std::byte*>(mem) -
			reinterpret_cast<const std::byte*>(a_src + sizeof(SrcAssembly));
		if (!in_range(disp)) {  // the trampoline should already be in range, so this should never happen
			stl::report_and_fail("displacement is out of range"sv);
		}

		SrcAssembly assembly;
		assembly.opcode = a_opcode;
		assembly.disp = static_cast<std::int32_t>(disp);
		REL::safe_write(a_src, &assembly, sizeof(assembly));

		mem->jmp = static_cast<std::uint8_t>(0xFF);
		mem->modrm = static_cast<std::uint8_t>(0x25);
		mem->disp = static_cast<std::int32_t>(0);
		mem->addr = static_cast<std::uint64_t>(a_dst);
	}

	void Trampoline::write_6branch(std::uintptr_t a_src, std::uintptr_t a_dst, std::uint8_t a_modrm)
	{
#pragma pack(push, 1)
		struct Assembly
		{
			// jmp/call [rip + imm32]
			std::uint8_t opcode;  // 0 - 0xFF
			std::uint8_t modrm;   // 1 - 0x25/0x15
			std::int32_t disp;    // 2
		};
		static_assert(offsetof(Assembly, opcode) == 0x0);
		static_assert(offsetof(Assembly, modrm) == 0x1);
		static_assert(offsetof(Assembly, disp) == 0x2);
		static_assert(sizeof(Assembly) == 0x6);
#pragma pack(pop)

		std::uintptr_t* mem = nullptr;
		if (const auto it = _6branches.find(a_dst); it != _6branches.end()) {
			mem = reinterpret_cast<std::uintptr_t*>(it->second);
		} else {
			mem = allocate<std::uintptr_t>();
			_6branches.emplace(a_dst, reinterpret_cast<std::byte*>(mem));
		}

		const auto disp =
			reinterpret_cast<const std::byte*>(mem) -
			reinterpret_cast<const std::byte*>(a_src + sizeof(Assembly));
		if (!in_range(disp)) {  // the trampoline should already be in range, so this should never happen
			stl::report_and_fail("displacement is out of range"sv);
		}

		Assembly assembly;
		assembly.opcode = static_cast<std::uint8_t>(0xFF);
		assembly.modrm = a_modrm;
		assembly.disp = static_cast<std::int32_t>(disp);
		REL::safe_write(a_src, &assembly, sizeof(assembly));

		*mem = a_dst;
	}

	void Trampoline::log_stats() const
	{
		const auto pct = (static_cast<double>(_size) / static_cast<double>(_capacity)) * 100.0;
		log::debug("{} => {}B / {}B ({:05.2f}%)"sv, _name, _size, _capacity, pct);
	}

	Trampoline& GetTrampoline()
	{
		static Trampoline trampoline;
		return trampoline;
	}
}
