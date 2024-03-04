#pragma once

#if defined(SKSE_SUPPORT_XBYAK)
namespace Xbyak
{
	class CodeGenerator;
}
#endif

namespace SKSE
{
	class Trampoline
	{
	public:
		using deleter_type = std::function<void(void* a_mem, std::size_t a_size)>;

		Trampoline() = default;
		Trampoline(const Trampoline&) = delete;

		Trampoline(Trampoline&& a_rhs) noexcept { move_from(std::move(a_rhs)); }

		explicit Trampoline(std::string_view a_name) :
			_name(a_name)
		{}

		~Trampoline() { release(); }

		Trampoline& operator=(const Trampoline&) = delete;

		Trampoline& operator=(Trampoline&& a_rhs) noexcept
		{
			if (this != std::addressof(a_rhs)) {
				move_from(std::move(a_rhs));
			}
			return *this;
		}

		void create(std::size_t a_size) { return create(a_size, nullptr); }
		void create(std::size_t a_size, void* a_module);

		void set_trampoline(void* a_trampoline, std::size_t a_size, deleter_type a_deleter = {})
		{
			auto trampoline = static_cast<std::byte*>(a_trampoline);
			if (trampoline) {
				constexpr auto INT3 = static_cast<int>(0xCC);
				std::memset(trampoline, INT3, a_size);
			}

			release();

			_deleter = std::move(a_deleter);
			_data = trampoline;
			_capacity = a_size;
			_size = 0;

			log_stats();
		}

		[[nodiscard]] void* allocate(std::size_t a_size)
		{
			auto result = do_allocate(a_size);
			log_stats();
			return result;
		}

#ifdef SKSE_SUPPORT_XBYAK
		[[nodiscard]] void* allocate(Xbyak::CodeGenerator& a_code);
#endif

		template <class T>
		[[nodiscard]] T* allocate()
		{
			return static_cast<T*>(allocate(sizeof(T)));
		}

		[[nodiscard]] constexpr std::size_t empty() const noexcept { return _capacity == 0; }
		[[nodiscard]] constexpr std::size_t capacity() const noexcept { return _capacity; }
		[[nodiscard]] constexpr std::size_t allocated_size() const noexcept { return _size; }
		[[nodiscard]] constexpr std::size_t free_size() const noexcept { return _capacity - _size; }

		template <std::size_t N>
		std::uintptr_t write_branch(std::uintptr_t a_src, std::uintptr_t a_dst)
		{
			std::uint8_t data = 0;
			if constexpr (N == 5) {
				// E9 cd
				// JMP rel32
				data = 0xE9;
			} else if constexpr (N == 6) {
				// FF /4
				// JMP r/m64
				data = 0x25;
			} else {
				static_assert(false && N, "invalid branch size");
			}

			return write_branch<N>(a_src, a_dst, data);
		}

		template <std::size_t N, class F>
		std::uintptr_t write_branch(std::uintptr_t a_src, F a_dst)
		{
			return write_branch<N>(a_src, stl::unrestricted_cast<std::uintptr_t>(a_dst));
		}

		template <std::size_t N>
		std::uintptr_t write_call(std::uintptr_t a_src, std::uintptr_t a_dst)
		{
			std::uint8_t data = 0;
			if constexpr (N == 5) {
				// E8 cd
				// CALL rel32
				data = 0xE8;
			} else if constexpr (N == 6) {
				// FF /2
				// CALL r/m64
				data = 0x15;
			} else {
				static_assert(false && N, "invalid call size");
			}

			return write_branch<N>(a_src, a_dst, data);
		}

		template <std::size_t N, class F>
		std::uintptr_t write_call(std::uintptr_t a_src, F a_dst)
		{
			return write_call<N>(a_src, stl::unrestricted_cast<std::uintptr_t>(a_dst));
		}

	private:
		[[nodiscard]] void* do_create(std::size_t a_size, std::uintptr_t a_address);
		[[nodiscard]] void* do_allocate(std::size_t a_size);

		void write_5branch(std::uintptr_t a_src, std::uintptr_t a_dst, std::uint8_t a_opcode);
		void write_6branch(std::uintptr_t a_src, std::uintptr_t a_dst, std::uint8_t a_modrm);

		template <std::size_t N>
		[[nodiscard]] std::uintptr_t write_branch(std::uintptr_t a_src, std::uintptr_t a_dst, std::uint8_t a_data)
		{
			const auto disp = reinterpret_cast<std::int32_t*>(a_src + N - 4);
			const auto nextOp = a_src + N;
			const auto func = nextOp + *disp;

			if constexpr (N == 5) {
				write_5branch(a_src, a_dst, a_data);
			} else if constexpr (N == 6) {
				write_6branch(a_src, a_dst, a_data);
			} else {
				static_assert(false && N, "invalid branch size");
			}

			return func;
		}

		void move_from(Trampoline&& a_rhs)
		{
			_5branches = std::move(a_rhs._5branches);
			_6branches = std::move(a_rhs._6branches);
			_name = std::move(a_rhs._name);

			_deleter = std::move(a_rhs._deleter);

			_data = a_rhs._data;
			a_rhs._data = nullptr;

			_capacity = a_rhs._capacity;
			a_rhs._capacity = 0;

			_size = a_rhs._size;
			a_rhs._size = 0;
		}

		void log_stats() const;

		[[nodiscard]] bool in_range(std::ptrdiff_t a_disp) const
		{
			constexpr auto min = (std::numeric_limits<std::int32_t>::min)();
			constexpr auto max = (std::numeric_limits<std::int32_t>::max)();

			return min <= a_disp && a_disp <= max;
		}

		void release()
		{
			if (_data && _deleter) {
				_deleter(_data, _capacity);
			}

			_5branches.clear();
			_6branches.clear();
			_data = nullptr;
			_capacity = 0;
			_size = 0;
		}

		std::map<std::uintptr_t, std::byte*> _5branches;
		std::map<std::uintptr_t, std::byte*> _6branches;
		std::string                          _name{ "Default Trampoline"sv };
		deleter_type                         _deleter;
		std::byte*                           _data{ nullptr };
		std::size_t                          _capacity{ 0 };
		std::size_t                          _size{ 0 };
	};

	Trampoline& GetTrampoline();
}
