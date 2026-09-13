#include "RE/B/BGSBipedObjectForm.h"

namespace RE
{
	auto BGSBipedObjectForm::AddSlotToMask(BipedObjectSlot a_slot)
		-> BipedObjectSlot
	{
		bipedModelData.bipedObjectSlots.set(a_slot);
		return *bipedModelData.bipedObjectSlots;
	}

	auto BGSBipedObjectForm::GetArmorType() const
		-> ArmorType
	{
		return *bipedModelData.armorType;
	}

	auto BGSBipedObjectForm::GetSlotMask() const
		-> REX::EnumSet<BipedObjectSlot, std::uint32_t>
	{
		return bipedModelData.bipedObjectSlots;
	}

	bool BGSBipedObjectForm::HasPartOf(BipedObjectSlot a_flag) const
	{
		return bipedModelData.bipedObjectSlots.all(a_flag);
	}

	bool BGSBipedObjectForm::IsClothing() const
	{
		return bipedModelData.armorType == ArmorType::kClothing;
	}

	bool BGSBipedObjectForm::IsHeavyArmor() const
	{
		return bipedModelData.armorType == ArmorType::kHeavyArmor;
	}

	bool BGSBipedObjectForm::IsLightArmor() const
	{
		return bipedModelData.armorType == ArmorType::kLightArmor;
	}

	bool BGSBipedObjectForm::IsShield() const
	{
		return bipedModelData.bipedObjectSlots.all(BipedObjectSlot::kShield);
	}

	bool BGSBipedObjectForm::IsHelmet() const
	{
		return bipedModelData.bipedObjectSlots.all(BipedObjectSlot::kHair, BipedObjectSlot::kCirclet);
	}

	bool BGSBipedObjectForm::IsCirclet() const
	{
		return bipedModelData.bipedObjectSlots.all(BipedObjectSlot::kCirclet) &&
		       !bipedModelData.bipedObjectSlots.all(BipedObjectSlot::kHair);
	}

	bool BGSBipedObjectForm::IsAccessory() const
	{
		return bipedModelData.bipedObjectSlots.all(BipedObjectSlot::kRing) || bipedModelData.bipedObjectSlots.all(BipedObjectSlot::kAmulet) || IsCirclet();
	}

	bool BGSBipedObjectForm::IsBoots() const
	{
		return bipedModelData.bipedObjectSlots.all(BipedObjectSlot::kFeet);
	}

	bool BGSBipedObjectForm::IsGauntlets() const
	{
		return bipedModelData.bipedObjectSlots.all(BipedObjectSlot::kHands);
	}

	bool BGSBipedObjectForm::IsChestpiece() const
	{
		return bipedModelData.bipedObjectSlots.all(BipedObjectSlot::kBody);
	}

	auto BGSBipedObjectForm::RemoveSlotFromMask(BipedObjectSlot a_slot)
		-> BipedObjectSlot
	{
		if (a_slot != BipedObjectSlot::kNone) {
			bipedModelData.bipedObjectSlots.reset(a_slot);
		}
		return *bipedModelData.bipedObjectSlots;
	}

	void BGSBipedObjectForm::SetSlotMask(BipedObjectSlot a_mask)
	{
		bipedModelData.bipedObjectSlots = a_mask;
	}
}
