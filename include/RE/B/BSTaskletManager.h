#pragma once

#include "REL/Relocation.h"
#include "REX/W32/BASE.h"

namespace RE
{
	class BSTaskletData;
	class BSTaskletGroup;
	class BSTaskletGroupData;

	class BSTaskletManager
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSTaskletManager;
		inline static constexpr auto VTABLE = VTABLE_BSTaskletManager;

		virtual ~BSTaskletManager() = default;  // 00
		virtual void Unk_01() { return; }       // 01 - { return; } (no confirmed caller)

		// add
		virtual void ShutdownAllTasks() = 0;                                                                      // 02
		virtual bool IsWorkerThread(std::uint32_t a_threadID) = 0;                                                // 03
		virtual bool CreateTaskGroupData(BSTaskletGroupData** a_taskGroupData) = 0;                               // 04
		virtual bool BeginTaskGroup(BSTaskletGroupData* a_taskGroupData) = 0;                                     // 05
		virtual bool AddTasklet(BSTaskletGroupData* a_taskGroupData, BSTaskletData* a_tasklet, bool a_flag) = 0;  // 06
		virtual bool CloseTaskGroupData(BSTaskletGroupData* a_taskGroupData) = 0;                                 // 07
		virtual void ReleaseTaskletData(BSTaskletData* a_tasklet) = 0;                                            // 08
		virtual void Unk_09() { return; }                                                                         // 09 - { return; } (notification hook; unoverridden in SE/AE/VR)

		bool CreateTaskGroup(BSTaskletGroup& a_taskGroup)
		{
			using func_t = decltype(&BSTaskletManager::CreateTaskGroup);
			static REL::Relocation<func_t> func{ RELOCATION_ID(68207, 69558) };
			return func(this, a_taskGroup);
		}

		// members
		bool             canCreateTaskGroup;  // 08 - true once >=1 worker thread started successfully
		bool             started;             // 09 - set by SignalInstanceAvailable
		std::uint8_t     pad0A[6];            // 0A
		REX::W32::HANDLE instanceSemaphore;   // 10 - binary semaphore (max 1)
		std::int32_t     instanceCount;       // 18 - incremented by SignalInstanceAvailable, decremented by the monitor thread
		std::uint32_t    unk1C;               // 1C - always 1 at construction; no reader found
	};
	static_assert(sizeof(BSTaskletManager) == 0x20);
}
