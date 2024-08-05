#pragma once

#include "RE/C/CombatMagicCaster.h"

namespace RE
{
	class CombatMagicCasterBoundItem : public CombatMagicCaster
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatMagicCasterBoundItem;
		inline static constexpr auto VTABLE = VTABLE_CombatMagicCasterBoundItem;

		~CombatMagicCasterBoundItem() override;  // 00

		// override (CombatMagicCaster)
		std::uint32_t                 GetObjectType() override;                                       // 02
		CombatInventoryItem::CATEGORY GetCategory() override;                                         // 05
		bool                          CheckStartCast(CombatController* a_combatController) override;  // 06
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatMagicCasterBoundItem) == 0x20);
}
