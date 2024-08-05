#pragma once

#include "RE/C/CombatInventoryItemMagic.h"

namespace RE
{
	template <class InventoryItem, class MagicCaster>
	class CombatInventoryItemMagicT : public CombatInventoryItemMagic
	{
	public:
		~CombatInventoryItemMagicT() override;  // 00
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatInventoryItemMagicT<void*, void*>) == 0x50);
}
