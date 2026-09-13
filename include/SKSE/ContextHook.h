// Based on hooking code by meh321 from Intellightent.
// https://www.nexusmods.com/skyrimspecialedition/mods/172423
#pragma once

#include "REL/Relocation.h"
#include "SKSE/Logger.h"
#include "SKSE/Trampoline.h"
#include <vector>

#if defined(SKSE_SUPPORT_XBYAK)
#	include <xbyak/xbyak.h>

namespace SKSE::stl
{
	namespace detail
	{
		/// Called from the generated context-capture stub.
		/// Restores registers saved above the CONTEXT on the stack, invokes the
		/// user delegate with the captured register state, then calls
		/// RtlRestoreContext to resume execution at resumeAddr.
		inline void context_hook_execute(
			CONTEXT* ctx,
			void (*func)(CONTEXT&),
			void* internalResume,
			void* publicResume)
		{
			// The stub pushes (in order, lowest address last) onto the stack before
			// allocating space for CONTEXT:
			//   RFLAGS, RCX, RAX, RSP (original), then an alignment sentinel.
			// These live above (at higher addresses than) the CONTEXT on the stack.
			auto* after = reinterpret_cast<DWORD64*>(reinterpret_cast<std::uint8_t*>(ctx) + sizeof(CONTEXT));
			if (after[0] == 0)
				after += 1;  // type-0 sentinel: stack was already 16-byte aligned
			else
				after += 2;  // type-1 + 0 sentinels: alignment pad was inserted
			ctx->EFlags = static_cast<DWORD>(after[0]);
			ctx->Rcx = after[1];
			ctx->Rax = after[2];
			ctx->Rsp = after[3];
			ctx->Rip = reinterpret_cast<DWORD64>(publicResume);

			struct HookState
			{
				void* internalResume;
				void* publicResume;
			};
			static thread_local std::vector<HookState> hookStack;
			const bool                                 needsRemap = internalResume != publicResume;
			if (needsRemap) {
				hookStack.push_back({ internalResume, publicResume });
			}

			func(*ctx);

			if (needsRemap) {
				const auto state = hookStack.back();
				hookStack.pop_back();

				if (ctx->Rip == reinterpret_cast<DWORD64>(state.publicResume)) {
					ctx->Rip = reinterpret_cast<DWORD64>(state.internalResume);
				}
			}
			RtlRestoreContext(ctx, nullptr);
		}
	}

	/// Install a full-context hook at a_patchAddr.
	///
	/// Replaces a_patchSize bytes at a_patchAddr with a JMP5 to a generated
	/// trampoline stub that:
	///   1. Captures all registers via RtlCaptureContext.
	///   2. Calls a_func(CONTEXT&), which may modify any register value.
	///   3. Restores all registers via RtlRestoreContext and resumes execution
	///      at a_patchAddr + a_patchSize.
	///
	/// a_patchSize must be >= 5; bytes beyond the first 5 are NOP-filled.
	///
	/// a_includeSize controls whether original bytes run alongside the stub:
	///   > 0  copies the first a_includeSize bytes of the original instruction
	///         BEFORE the stub (original prologue is preserved).
	///   < 0  copies the first |a_includeSize| bytes AFTER the stub, followed
	///         by an absolute JMP back to resumeAddr (original epilogue preserved);
	///         the delegate sees Rip == resumeAddr and unchanged Rip runs the
	///         copied bytes before resuming.
	///   = 0  original bytes are fully replaced.
	///
	/// Requires SKSE_SUPPORT_XBYAK. Uses SKSE::GetTrampoline() for stub allocation.
	/// Returns true on success, false if patchSize < 5 or the trampoline is full.
	[[nodiscard]] inline bool install_context_hook(
		std::uintptr_t a_patchAddr,
		int            a_patchSize,
		void (*a_func)(CONTEXT&),
		int a_includeSize = 0)
	{
		if (a_patchSize < 5) {
			SKSE::log::error("install_context_hook: patchSize {} < 5", a_patchSize);
			return false;
		}

		void* resumeAddr = reinterpret_cast<void*>(a_patchAddr + a_patchSize);

		std::vector<std::uint8_t> includedBytes;
		if (a_includeSize != 0) {
			includedBytes.resize(static_cast<std::size_t>(std::abs(a_includeSize)));
			std::memcpy(includedBytes.data(), reinterpret_cast<void*>(a_patchAddr), includedBytes.size());
		}

		static const auto s_rtlCapture = reinterpret_cast<std::uint64_t>(
			GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "RtlCaptureContext"));

		// The context-capture stub:
		//   1. Saves RSP/RAX/RCX/RFLAGS on the stack.
		//   2. Pushes a sentinel to record whether alignment padding was added.
		//   3. 16-byte aligns the stack, padding with an extra qword if needed.
		//   4. Allocates sizeof(CONTEXT) on the stack and calls RtlCaptureContext.
		//   5. Calls detail::context_hook_execute(CONTEXT*, a_func, innerResume, resumeAddr),
		//      which patches CONTEXT from the saved values and calls
		//      RtlRestoreContext to resume execution — it does not return.
		const auto buildStub = [&](Xbyak::CodeGenerator& gen, void* a_internalResume, void* a_publicResume) {
			using namespace Xbyak::util;
			Xbyak::Label aligned;
			gen.push(rsp);  // save original RSP
			gen.push(rax);  // scratch
			gen.push(rcx);  // arg1 scratch
			gen.pushfq();   // flags
			gen.xor_(rax, rax);
			gen.push(rax);  // type-0 sentinel (== 0)
			gen.mov(rax, rsp);
			gen.and_(rax, -16);  // clear low 4 bits
			gen.cmp(rax, rsp);
			gen.je(aligned, Xbyak::CodeGenerator::T_SHORT);  // skip pad if already aligned
			gen.mov(rax, 1);
			gen.push(rax);  // type-1 sentinel (!= 0)
			gen.L(aligned);
			gen.sub(rsp, sizeof(CONTEXT));  // allocate CONTEXT (0x4D0)
			gen.mov(rcx, rsp);              // arg1 = CONTEXT*
			gen.mov(rax, s_rtlCapture);
			gen.call(rax);
			gen.mov(rcx, rsp);   // restore arg1 after call
			gen.sub(rsp, 0x20);  // shadow space
			gen.mov(rdx, reinterpret_cast<std::uint64_t>(a_func));
			gen.mov(r8, reinterpret_cast<std::uint64_t>(a_internalResume));
			gen.mov(r9, reinterpret_cast<std::uint64_t>(a_publicResume));
			gen.mov(rax, reinterpret_cast<std::uint64_t>(&detail::context_hook_execute));
			gen.call(rax);
			gen.ready();
		};

		// Pass 1: measure the stub's byte size.
		// Use a sentinel address with bits above bit 32 set so the movabs
		// encoding for the resumePtr slot is identical in both passes.
		std::size_t stubSize;
		{
			Xbyak::CodeGenerator sizer;
			const auto           sentinel = reinterpret_cast<void*>(static_cast<uintptr_t>(0xDEADBEEFDEADBEEFull));
			buildStub(sizer, sentinel, sentinel);
			stubSize = sizer.getSize();
		}

		// Cave layout:
		//   a_includeSize > 0: [includedBytes | stub]
		//   a_includeSize < 0: [stub | includedBytes | abs-jmp(14)]
		//   a_includeSize = 0: [stub]
		constexpr int absJmpSize = 14;
		const int     totalSize =
			static_cast<int>(stubSize) + std::abs(a_includeSize) + (a_includeSize < 0 ? absJmpSize : 0);

		auto& trampoline = SKSE::GetTrampoline();
		auto* cave = static_cast<std::uint8_t*>(trampoline.allocate(totalSize));
		if (!cave) {
			SKSE::log::error("install_context_hook: trampoline out of space");
			return false;
		}

		// When a_includeSize < 0 the stub resumes into the copied original bytes
		// (cave + stubSize); otherwise execution resumes after the patched bytes.
		void* innerResume = (a_includeSize < 0) ? static_cast<void*>(cave + stubSize) : resumeAddr;
		void* publicResume = resumeAddr;

		// Pass 2: emit the stub directly into the cave.
		auto*                stubDst = cave + (a_includeSize > 0 ? static_cast<std::size_t>(a_includeSize) : 0u);
		Xbyak::CodeGenerator gen(stubSize + 16, stubDst);
		buildStub(gen, innerResume, publicResume);

		// Write included bytes preceding the stub (a_includeSize > 0 case).
		if (a_includeSize > 0)
			std::memcpy(cave, includedBytes.data(), a_includeSize);

		// Write included bytes + absolute JMP following the stub (a_includeSize < 0 case).
		if (a_includeSize < 0) {
			auto* after = cave + stubSize;
			std::memcpy(after, includedBytes.data(), -a_includeSize);
			after += -a_includeSize;
			// FF 25 00000000 <abs64>: JMP [RIP+0], target follows immediately.
			std::uint8_t jmp[absJmpSize] = { 0xFF, 0x25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			const auto   resume64 = reinterpret_cast<std::uint64_t>(resumeAddr);
			std::memcpy(jmp + 6, &resume64, 8);
			std::memcpy(after, jmp, absJmpSize);
		}

		trampoline.write_branch<5>(a_patchAddr, reinterpret_cast<std::uintptr_t>(cave));
		if (a_patchSize > 5) {
			std::vector<std::uint8_t> nops(a_patchSize - 5, 0x90);
			REL::safe_write(a_patchAddr + 5, nops.data(), nops.size());
		}

		return true;
	}
}

#endif  // SKSE_SUPPORT_XBYAK
