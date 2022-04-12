#include "RE/P/PlayerCharacter.h"

#include "RE/T/TESObjectREFR.h"

using namespace REL;

namespace RE
{
	void PlayerCharacter::PlayerSkills::AdvanceLevel(bool a_addThreshold)
	{
		using func_t = decltype(&PlayerCharacter::PlayerSkills::AdvanceLevel);
		REL::Relocation<func_t> func{ Offset::PlayerCharacter::PlayerSkills::AdvanceLevel };
		return func(this, a_addThreshold);
	}

	PlayerCharacter* PlayerCharacter::GetSingleton()
	{
		REL::Relocation<NiPointer<PlayerCharacter>*> singleton{ Offset::PlayerCharacter::Singleton };
		return singleton->get();
	}

	void PlayerCharacter::ActivatePickRef()
	{
		using func_t = decltype(&PlayerCharacter::ActivatePickRef);
		REL::Relocation<func_t> func{ Offset::PlayerCharacter::ActivatePickRef };
		return func(this);
	}

	bool PlayerCharacter::AttemptPickpocket(TESObjectREFR* a_containerRef, InventoryEntryData* a_entry, std::int32_t a_number, bool a_fromContainer)
	{
		using func_t = decltype(&PlayerCharacter::AttemptPickpocket);
		REL::Relocation<func_t> func{ REL::RelocationID(39568, 40654) };
		return func(this, a_containerRef, a_entry, a_number, a_fromContainer);
	}

	bool PlayerCharacter::CenterOnCell(const char* a_cellName)
	{
		return CenterOnCell_Impl(a_cellName, nullptr);
	}

	bool PlayerCharacter::CenterOnCell(RE::TESObjectCELL* a_cell)
	{
		return CenterOnCell_Impl(nullptr, a_cell);
	}

	NiPointer<Actor> PlayerCharacter::GetActorDoingPlayerCommand() const
	{
		return REL::RelocateMember<ActorHandle>(this, 0x894, 0xE8C).get();
	}

	float PlayerCharacter::GetArmorValue(InventoryEntryData* a_form)
	{
		using func_t = decltype(&PlayerCharacter::GetArmorValue);
		REL::Relocation<func_t> func{ Offset::PlayerCharacter::GetArmorValue };
		return func(this, a_form);
	}

	float PlayerCharacter::GetDamage(InventoryEntryData* a_form)
	{
		using func_t = decltype(&PlayerCharacter::GetDamage);
		REL::Relocation<func_t> func{ Offset::PlayerCharacter::GetDamage };
		return func(this, a_form);
	}

	NiPointer<TESObjectREFR> PlayerCharacter::GetGrabbedRef()
	{
		if (REL::Module::get().IsVR()) {
			return nullptr;
		}
		return REL::RelocateMember<ObjectRefHandle>(this, 0x8C8, 0).get();
	}

	std::uint32_t PlayerCharacter::GetNumTints(std::uint32_t a_tintType)
	{
		using func_t = decltype(&PlayerCharacter::GetNumTints);
		REL::Relocation<func_t> func{ Offset::PlayerCharacter::GetNumTints };
		return func(this, a_tintType);
	}

#ifndef ENABLE_SKYRIM_VR
	TintMask* PlayerCharacter::GetOverlayTintMask(TintMask* a_original)
	{
		if (!overlayTintMasks) {
			return nullptr;
		}

		for (std::uint32_t i = 0; i < tintMasks.size(); ++i) {
			if (tintMasks[i] == a_original) {
				return i < overlayTintMasks->size() ? (*overlayTintMasks)[i] : nullptr;
			}
		}

		return nullptr;
	}

	BSTArray<TintMask*>& PlayerCharacter::GetTintList()
	{
		return overlayTintMasks ? *overlayTintMasks : tintMasks;
	}

	TintMask* PlayerCharacter::GetTintMask(std::uint32_t a_tintType, std::uint32_t a_index)
	{
		using func_t = decltype(&PlayerCharacter::GetTintMask);
		REL::Relocation<func_t> func{ Offset::PlayerCharacter::GetTintMask };
		return func(this, a_tintType, a_index);
	}
#endif

	bool PlayerCharacter::HasActorDoingCommand() const
	{
		return static_cast<bool>(REL::RelocateMember<ActorHandle>(this, 0x894, 0xE8C));
	}

	bool PlayerCharacter::IsGrabbing() const
	{
		if (Module::get().IsVR()) {
			return false;
		}
		return static_cast<bool>(REL::RelocateMember<ObjectRefHandle>(this, 0x8C8, 0));
	}

	void PlayerCharacter::PlayPickupEvent(TESForm* a_item, TESForm* a_containerOwner, TESObjectREFR* a_containerRef, EventType a_eventType)
	{
		using func_t = decltype(&PlayerCharacter::PlayPickupEvent);
		REL::Relocation<func_t> func{ Offset::PlayerCharacter::PlayPickupEvent };
		return func(this, a_item, a_containerOwner, a_containerRef, a_eventType);
	}

	void PlayerCharacter::StartGrabObject()
	{
		using func_t = decltype(&PlayerCharacter::StartGrabObject);
		REL::Relocation<func_t> func{ Offset::PlayerCharacter::StartGrabObject };
		return func(this);
	}

	bool PlayerCharacter::CenterOnCell_Impl(const char* a_cellName, RE::TESObjectCELL* a_cell)
	{
		using func_t = decltype(&PlayerCharacter::CenterOnCell_Impl);
		REL::Relocation<func_t> func{ REL::RelocationID(39365, 40437) };
		return func(this, a_cellName, a_cell);
	}

	void PlayerCharacter::AddSkillExperience(ActorValue a_skill, float a_experience)
	{
		using func_t = decltype(&PlayerCharacter::AddSkillExperience);
		REL::Relocation<func_t> func(REL::RelocationID(39413, 40488));
		return func(this, a_skill, a_experience);
	}

	void PlayerCharacter::Unk_12A()
	{
		return RelocateVirtual<decltype(&PlayerCharacter::Unk_12A)>(0x12A, 0x12C, this);
	}

	std::uint32_t PlayerCharacter::GetViolentCrimeGoldValue(const TESFaction* a_faction) const
	{
		return RelocateVirtual<decltype(&PlayerCharacter::GetViolentCrimeGoldValue)>(0x12B, 0x12D, this, a_faction);
	}

	std::uint32_t PlayerCharacter::GetNonViolentCrimeGoldValue(const TESFaction* a_faction) const
	{
		return RelocateVirtual<decltype(&PlayerCharacter::GetNonViolentCrimeGoldValue)>(0x12C, 0x12E, this, a_faction);
	}

	void PlayerCharacter::ClearAllCrimeGold(TESFaction* a_faction)
	{
		RelocateVirtual<decltype(&PlayerCharacter::ClearAllCrimeGold)>(0x12D, 0x12F, this, a_faction);
	}

	void PlayerCharacter::Unk_12E()
	{
		return RelocateVirtual<decltype(&PlayerCharacter::Unk_12E)>(0x12E, 0x130, this);
	}
}
