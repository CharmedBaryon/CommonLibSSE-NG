#pragma once

#include "REX/W32/BASE.h"

namespace RE
{
	class BSTaskletGroupData
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSTaskletGroupData;
		inline static constexpr auto VTABLE = VTABLE_BSTaskletGroupData;

		virtual ~BSTaskletGroupData() = default;  // 00

		// add
		virtual void WaitForCompletion(bool a_spin) = 0;             // 01
		virtual void Cancel() = 0;                                   // 02
		virtual void WaitForCompletionTimeout(float a_seconds) = 0;  // 03
		virtual void Unk_04() { return; }                            // 04 - { return; }

		// members
		bool                       allComplete;          // 08 - initialized true; cleared while a task group is active
		std::uint8_t               pad09[7];             // 09
		REX::W32::HANDLE           completionSemaphore;  // 10
		REX::W32::CRITICAL_SECTION lock;                 // 18
		bool                       unk40;                // 40 - cleared on completion
		bool                       unk41;                // 41 - cleared by Cancel/CloseTaskGroupData
		bool                       cancelled;            // 42 - set by Cancel
		std::uint8_t               unk43;                // 43
		std::uint32_t              unk44;                // 44
		std::int32_t               totalTaskCount;       // 48
		std::int32_t               completedTaskCount;   // 4C
	};
	static_assert(sizeof(BSTaskletGroupData) == 0x50);

	class BSWin32TaskletGroupData : public BSTaskletGroupData
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSWin32TaskletGroupData;
		inline static constexpr auto VTABLE = VTABLE_BSWin32TaskletGroupData;
	};
	static_assert(sizeof(BSWin32TaskletGroupData) == 0x50);
}
