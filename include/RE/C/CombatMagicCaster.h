#pragma once

#include "RE/C/CombatInventoryItem.h"
#include "RE/C/CombatObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatController;
	class CombatProjectileAimController;
	class MagicItem;

	class CombatMagicCaster : public CombatObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatMagicCaster;
		inline static constexpr auto VTABLE = VTABLE_CombatMagicCaster;

		~CombatMagicCaster() override;  // 00

		// override (CombatObject)
		void SaveGame(BGSSaveGameBuffer* a_buf) override;  // 03
		void LoadGame(BGSLoadGameBuffer* a_buf) override;  // 04

		// add
		virtual CombatInventoryItem::CATEGORY GetCategory() = 0;                                                   // 05
		virtual bool                          CheckStartCast(CombatController* a_combatController);                // 06
		virtual bool                          CheckStopCast(CombatController* a_combatController);                 // 07
		virtual float                         CalcCastMagicChance(CombatController* a_combatController) const;     // 08
		virtual float                         CalcMagicHoldTime(CombatController* a_combatController) const;       // 09
		virtual void*                         GetMagicTarget(CombatController* a_combatController) const;          // 0A
		virtual void                          NotifyStartCast(CombatController* a_combatController);               // 0B
		virtual void                          NotifyStopCast(CombatController* a_combatController);                // 0C
		virtual void                          SetupAimController(CombatProjectileAimController* a_aimController);  // 0D

		bool CheckTargetValid(const CombatController* a_combatController)
		{
			using func_t = bool* (*)(CombatMagicCaster*, const CombatController*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(43956, 45348) };
			return func(this, a_combatController);
		}

		static bool CheckTargetValid(const CombatController* a_combatController, Actor* a_target, const CombatInventoryItemMagic* a_inventoryItem)
		{
			using func_t = bool* (*)(const CombatController*, Actor*, const CombatInventoryItemMagic*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(43952, 45343) };
			return func(a_combatController, a_target, a_inventoryItem);
		}

		// members
		NiPointer<CombatInventoryItemMagic> inventoryItem;  // 10
		MagicItem*                          magicItem;      // 18
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatMagicCaster) == 0x20);
}
