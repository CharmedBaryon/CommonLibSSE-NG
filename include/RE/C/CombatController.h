#pragma once

#include "RE/A/AITimer.h"
#include "RE/B/BSAtomic.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/C/CombatState.h"
#include "RE/N/NiSmartPointer.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class CombatAimController;
	class CombatAreaStandard;
	class CombatBehaviorController;
	class CombatBlackboard;
	class CombatGroup;
	class CombatInventory;
	class CombatTargetSelectorStandard;
	class CombatState;
	class TESCombatStyle;

	class CombatController
	{
	public:
		enum class COMBAT_STANCE : uint8_t
		{
			None,
			Sneak
		};

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                  \
	CombatAimController*                    currentAimController;   /* 68 */                  \
	CombatAimController*                    previousAimController;  /* 70 */                  \
	BSTArray<CombatAreaStandard*>           areas;                  /* 78 */                  \
	CombatAreaStandard*                     currentArea;            /* 90 */                  \
	BSTArray<CombatTargetSelectorStandard*> targetSelectors;        /* 98 */                  \
	CombatTargetSelectorStandard*           currentTargetSelector;  /* B0 */                  \
	CombatTargetSelectorStandard*           previousTargetSelector; /* B8 */                  \
	std::uint32_t                           handleCount;            /* C0 */                  \
	std::int32_t                            unkC4;                  /* C4 */                  \
	NiPointer<Actor>                        cachedAttacker;         /* C8 - attackerHandle */ \
	NiPointer<Actor>                        cachedTarget;           /* D0 - targetHandle */
            RUNTIME_DATA_CONTENT
		};

		// 629 and later
		struct AE_RUNTIME_DATA
		{
#define AE_RUNTIME_DATA_CONTENT \
	mutable BSSpinLock aimControllerLock; /* 68 */

			AE_RUNTIME_DATA_CONTENT
		};

		RUNTIME_DATA_ACCESSOR_VERSIONED(RUNTIME_DATA, SKSE::RUNTIME_SSE_1_6_629, 0x68, 0x70);
		AE_ONLY_POINTER_ACCESSOR_VERSIONED(AE_RUNTIME_DATA, GetAERuntimeData, SKSE::RUNTIME_SSE_1_6_629, 0x68);

		[[nodiscard]] bool IsFleeing() const
		{
			return state->isFleeing;
		}
		bool CheckCombatArea(Actor* atatcker) const;
		bool CheckStraightPath(NiPoint3& dst, float dist, float min_dist = -1.0f) const;

		// members
		CombatGroup*                   combatGroup;           // 00
		CombatState*                   state;                 // 08
		CombatInventory*               inventory;             // 10
		CombatBlackboard*              blackboard;            // 18
		CombatBehaviorController*      behaviorController;    // 20
		ActorHandle                    attackerHandle;        // 28
		ActorHandle                    targetHandle;          // 2C
		ActorHandle                    previousTargetHandle;  // 30
		COMBAT_STANCE                  stance;                // 34
		bool                           startedCombat;         // 35
		std::uint8_t                   unk36;                 // 36
		std::uint8_t                   unk37;                 // 37
		TESCombatStyle*                combatStyle;           // 38
		bool                           stoppedCombat;         // 40
		bool                           unk41;                 // 41 - isbeingMeleeAttacked?
		bool                           ignoringCombat;        // 42
		bool                           inactive;              // 43
		AITimer                        unk44;                 // 44
		float                          lowMovementDelta;      // 4C
		BSTArray<CombatAimController*> aimControllers;        // 50
#if defined(EXCLUSIVE_SKYRIM_AE)
		AE_RUNTIME_DATA_CONTENT;
#endif
		RUNTIME_DATA_CONTENT;
	};
#if defined(EXCLUSIVE_SKYRIM_AE)
	static_assert(sizeof(CombatController) == 0xE0);
#else
	static_assert(sizeof(CombatController) == 0xD8);
#endif
}

#undef RUNTIME_DATA_CONTENT
#undef AE_RUNTIME_DATA_CONTENT