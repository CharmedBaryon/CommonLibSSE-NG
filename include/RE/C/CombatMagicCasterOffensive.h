#pragma once

#include "RE/A/AITimer.h"
#include "RE/C/CombatMagicCaster.h"

namespace RE
{
	class CombatMagicCasterOffensive : public CombatMagicCaster
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatMagicCasterOffensive;
		inline static constexpr auto VTABLE = VTABLE_CombatMagicCasterOffensive;

		~CombatMagicCasterOffensive() override;  // 00

		// override (CombatMagicCaster)
		std::uint32_t                 GetObjectType() override;                                                  // 02
		void                          SaveGame(BGSSaveGameBuffer* a_buf) override;                               // 03
		void                          LoadGame(BGSLoadGameBuffer* a_buf) override;                               // 04
		CombatInventoryItem::CATEGORY GetCategory() override;                                                    // 05 - { return 0; }
		bool                          CheckStartCast(CombatController* a_combatController) override;             // 06
		bool                          CheckStopCast(CombatController* a_combatController) override;              // 07
		float                         CalcCastMagicChance(CombatController* a_combatController) const override;  // 08
		float                         CalcMagicHoldTime(CombatController* a_combatController) const override;    // 09
		void                          NotifyStartCast(CombatController* a_combatController) override;            // 0B
		void                          NotifyStopCast(CombatController* a_combatController) override;             // 0C

		// members
		AITimer startCastTimer;  // 20
		AITimer stopCastTimer;   // 28
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatMagicCasterOffensive) == 0x30);
}
