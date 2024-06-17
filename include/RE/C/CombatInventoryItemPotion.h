#pragma once

#include "RE/C/CombatInventoryItemMagic.h"

namespace RE
{
	class CombatInventoryItemPotion : public CombatInventoryItemMagic
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatInventoryItemPotion;
		inline static constexpr auto VTABLE = VTABLE_CombatInventoryItemPotion;

		~CombatInventoryItemPotion() override;  // 00

		// override (CombatInventoryItemMagic)
		TYPE GetType() override;                                  // 09 - { return 7; }
		bool CheckBusy(CombatController* a_controller) override;  // 0E
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatInventoryItemPotion) == 0x50);
}
