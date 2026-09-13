#include "RE/T/TESObjectARMO.h"

#include "RE/T/TESObjectARMA.h"

namespace RE
{
	float TESObjectARMO::GetArmorRating()
	{
		return static_cast<float>(armorRating) / static_cast<float>(100.0);
	}

	TESObjectARMA* TESObjectARMO::GetArmorAddon(TESRace* a_race)
	{
		if (a_race) {
			for (auto& currentAddon : armorAddons) {
				if (currentAddon && currentAddon->IsValidRace(a_race)) {
					return currentAddon;
				}
			}
		}
		return nullptr;
	}

	TESObjectARMA* TESObjectARMO::GetArmorAddonByMask(TESRace* a_race, BipedObjectSlot a_slot)
	{
		if (a_race) {
			for (auto& currentAddon : armorAddons) {
				if (currentAddon && currentAddon->IsValidRace(a_race) && currentAddon->HasPartOf(a_slot)) {
					return currentAddon;
				}
			}
		}
		return nullptr;
	}

	void TESObjectARMO::InitWornArmor(Actor* a_actor, BSTSmartPointer<BipedAnim>* a_biped)
	{
		using func_t = decltype(&TESObjectARMO::InitWornArmor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(24232, 24736) };
		return func(this, a_actor, a_biped);
	}
}
