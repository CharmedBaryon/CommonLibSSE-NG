#pragma once

#include "RE/C/CombatInventoryItem.h"

namespace RE
{
	class MagicItem;

	struct Effect;

	class CombatInventoryItemMagic : public CombatInventoryItem
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatInventoryItemMagic;
		inline static constexpr auto VTABLE = VTABLE_CombatInventoryItemMagic;

		~CombatInventoryItemMagic() override;  // 00

		// override (CombatInventoryItem)
		void  SaveGame(BGSSaveGameBuffer* a_buf) override;                    // 03
		void  LoadGame(BGSLoadGameBuffer* a_buf) override;                    // 04
		float GetMinRange() override;                                         // 05 - { return minRange; }
		float GetMaxRange() override;                                         // 06 - { return maxRange; }
		float GetOptimalRange() override;                                     // 07 - { return ((maxRange - minRange) * fCombatInventoryOptimalRangePercent) + minRange; }
		float GetEquipRange() override;                                       // 08
		TYPE  GetType() override;                                             // 09 - { return 4; }
		TYPE  GetEquipType(BGSEquipSlot a_slot) override;                     // 0A
		float CalculateScore(CombatController* a_controller) override;        // 0C
		bool  CheckBusy(CombatController* a_controller) override;             // 0E
		bool  CheckShouldEquip(CombatController* a_controller) override;      // 0F - { return true; }
		bool  GetResource(CombatInventoryItemResource& a_resource) override;  // 10
		bool  IsValid() override;                                             // 12 - { return item && effect; }

		//add
		virtual void*      CreateCaster() = 0;  // 15
		virtual MagicItem* GetMagic();          // 16 - { return unk10; };

		// members
		float   minRange;          // 30
		float   maxRange;          // 34
		float   tacticalDuration;  // 38
		float   power;             // 3C
		float   currentAV;         // 40
		Effect* effect;            // 48
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatInventoryItemMagic) == 0x50);
}
