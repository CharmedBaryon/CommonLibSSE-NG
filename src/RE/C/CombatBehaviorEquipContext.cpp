#include "RE/C/CombatBehaviorEquipContext.h"

#include "RE/C/CombatBehaviorController.h"
#include "RE/C/CombatBehaviorThread.h"
#include "RE/C/CombatController.h"
#include "RE/C/CombatInventory.h"
#include "RE/T/TLSData.h"

namespace RE
{
	class CombatInventory;

	bool CombatBehaviorEquipContext::CanEquipItem() const
	{
		// not in addresslib

		// CombatInventory::CanEquip
		using func_t = bool (*)(CombatInventory* self, uint32_t slot, CombatInventoryItem* citem);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43628, 0) };
		return func(GetStaticTLSData()->combatAIThread->controller->combatController->inventory, slot, combat_item);
	}

	bool CombatBehaviorEquipContext::CheckEquipmentChanged()
	{
		using func_t = decltype(&CombatBehaviorEquipContext::CheckEquipmentChanged);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46951, 0) };
		return func(this);
	}

	bool CombatBehaviorEquipContext::EquipItem()
	{
		using func_t = decltype(&CombatBehaviorEquipContext::EquipItem);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46952, 0) };
		return func(this);
	}

	NiPointer<CombatInventoryItem> const& CombatBehaviorEquipContext::GetCombatItem() const
	{
		using func_t = decltype(&CombatBehaviorEquipContext::GetCombatItem);
		static REL::Relocation<func_t> func{ RELOCATION_ID(32458, 0) };
		return func(this);
	}

	CombatInventoryItem::TYPE CombatBehaviorEquipContext::GetEquipmentType() const
	{
		// not in addresslib
		if (combat_item) {
			auto raceEquipSlots = GetStaticTLSData()->combatAIThread->controller->combatController->inventory->raceEquipSlots;
			if (slot < raceEquipSlots->size())
				if (auto eq_slot = (*raceEquipSlots)[slot])
					return combat_item->GetEquipType(eq_slot);
		}

		return CombatInventoryItem::TYPE::kNone;
	}
}
