#pragma once

#include "REX/W32/BASE.h"

namespace REX::W32
{
	struct EXCEPTION_REGISTRATION_RECORD;
	struct PEB_LDR_DATA;
	struct RTL_USER_PROCESS_PARAMETERS;
	struct UNICODE_STRING;

	using PS_POST_PROCESS_INIT_ROUTINE = void (*)();

	struct LIST_ENTRY
	{
		struct LIST_ENTRY* fLink;
		struct LIST_ENTRY* bLink;
	};

	struct NT_TIB
	{
		EXCEPTION_REGISTRATION_RECORD* exceptionList;
		void*                          stackBase;
		void*                          stackLimit;
		void*                          subSystemTib;
		union
		{
			void*         fiberData;
			std::uint32_t version;
		};
		void*          arbitraryUserPointer;
		struct NT_TIB* self;
	};

	struct PEB
	{
		std::byte                    reserved1[2];
		std::byte                    beingDebugged;
		std::byte                    reserved2[1];
		void*                        reserved3[2];
		PEB_LDR_DATA*                ldr;
		RTL_USER_PROCESS_PARAMETERS* processParameters;
		void*                        reserved4[3];
		void*                        atlThunkSListPtr;
		void*                        reserved5;
		std::uint32_t                reserved6;
		void*                        reserved7;
		std::uint32_t                reserved8;
		std::uint32_t                atlThunkSListPtr32;
		void*                        reserved9[45];
		std::byte                    reserved10[96];
		PS_POST_PROCESS_INIT_ROUTINE postProcessInitRoutine;
		std::byte                    reserved11[128];
		void*                        reserved12[1];
		std::uint32_t                sessionID;
	};

	struct PEB_LDR_DATA
	{
		std::byte  reserved1[8];
		void*      reserved2[3];
		LIST_ENTRY inMemoryOrderModuleList;
	};

	struct RTL_USER_PROCESS_PARAMETERS
	{
		std::byte      reserved1[16];
		void*          reserved2[10];
		UNICODE_STRING imagePathName;
		UNICODE_STRING commandLine;
	};

	struct TEB
	{
		void*     reserved1[11];
		void*     threadLocalStoragePointer;
		PEB*      processEnvironmentBlock;
		void*     reserved2[399];
		std::byte reserved3[1952];
		void*     tlsSlots[64];
		std::byte reserved4[8];
		void*     reserved5[26];
		void*     reservedForOle;
		void*     reserved6[4];
		void*     tlsExpansionSlots;
	};
}

namespace REX::W32
{
	TEB* NtCurrentTeb() noexcept;
}
