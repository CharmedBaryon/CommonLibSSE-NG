#pragma once

#include "RE/I/IAnimationSetCallbackFunctor.h"
#include "RE/I/IMovementDirectControl.h"
#include "RE/I/IMovementMessageInterface.h"
#include "RE/I/IMovementMotionDrivenControl.h"
#include "RE/I/IMovementPlannerDirectControl.h"
#include "RE/I/IMovementSelectIdle.h"
#include "RE/M/MovementControllerAI.h"

namespace RE
{
	class MovementMessage;

	class MovementControllerNPC :
		public MovementControllerAI,           // 000
		public IMovementMessageInterface,      // 120
		public IMovementMotionDrivenControl,   // 128
		public IMovementSelectIdle,            // 130
		public IMovementDirectControl,         // 138
		public IMovementPlannerDirectControl,  // 140
		public IAnimationSetCallbackFunctor    // 148
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementControllerNPC;
		inline static constexpr auto VTABLE = VTABLE_MovementControllerNPC;

		~MovementControllerNPC() override;  // 00

		// add
		virtual void Unk_0A(void);         // 0A
		virtual void Unk_0B(void);         // 0B
		virtual void SetAIDriven();        // 0C
		virtual void SetControlsDriven();  // 0D
		virtual bool GetAIDriven();        // 0E - { return controlsDriven == 0; }
		virtual bool GetControlsDriven();  // 0F - { return controlsDriven; }
		virtual void Unk_10(void);         // 10
		virtual void Unk_11(void);         // 11
		virtual void Unk_12(void);         // 12
		virtual void Unk_13(void);         // 13
		virtual void Unk_14(void);         // 14

		// members
		BSSpinLock                 unk150;            // 150
		BSTArray<MovementMessage*> movementMessages;  // 158
		BSTArray<void*>            unk170;            // 170
		BSTArray<void*>            unk188;            // 188
		BSSpinLock                 unk1A0;            // 1A0
		std::uint64_t              unk1A8;            // 1A8
		std::uint64_t              unk1B0;            // 1B0
		Actor*                     actor;             // 1B8
		std::uint32_t              unk1C0;            // 1C0
		bool                       unk1C4;            // 1C4
		bool                       controlsDriven;    // 1C5
		bool                       unk1C6;            // 1C6
		bool                       unk1C7;            // 1C7
		bool                       unk1C8;            // 1C8
		bool                       unk1C9;            // 1C9
		bool                       unk1CA;            // 1CA
		bool                       unk1CB;            // 1CB
		std::uint32_t              unk1CC;            // 1CC
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(MovementControllerNPC) == 0x1D0);
#endif
}
