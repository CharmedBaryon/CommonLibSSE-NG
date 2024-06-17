#pragma once

#include "RE/A/AITimer.h"
#include "RE/C/CombatMagicCaster.h"

namespace RE
{
	class CombatMagicCasterWard : public CombatMagicCaster
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatMagicCasterWard;
		inline static constexpr auto VTABLE = VTABLE_CombatMagicCasterWard;

		~CombatMagicCasterWard() override;  // 00

		// override (CombatMagicCaster)
		std::uint32_t                 GetObjectType() override;                                       // 02
		void                          SaveGame(BGSSaveGameBuffer* a_buf) override;                    // 03
		void                          LoadGame(BGSLoadGameBuffer* a_buf) override;                    // 04
		CombatInventoryItem::CATEGORY GetCategory() override;                                         // 05
		bool                          CheckStartCast(CombatController* a_combatController) override;  // 06
		bool                          CheckStopCast(CombatController* a_combatController) override;   // 07

		// members
		AITimer cooldownTimer;  // 20
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatMagicCasterWard) == 0x28);
}
