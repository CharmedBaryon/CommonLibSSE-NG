#pragma once

#include "RE/A/AITimeStamp.h"
#include "RE/A/AITimer.h"
#include "RE/B/BSTArray.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BGSEquipSlot;
	class CombatController;
	class CombatInventoryItem;
	class CombatObject;
	class TESObjectWEAP;
	class TESForm;

	struct CombatEquipment
	{
	public:
		// members
		BSTArray<NiPointer<CombatInventoryItem>> items;         // 00
		std::uint32_t                            slot;          // 18
		float                                    maxRange;      // 1C
		float                                    optimalRange;  // 20
		float                                    minRange;      // 24
		float                                    score;         // 28
	};
	static_assert(sizeof(CombatEquipment) == 0x30);

	struct CombatEquippedItem
	{
	public:
		// members
		NiPointer<CombatInventoryItem> item;       // 00
		AITimeStamp                    equipTime;  // 08
	};
	static_assert(sizeof(CombatEquippedItem) == 0x10);

	class CombatInventory
	{
	public:
		// members
		CombatController*                        parentController;          // 000
		BSTArray<NiPointer<CombatInventoryItem>> inventoryItems[7];         // 008 - sorted by score?
		BSTArray<TESForm*>                       unk0B0;                    // 0B0
		BSTArray<TESForm*>                       unk0C8;                    // 0C8
		BSTArray<BGSEquipSlot*>*                 raceEquipSlots;            // 0E0
		std::uint64_t                            unk0E8;                    // 0E8 - map?
		std::uint32_t                            unk0F0;                    // 0F0
		std::uint32_t                            unk0F4;                    // 0F4
		std::uint32_t                            unk0F8;                    // 0F8
		std::uint32_t                            unk0FC;                    // 0FC
		std::uint64_t                            unk100;                    // 100
		std::uint64_t                            unk108;                    // 108
		std::uint64_t                            unk110;                    // 110
		CombatEquipment                          unk118;                    // 118
		CombatEquipment                          unk148;                    // 148
		BSTArray<CombatEquippedItem>             equippedItems;             // 178
		std::int32_t                             unk190;                    // 190
		AITimer                                  equippedTimer;             // 194
		std::uint32_t                            unk19C;                    // 19C
		std::uint32_t                            unk1A0;                    // 1A0
		std::uint32_t                            unk1A4;                    // 1A4
		float                                    actorExtents;              // 1A8
		float                                    actorCollisionExtents;     // 1AC
		float                                    minimumEffectiveDistance;  // 1B0
		float                                    maximumEffectiveDistance;  // 1B4
		float                                    maximumRange;              // 1B8
		float                                    optimalRange;              // 1BC
		float                                    minimumRange;              // 1C0
		bool                                     dirty;                     // 1C4
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatInventory) == 0x1C8);
}
