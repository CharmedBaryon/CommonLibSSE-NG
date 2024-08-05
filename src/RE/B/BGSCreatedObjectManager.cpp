#include "RE/B/BGSCreatedObjectManager.h"

namespace RE
{
	BGSCreatedObjectManager* BGSCreatedObjectManager::GetSingleton()
	{
		REL::Relocation<BGSCreatedObjectManager**> singleton{ RELOCATION_ID(514172, 400320) };
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
}
