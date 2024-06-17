#pragma once

#include "RE/C/CombatInventoryItemMagic.h"

namespace RE
{
	class CombatInventoryItemStaff : public CombatInventoryItemMagic
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatInventoryItemStaff;
		inline static constexpr auto VTABLE = VTABLE_CombatInventoryItemStaff;

		~CombatInventoryItemStaff() override;  // 00

		// override (CombatInventoryItemMagic)
		TYPE       GetType() override;   // 09 - { return 6; }
		MagicItem* GetMagic() override;  // 16
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatInventoryItemStaff) == 0x50);
}
