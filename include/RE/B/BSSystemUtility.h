#pragma once

#include "RE/B/BSTEvent.h"
#include "REL/Relocation.h"
#include "REL/RuntimeDataAccessors.h"
#include "SKSE/Version.h"

namespace RE
{
	class BSSystemEvent;
	struct BSGamepadEvent;

	class BSSystemUtility :
		public BSTEventSink<BSGamepadEvent>,  // 000
		public BSTEventSource<BSSystemEvent>  // 008
	{
	public:
		virtual ~BSSystemUtility();  // 00

		// override (BSTEventSink<BSGamepadEvent>)
		BSEventNotifyControl ProcessEvent(const BSGamepadEvent* a_event, BSTEventSource<BSGamepadEvent>* a_eventSource) override;  // 01

#ifdef ENABLE_SKYRIM_AE
		bool Unk_02AE(void* a_result)
		{
			if (!REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
				return false;
			}
			REL::RelocateVirtual<void(BSSystemUtility*, void*)>(0x02, 0x02, this, a_result);
			return true;
		}
#endif

#ifndef ENABLE_SKYRIM_AE
		virtual void GetAuthenticationInfo(char*& a_userAuthID, std::uint64_t& a_size);  // 02
		virtual void Unk_03(void);                                                       // 03
		virtual void DoInitialize();                                                     // 04
		virtual void Unk_05(void);                                                       // 05
		virtual void DoUpdate();                                                         // 06
		virtual void Unk_07(void);                                                       // 07
		virtual void DoGetUserName(char* a_buffer, std::uint64_t a_size);                // 08
		virtual void Unk_09(void);                                                       // 09
		virtual void Unk_0A(void);                                                       // 0A
		virtual void Unk_0B(void);                                                       // 0B
		virtual void Unk_0C(void);                                                       // 0C
		virtual void DoGetComputerName(char* a_buffer, std::uint64_t a_size);            // 0D
		virtual void Unk_0E(void);                                                       // 0E
		virtual void Unk_0F(void);                                                       // 0F
		virtual void DoAuthenticateUser();                                               // 10
		virtual void Unk_11(void);                                                       // 11
		virtual bool Unk_12();                                                           // 12 - added in 1.6.1130
#else
		static constexpr std::size_t kAE1799AddedVFuncCount = 1;  // matches Unk_02AE above
		void                         GetAuthenticationInfo(char*& a_userAuthID, std::uint64_t& a_size)
		{
			REL::RelocateVirtual<void(BSSystemUtility*, char*&, std::uint64_t&)>(REL::VersionShift(0x02, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), REL::VersionShift(0x02, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), this, a_userAuthID, a_size);
		}
		void Unk_03(void) { REL::RelocateVirtual<void(BSSystemUtility*)>(REL::VersionShift(0x03, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), REL::VersionShift(0x03, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), this); }
		void DoInitialize() { REL::RelocateVirtual<void(BSSystemUtility*)>(REL::VersionShift(0x04, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), REL::VersionShift(0x04, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), this); }
		void Unk_05(void) { REL::RelocateVirtual<void(BSSystemUtility*)>(REL::VersionShift(0x05, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), REL::VersionShift(0x05, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), this); }
		void DoUpdate() { REL::RelocateVirtual<void(BSSystemUtility*)>(REL::VersionShift(0x06, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), REL::VersionShift(0x06, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), this); }
		void Unk_07(void) { REL::RelocateVirtual<void(BSSystemUtility*)>(REL::VersionShift(0x07, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), REL::VersionShift(0x07, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), this); }
		void DoGetUserName(char* a_buffer, std::uint64_t a_size)
		{
			REL::RelocateVirtual<void(BSSystemUtility*, char*, std::uint64_t)>(REL::VersionShift(0x08, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), REL::VersionShift(0x08, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), this, a_buffer, a_size);
		}
		void Unk_09(void) { REL::RelocateVirtual<void(BSSystemUtility*)>(REL::VersionShift(0x09, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), REL::VersionShift(0x09, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), this); }
		void Unk_0A(void) { REL::RelocateVirtual<void(BSSystemUtility*)>(REL::VersionShift(0x0A, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), REL::VersionShift(0x0A, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), this); }
		void Unk_0B(void) { REL::RelocateVirtual<void(BSSystemUtility*)>(REL::VersionShift(0x0B, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), REL::VersionShift(0x0B, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), this); }
		void Unk_0C(void) { REL::RelocateVirtual<void(BSSystemUtility*)>(REL::VersionShift(0x0C, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), REL::VersionShift(0x0C, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), this); }
		void DoGetComputerName(char* a_buffer, std::uint64_t a_size)
		{
			REL::RelocateVirtual<void(BSSystemUtility*, char*, std::uint64_t)>(REL::VersionShift(0x0D, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), REL::VersionShift(0x0D, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), this, a_buffer, a_size);
		}
		void Unk_0E(void) { REL::RelocateVirtual<void(BSSystemUtility*)>(REL::VersionShift(0x0E, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), REL::VersionShift(0x0E, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), this); }
		void Unk_0F(void) { REL::RelocateVirtual<void(BSSystemUtility*)>(REL::VersionShift(0x0F, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), REL::VersionShift(0x0F, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), this); }
		void DoAuthenticateUser() { REL::RelocateVirtual<void(BSSystemUtility*)>(REL::VersionShift(0x10, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), REL::VersionShift(0x10, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), this); }
		void Unk_11(void) { REL::RelocateVirtual<void(BSSystemUtility*)>(REL::VersionShift(0x11, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), REL::VersionShift(0x11, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), this); }
		bool Unk_12() { return REL::RelocateVirtual<bool(BSSystemUtility*)>(REL::VersionShift(0x12, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), REL::VersionShift(0x12, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), this); }  // added in 1.6.1130
#endif

		// members
		std::uint64_t unk060[24];  // 060
		std::uint8_t  unk120;      // 120 - added in 1.6.1130
		std::uint8_t  unk121;      // 121 - added in 1.6.1130
		std::uint16_t pad122;      // 122
		std::uint32_t pad124;      // 124
	};
	static_assert(sizeof(BSSystemUtility) == 0x128);
}
