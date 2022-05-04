#pragma once

#include "RE/C/CombatMagicCaster.h"

namespace RE
{
	class CombatMagicCasterTargetEffect : public CombatMagicCaster
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatMagicCasterTargetEffect;
		inline static constexpr auto VTABLE = VTABLE_CombatMagicCasterTargetEffect;

		~CombatMagicCasterTargetEffect() override;  // 00

		// override (CombatMagicCaster)
		void                          SaveGame(BGSSaveGameBuffer* a_buf) override;                               // 03
		void                          LoadGame(BGSLoadGameBuffer* a_buf) override;                               // 04
		CombatInventoryItem::CATEGORY GetCategory() override;                                                    // 05
		bool                          CheckStartCast(CombatController* a_combatController) override;             // 06
		bool                          CheckStopCast(CombatController* a_combatController) override;              // 07
		float                         CalcCastMagicChance(CombatController* a_combatController) const override;  // 08
		float                         CalcMagicHoldTime(CombatController* a_combatController) const override;    // 09
		void*                         GetMagicTarget(CombatController* a_combatController) const override;       // 0A
	};
	static_assert(sizeof(CombatMagicCasterTargetEffect) == 0x20);
}
