#pragma once

#include "RE/C/CombatInventoryItemMagic.h"

namespace RE
{
	class CombatInventoryItemShout : public CombatInventoryItemMagic
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatInventoryItemShout;
		inline static constexpr auto VTABLE = VTABLE_CombatInventoryItemShout;

		~CombatInventoryItemShout() override;  // 00

		// override (CombatInventoryItemMagic)
		TYPE       GetType() override;                                         // 09 - { return 5; }
		bool       CheckBusy(CombatController* a_controller) override;         // 0E - { return actor->GetVoiceState() != 0; }
		bool       CheckShouldEquip(CombatController* a_controller) override;  // 0F - { return fCombatInventoryShoutMaxRecoveryTime >= actor->GetVoiceRecoveryTime(); }
		MagicItem* GetMagic() override;                                        // 16
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatInventoryItemShout) == 0x50);
}
