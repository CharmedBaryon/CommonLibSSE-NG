#pragma once

#include "RE/C/CombatInventoryItemMagic.h"

namespace RE
{
	class CombatInventoryItemScroll : public CombatInventoryItemMagic
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatInventoryItemScroll;
		inline static constexpr auto VTABLE = VTABLE_CombatInventoryItemScroll;

		~CombatInventoryItemScroll() override;  // 00

		// override (CombatInventoryItemMagic)
		TYPE GetType() override;                                  // 09 - { return 8; }
		bool CheckBusy(CombatController* a_controller) override;  // 0E
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatInventoryItemScroll) == 0x50);
}
