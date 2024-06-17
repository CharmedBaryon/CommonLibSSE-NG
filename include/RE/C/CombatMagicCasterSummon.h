#pragma once

#include "RE/C/CombatMagicCaster.h"

namespace RE
{
	class CombatMagicCasterSummon : public CombatMagicCaster
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatMagicCasterSummon;
		inline static constexpr auto VTABLE = VTABLE_CombatMagicCasterSummon;

		~CombatMagicCasterSummon() override;  // 00

		// override (CombatMagicCaster)
		std::uint32_t                 GetObjectType() override;                                       // 02
		CombatInventoryItem::CATEGORY GetCategory() override;                                         // 05
		bool                          CheckStartCast(CombatController* a_combatController) override;  // 06
		void                          NotifyStopCast(CombatController* a_combatController) override;  // 0C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatMagicCasterSummon) == 0x20);
}
