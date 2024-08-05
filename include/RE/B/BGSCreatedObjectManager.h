#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTSingleton.h"
#include "RE/E/Effect.h"

namespace RE
{
	class MagicItem;
	class EnchantmentItem;

	class BGSCreatedObjectManager : public BSTSingletonSDM<BGSCreatedObjectManager>
	{
	public:
		struct CreatedMagicItemData
		{
			MagicItem*             magicItem;  // 00
			volatile std::uint32_t refCount;   // 08
			std::uint32_t          pad0C;      // 0C
		};
		static_assert(sizeof(CreatedMagicItemData) == 0x10);

		static BGSCreatedObjectManager* GetSingleton();

		EnchantmentItem* AddArmorEnchantment(BSTArray<Effect>& a_effects);
		EnchantmentItem* AddWeaponEnchantment(BSTArray<Effect>& a_effects);

		// members
		std::uint8_t                                    pad01;               // 01
		std::uint16_t                                   pad02;               // 02
		std::uint32_t                                   pad04;               // 03
		BSTArray<CreatedMagicItemData>                  weaponEnchantments;  // 08
		BSTArray<CreatedMagicItemData>                  armorEnchantments;   // 20
		BSTHashMap<std::uint32_t, CreatedMagicItemData> potions;             // 38
		BSTHashMap<std::uint32_t, CreatedMagicItemData> poisons;             // 68
		BSTSet<MagicItem*>                              queuedDeletes;       // 98
		mutable BSSpinLock                              lock;                // C8
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSCreatedObjectManager) == 0xD0);
}
