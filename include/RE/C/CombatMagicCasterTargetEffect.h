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
		std::uint32_t                 GetObjectType() override;                                       // 02
		CombatInventoryItem::CATEGORY GetCategory() override;                                         // 05
		bool                          CheckStartCast(CombatController* a_combatController) override;  // 06
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatMagicCasterTargetEffect) == 0x20);
}
