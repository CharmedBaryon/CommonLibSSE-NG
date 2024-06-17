#pragma once

#include "RE/C/CombatMagicCaster.h"

namespace RE
{
	class CombatMagicCasterInvisibility : public CombatMagicCaster
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatMagicCasterInvisibility;
		inline static constexpr auto VTABLE = VTABLE_CombatMagicCasterInvisibility;

		~CombatMagicCasterInvisibility() override;  // 00

		// override (CombatMagicCaster)
		std::uint32_t                 GetObjectType() override;                                       // 02
		CombatInventoryItem::CATEGORY GetCategory() override;                                         // 05
		bool                          CheckStartCast(CombatController* a_combatController) override;  // 06
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatMagicCasterInvisibility) == 0x20);
}
