#pragma once

#include "RE/A/AITimer.h"
#include "RE/B/BSAtomic.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/C/CombatState.h"
#include "RE/N/NiSmartPointer.h"

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

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMemberIfNewer<RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x68, 0x70);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMemberIfNewer<RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x68, 0x70);
		}

		[[nodiscard]] inline AE_RUNTIME_DATA* GetAERuntimeData() noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
				if (REL::Module::get().version().compare(SKSE::RUNTIME_SSE_1_6_629) != std::strong_ordering::less) {
					return REL::RelocateMember<AE_RUNTIME_DATA*>(this, 0x68);
				}
			}
			return nullptr;
		}

		[[nodiscard]] inline const AE_RUNTIME_DATA& GetAERuntimeData() const noexcept
		{
			return this->GetAERuntimeData();
		}

		[[nodiscard]] bool IsFleeing() const
		{
			return state->isFleeing;
		}

		// members
		CombatGroup*                   combatGroup;           // 00
		CombatState*                   state;                 // 08
		CombatInventory*               inventory;             // 10
		CombatBlackboard*              blackboard;            // 18
		CombatBehaviorController*      behaviorController;    // 20
		ActorHandle                    attackerHandle;        // 28
		ActorHandle                    targetHandle;          // 2C
		ActorHandle                    previousTargetHandle;  // 30
		std::uint8_t                   unk34;                 // 34
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

	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_AE)
	static_assert(sizeof(CombatController) == 0xE0);
#else
	static_assert(sizeof(CombatController) == 0xD8);
#endif
}
