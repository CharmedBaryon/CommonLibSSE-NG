#pragma once

#include "RE/B/BSTaskletManager.h"
#include "REX/W32/BASE.h"

namespace RE
{
	class BSWin32TaskletManager : public BSTaskletManager
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSWin32TaskletManager;
		inline static constexpr auto VTABLE = VTABLE_BSWin32TaskletManager;

		[[nodiscard]] static BSWin32TaskletManager* GetSingleton()
		{
			using func_t = decltype(&BSWin32TaskletManager::GetSingleton);
			static REL::Relocation<func_t> func{ RELOCATION_ID(68203, 69554) };
			return func();
		}

		// members
		REX::W32::HANDLE           monitorThread;             // 20
		std::uint32_t              desiredWorkerThreadCount;  // 28 - clamped <=6; the real singleton always requests 6
		std::uint32_t              startedWorkerThreadCount;  // 2C
		REX::W32::HANDLE           workerThreads[6];          // 30
		std::uint32_t              workerThreadIDs[6];        // 60
		bool                       shutdownRequested;         // 78
		std::uint8_t               pad79[7];                  // 79
		REX::W32::CRITICAL_SECTION queueLock;                 // 80
		void*                      queueHeads[64];            // A8 - one linked-list head per priority bucket
		void**                     queueTails[64];            // 2A8 - self-referential tail-insertion pointers
		REX::W32::HANDLE           taskletSemaphore;          // 4A8 - counting semaphore (max INT32_MAX); signalled per enqueued tasklet
		std::uint8_t               unk4B0[0x600];             // 4B0 - unidentified; untouched by ctor/dtor or any confirmed method
	};
	static_assert(sizeof(BSWin32TaskletManager) == 0xAB0);
}
