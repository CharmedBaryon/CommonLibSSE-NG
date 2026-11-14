#pragma once

#include "RE/A/AlchemyItem.h"
#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTSingleton.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/E/Effect.h"

namespace RE
{
	class MagicItem;
	class AlchemyItem;
	class EnchantmentItem;
	class AlchemyItem;

	class BGSCreatedObjectManager : public BSTSingletonSDM<BGSCreatedObjectManager>
	{
	public:
		void DecrementRef(AlchemyItem* a_alchItem);
		void IncrementRef(AlchemyItem* a_alchItem);

		template <class T>
		struct BSTCreatedObjectSmartPointerPolicy
		{
		public:
			static void Acquire(T* a_ptr)
			{
				const auto manager = BGSCreatedObjectManager::GetSingleton();
				if (manager &&
					a_ptr->IsDynamicForm() &&
					a_ptr->Is(FormType::AlchemyItem)) {
					manager->IncrementRef(static_cast<AlchemyItem*>(a_ptr));
				}
			}

			static void Release(T* a_ptr)
			{
				const auto manager = BGSCreatedObjectManager::GetSingleton();
				if (manager &&
					a_ptr->IsDynamicForm() &&
					a_ptr->Is(FormType::AlchemyItem)) {
					manager->DecrementRef(static_cast<AlchemyItem*>(a_ptr));
				}
			}
		};

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
		AlchemyItem*     AddPoison(BSTSmartPointer<AlchemyItem>& a_out, BSTArray<Effect>& a_effects);
		void             AddPotion(BSTSmartPointer<AlchemyItem, BSTCreatedObjectSmartPointerPolicy>& a_created, BSTArray<Effect>& a_effects);
		void             DestroyEnchantment(EnchantmentItem* a_enchantment, bool a_isWeapon);

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
	};
	static_assert(sizeof(BGSCreatedObjectManager) == 0xD0);

	extern template struct BGSCreatedObjectManager::BSTCreatedObjectSmartPointerPolicy<AlchemyItem>;
	extern template struct BGSCreatedObjectManager::BSTCreatedObjectSmartPointerPolicy<TESForm>;

	template <class T>
	using CreatedObjPtr = BSTSmartPointer<T, BGSCreatedObjectManager::BSTCreatedObjectSmartPointerPolicy>;
}
