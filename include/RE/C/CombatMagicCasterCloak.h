#pragma once

#include "RE/C/CombatMagicCaster.h"

namespace RE
{
	class CombatMagicCasterCloak : public CombatMagicCaster
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatMagicCasterCloak;
		inline static constexpr auto VTABLE = VTABLE_CombatMagicCasterCloak;

		~CombatMagicCasterCloak() override;  // 00

		// override (CombatMagicCaster)
		std::uint32_t                 GetObjectType() override;                                       // 02
		CombatInventoryItem::CATEGORY GetCategory() override;                                         // 05
		bool                          CheckStartCast(CombatController* a_combatController) override;  // 06
		bool                          CheckStopCast(CombatController* a_combatController) override;   // 07
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatMagicCasterCloak) == 0x20);
}
