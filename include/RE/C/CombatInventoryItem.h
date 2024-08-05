#pragma once

#include "RE/A/ActorValues.h"
#include "RE/C/CombatObject.h"

namespace RE
{
	class BGSLoadGameBuffer;
	class BGSSaveGameBuffer;
	class CombatController;
	class TESBoundObject;
	class BGSEquipSlot;

	struct CombatInventoryItemResource
	{
	public:
		// members
		ActorValue actorValue;  // 00
		float      value;       // 04
	};
	static_assert(sizeof(CombatInventoryItemResource) == 0x8);

	class CombatInventoryItemSlot
	{
	public:
		// members
		BGSEquipSlot* equipSlot;  // 08
		std::uint32_t slot;       // 0C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatInventoryItemSlot) == 0x10);

	class CombatInventoryItem : public CombatObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatInventoryItem;
		inline static constexpr auto VTABLE = VTABLE_CombatInventoryItem;

		enum class TYPE
		{
			kNone = 0,
			kMelee,
			kRanged,
			kShield,
			kOneHandedBlock = kShield,
			kMagic,
			kShout,
			kStaff,
			kPotion,
			kScroll,
			kTorch
		};

		enum class CATEGORY
		{
			kTotal = 7
		};

		~CombatInventoryItem() override;  // 00

		// override (CombatObject)
		void SaveGame(BGSSaveGameBuffer* a_buf) override;  // 03
		void LoadGame(BGSLoadGameBuffer* a_buf) override;  // 04

		// add
		virtual float                GetMinRange();                                             // 05 - { return 0.0; }
		virtual float                GetMaxRange();                                             // 06 - { return 0.0; }
		virtual float                GetOptimalRange();                                         // 07 - { return 0.0; }
		virtual float                GetEquipRange();                                           // 08 - { return FLT_MAX; }
		virtual TYPE                 GetType();                                                 // 09
		virtual TYPE                 GetEquipType(BGSEquipSlot a_slot);                         // 0A - { return GetType(); }
		virtual CATEGORY             GetCategory() = 0;                                         // 0B
		virtual float                CalculateScore(CombatController* a_controller) = 0;        // 0C
		virtual CombatInventoryItem* Clone() = 0;                                               // 0D
		virtual bool                 CheckBusy(CombatController* a_controller);                 // 0E
		virtual bool                 CheckShouldEquip(CombatController* a_controller);          // 0F - { return !a_controller->state->isFleeing; }
		virtual bool                 GetResource(CombatInventoryItemResource& a_resource);      // 10
		virtual void                 Equip(CombatController* a_controller);                     // 11
		virtual void                 Unequip(CombatController* a_controller);                   // 12
		virtual bool                 IsValid();                                                 // 13 - { return item != nullptr; }
		virtual void                 GetDescription(const char* a_dest, std::uint32_t a_size);  // 14

		// members
		TESForm*                item;       // 10
		float                   itemScore;  // 18
		std::uint32_t           unk1C;      // 1C
		CombatInventoryItemSlot itemSlot;   // 20
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatInventoryItem) == 0x30);
}
