#pragma once

#include "RE/C/CombatMagicCaster.h"

namespace RE
{
	class CombatMagicCasterStagger : public CombatMagicCaster
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatMagicCasterStagger;
		inline static constexpr auto VTABLE = VTABLE_CombatMagicCasterStagger;

		~CombatMagicCasterStagger() override;  // 00

		// override (CombatMagicCaster)
		std::uint32_t                 GetObjectType() override;                                       // 02
		CombatInventoryItem::CATEGORY GetCategory() override;                                         // 05
		bool                          CheckStartCast(CombatController* a_combatController) override;  // 06
		bool                          CheckStopCast(CombatController* a_combatController) override;   // 07
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatMagicCasterStagger) == 0x20);
}
