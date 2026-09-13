#include "RE/B/BGSCreatedObjectManager.h"

namespace RE
{
	BGSCreatedObjectManager* BGSCreatedObjectManager::GetSingleton()
	{
		static REL::Relocation<BGSCreatedObjectManager**> singleton{ RELOCATION_ID(514172, 400320) };
		return *singleton;
	}

	EnchantmentItem* BGSCreatedObjectManager::AddArmorEnchantment(BSTArray<Effect>& a_effects)
	{
		using func_t = decltype(&BGSCreatedObjectManager::AddArmorEnchantment);
		static REL::Relocation<func_t> func{ RELOCATION_ID(35264, 36166) };
		return func(this, a_effects);
	}

	EnchantmentItem* BGSCreatedObjectManager::AddWeaponEnchantment(BSTArray<Effect>& a_effects)
	{
		using func_t = decltype(&BGSCreatedObjectManager::AddWeaponEnchantment);
		static REL::Relocation<func_t> func{ RELOCATION_ID(35263, 36165) };
		return func(this, a_effects);
	}

	AlchemyItem* BGSCreatedObjectManager::AddPoison(BSTSmartPointer<AlchemyItem>& a_out, BSTArray<Effect>& a_effects)
	{
		using func_t = decltype(&BGSCreatedObjectManager::AddPoison);
		static REL::Relocation<func_t> func{ RELOCATION_ID(35266, 36168) };
		return func(this, a_out, a_effects);
	}

	void BGSCreatedObjectManager::DestroyEnchantment(EnchantmentItem* a_enchantment, bool a_isWeapon)
	{
		using func_t = decltype(&BGSCreatedObjectManager::DestroyEnchantment);
		static REL::Relocation<func_t> func{ RELOCATION_ID(35267, 36169) };
		func(this, a_enchantment, a_isWeapon);
	}

	void BGSCreatedObjectManager::AddPotion(BSTSmartPointer<
												AlchemyItem,
												BSTCreatedObjectSmartPointerPolicy>& a_created,
		BSTArray<Effect>&                                                            a_effects)
	{
		using func_t = decltype(&BGSCreatedObjectManager::AddPotion);
		static REL::Relocation<func_t> func{ RELOCATION_ID(35265, 36167) };
		func(this, a_created, a_effects);
	}

	void BGSCreatedObjectManager::DecrementRef(AlchemyItem* a_alchItem)
	{
		using func_t = decltype(&BGSCreatedObjectManager::DecrementRef);
		static REL::Relocation<func_t> func{ RELOCATION_ID(35269, 36171) };
		func(this, a_alchItem);
	}

	void BGSCreatedObjectManager::IncrementRef(AlchemyItem* a_alchItem)
	{
		using func_t = decltype(&BGSCreatedObjectManager::IncrementRef);
		static REL::Relocation<func_t> func{ RELOCATION_ID(35268, 36170) };
		func(this, a_alchItem);
	}
}
