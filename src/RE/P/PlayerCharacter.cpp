#include "RE/P/PlayerCharacter.h"

#include "RE/T/TESObjectREFR.h"

using namespace REL;

namespace RE
{
	bool PlayerCharacter::PlayerSkills::CanLevelUp()
	{
		return this->data->levelThreshold <= this->data->xp;
	}

	void PlayerCharacter::PlayerSkills::AdvanceLevel(bool a_addThreshold)
	{
		using func_t = decltype(&PlayerCharacter::PlayerSkills::AdvanceLevel);
		static REL::Relocation<func_t> func{ RELOCATION_ID(40560, 41567) };
		func(this, a_addThreshold);
	}

	PlayerCharacter* PlayerCharacter::GetSingleton()
	{
		static REL::Relocation<NiPointer<PlayerCharacter>*> singleton{ RELOCATION_ID(517014, 403521) };
		return singleton->get();
	}

	bool PlayerCharacter::IsGodMode()
	{
		static REL::Relocation<bool*> singleton{ RELOCATION_ID(517711, 404238) };
		return *singleton;
	}

	void PlayerCharacter::ActivatePickRef()
	{
		using func_t = decltype(&PlayerCharacter::ActivatePickRef);
		static REL::Relocation<func_t> func{ RELOCATION_ID(39471, 40548) };
		func(this);
	}

	void PlayerCharacter::ActivatePickRefVR(VR_DEVICE a_device)
	{
		using func_t = decltype(&PlayerCharacter::ActivatePickRefVR);
		static REL::Relocation<func_t> func{ RELOCATION_ID(39471, 40548) };
		return func(this, a_device);
	}

	void PlayerCharacter::AddPlayerAddItemEvent(TESObject* a_object, TESForm* a_owner, TESObjectREFR* a_container, AQUIRE_TYPE a_type)
	{
		using func_t = decltype(&PlayerCharacter::AddPlayerAddItemEvent);
		static REL::Relocation<func_t> func{ RELOCATION_ID(39384, 40456) };
		func(this, a_object, a_owner, a_container, a_type);
	}

	bool PlayerCharacter::AttemptPickpocket(TESObjectREFR* a_containerRef, InventoryEntryData* a_entry, std::int32_t a_number, bool a_fromContainer)
	{
		using func_t = decltype(&PlayerCharacter::AttemptPickpocket);
		static REL::Relocation<func_t> func{ RELOCATION_ID(39568, 40654) };
		return func(this, a_containerRef, a_entry, a_number, a_fromContainer);
	}

	bool PlayerCharacter::CenterOnCell(const char* a_cellName)
	{
		return CenterOnCell_Impl(a_cellName, nullptr);
	}

	bool PlayerCharacter::CenterOnCell(TESObjectCELL* a_cell)
	{
		return CenterOnCell_Impl(nullptr, a_cell);
	}

	bool PlayerCharacter::CheckCast(MagicItem* a_spell, Effect* a_effect, MagicSystem::CannotCastReason& a_reason)
	{
		using func_t = decltype(&PlayerCharacter::CheckCast);
		static REL::Relocation<func_t> func{ RELOCATION_ID(39409, 40484) };
		return func(this, a_spell, a_effect, a_reason);
	}

	void PlayerCharacter::CheckPoisonWeapon(AlchemyItem* a_poison)
	{
		using func_t = decltype(&PlayerCharacter::CheckPoisonWeapon);
		static REL::Relocation<func_t> func{ RELOCATION_ID(39406, 40481) };
		func(this, a_poison);
	}

	void PlayerCharacter::DestroyMouseSprings()
	{
		using func_t = decltype(&PlayerCharacter::DestroyMouseSprings);
		static REL::Relocation<func_t> func{ RELOCATION_ID(39480, 40557) };
		func(this);
	}

	void PlayerCharacter::EndGrabObject()
	{
		if (GetPlayerRuntimeData().grabType == GrabbingType::kNormal) {
			DestroyMouseSprings();
		}
	}

	NiPointer<Actor> PlayerCharacter::GetActorDoingPlayerCommand() const
	{
		if SKYRIM_REL_CONSTEXPR (REL::Module::IsVR()) {
			return REL::RelocateMember<ActorHandle>(this, 0, 0xE8C).get();
		} else {
			return REL::RelocateMemberIfNewer<ActorHandle>(SKSE::RUNTIME_SSE_1_6_629, this, 0x894, REL::VersionShift(0x89C, kAE1799ShiftBytes, SKSE::RUNTIME_SSE_1_7_99)).get();
		}
	}

	float PlayerCharacter::GetArmorValue(InventoryEntryData* a_form)
	{
		using func_t = decltype(&PlayerCharacter::GetArmorValue);
		static REL::Relocation<func_t> func{ RELOCATION_ID(39175, 40249) };
		return func(this, a_form);
	}

	float PlayerCharacter::GetDamage(InventoryEntryData* a_form)
	{
		using func_t = decltype(&PlayerCharacter::GetDamage);
		static REL::Relocation<func_t> func{ RELOCATION_ID(39179, 40253) };
		return func(this, a_form);
	}

	float PlayerCharacter::GetEquippedWeaponsDamage()
	{
		using func_t = decltype(&PlayerCharacter::GetEquippedWeaponsDamage);
		static REL::Relocation<func_t> func{ RELOCATION_ID(0, 40252) };
		return func(this);
	}

	NiPointer<TESObjectREFR> PlayerCharacter::GetGrabbedRef(VR_DEVICE a_device)
	{
		if SKYRIM_REL_CONSTEXPR (Module::IsVR()) {
			return GetVRPlayerRuntimeData()->grabbedObjectData[a_device].grabbedObject.get();
		} else {
			return REL::RelocateMemberIfNewer<ObjectRefHandle>(SKSE::RUNTIME_SSE_1_6_629, this, 0x8C8, REL::VersionShift(0x8D0, kAE1799ShiftBytes, SKSE::RUNTIME_SSE_1_7_99)).get();
		}
	}

	std::int32_t PlayerCharacter::GetItemCount(TESBoundObject* a_object)
	{
		using func_t = decltype(&PlayerCharacter::GetItemCount);
		static REL::Relocation<func_t> func{ RELOCATION_ID(19275, 19701) };
		return func(this, a_object);
	}

	std::uint32_t PlayerCharacter::GetNumTints(std::uint32_t a_tintType)
	{
		using func_t = decltype(&PlayerCharacter::GetNumTints);
		static REL::Relocation<func_t> func{ RELOCATION_ID(39614, 40700) };
		return func(this, a_tintType);
	}

	// TODO need to understand how this changed in VR
#ifndef ENABLE_SKYRIM_VR
	TintMask* PlayerCharacter::GetOverlayTintMask(TintMask* a_original)
	{
		if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
			return nullptr;
		} else {
			auto* tryOverlayTintMasks = REL::RelocateMemberIfNewer<BSTArray<TintMask*>*>(SKSE::RUNTIME_SSE_1_6_629, this, 0xB28, 0xB30);
			if (!tryOverlayTintMasks) {
				return nullptr;
			}

			auto& tintMasksValue = REL::RelocateMemberIfNewer<BSTArray<TintMask*>>(SKSE::RUNTIME_SSE_1_6_629, this, 0xB10, 0xB18);
			for (std::uint32_t i = 0; i < tintMasksValue.size(); ++i) {
				if (tintMasksValue[i] == a_original) {
					return i < tryOverlayTintMasks->size() ? (*tryOverlayTintMasks)[i] : nullptr;
				}
			}

			return nullptr;
		}
	}

	BSTArray<TintMask*>* PlayerCharacter::GetTintList()
	{
		if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
			return nullptr;
		} else {
			auto* tryOverlayTintMasks = REL::RelocateMemberIfNewer<BSTArray<TintMask*>*>(SKSE::RUNTIME_SSE_1_6_629, this, 0xB28, 0xB30);
			return tryOverlayTintMasks ? tryOverlayTintMasks : &REL::RelocateMemberIfNewer<BSTArray<TintMask*>>(SKSE::RUNTIME_SSE_1_6_629, this, 0xB10, 0xB18);
		}
	}

	TintMask* PlayerCharacter::GetTintMask(std::uint32_t a_tintType, std::uint32_t a_index)
	{
		if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
			return nullptr;
		} else {
			using func_t = decltype(&PlayerCharacter::GetTintMask);
			static REL::Relocation<func_t> func{ RELOCATION_ID(39612, 40698) };
			return func(this, a_tintType, a_index);
		}
	}
#endif

	bool PlayerCharacter::HasActorDoingCommand() const
	{
		if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
			return static_cast<bool>(REL::RelocateMember<ActorHandle>(this, 0, 0xE8C));
		} else {
			return static_cast<bool>(REL::RelocateMemberIfNewer<ActorHandle>(SKSE::RUNTIME_SSE_1_6_629, this, 0x894, REL::VersionShift(0x89C, kAE1799ShiftBytes, SKSE::RUNTIME_SSE_1_7_99)));
		}
	}

	bool PlayerCharacter::IsGrabbing() const
	{
		if SKYRIM_REL_CONSTEXPR (Module::IsVR()) {
			for (auto& VRgrabData : GetVRPlayerRuntimeData()->grabbedObjectData) {
				if (VRgrabData.grabbedObject) {
					return true;
				}
			}
			return false;
		} else {
			return static_cast<bool>(REL::RelocateMemberIfNewer<ObjectRefHandle>(SKSE::RUNTIME_SSE_1_6_629, this, 0x8C8, REL::VersionShift(0x8D0, kAE1799ShiftBytes, SKSE::RUNTIME_SSE_1_7_99)));
		}
	}

#ifdef ENABLE_SKYRIM_VR
	bool PlayerCharacter::IsGrabbingWithDevice(VR_DEVICE a_device) const
	{
		auto* vrData = GetVRPlayerRuntimeData();
		return vrData && static_cast<bool>(vrData->grabbedObjectData[a_device].grabbedObject);
	}
#endif

	void PlayerCharacter::PlayMagicFailureSound(MagicSystem::SpellType a_spellType)
	{
		using func_t = decltype(&PlayerCharacter::PlayMagicFailureSound);
		static REL::Relocation<func_t> func{ RELOCATION_ID(39486, 40565) };
		func(this, a_spellType);
	}

	void PlayerCharacter::SetAIDriven(bool a_enable)
	{
		using func_t = decltype(&PlayerCharacter::SetAIDriven);
		static REL::Relocation<func_t> func{ RELOCATION_ID(39507, 40586) };
		func(this, a_enable);
	}

	void PlayerCharacter::SetEscaping(bool a_flag, bool a_escaped)
	{
		using func_t = decltype(&PlayerCharacter::SetEscaping);
		static REL::Relocation<func_t> func{ RELOCATION_ID(39574, 40660) };
		func(this, a_flag, a_escaped);
	}

	void PlayerCharacter::SetGodMode(bool a_enable)
	{
		using func_t = decltype(&PlayerCharacter::SetGodMode);
		static REL::Relocation<func_t> func{ RELOCATION_ID(39424, 40500) };
		return func(this, a_enable);
	}

	void PlayerCharacter::StartGrabObject(VR_DEVICE a_device)
	{
		using func_t = decltype(&PlayerCharacter::StartGrabObject);
		static REL::Relocation<func_t> func{ RELOCATION_ID(39475, 40552) };
		return func(this, a_device);
	}

	void PlayerCharacter::StartWaiting(std::int32_t a_hours)
	{
		using func_t = decltype(&PlayerCharacter::StartWaiting);
		static REL::Relocation<func_t> func{ RELOCATION_ID(39344, 40415) };
		return func(this, a_hours);
	}

	void PlayerCharacter::UpdateCrosshairs()
	{
		using func_t = decltype(&PlayerCharacter::UpdateCrosshairs);
		static REL::Relocation<func_t> func(RELOCATION_ID(39535, 40621));
		func(this);
	}

	void PlayerCharacter::UpdateVRComfortCheck()
	{
		if (REL::Module::IsVR()) {
			using func_t = decltype(&PlayerCharacter::UpdateVRComfortCheck);
			static REL::Relocation<func_t> func{ REL::VariantID(0, 0, 0x6B9AA0) };
			func(this);
		}
	}

	void PlayerCharacter::UsePoisonFromInventory(AlchemyItem* a_poison)
	{
		using func_t = decltype(&PlayerCharacter::UsePoisonFromInventory);
		static REL::Relocation<func_t> func{ RELOCATION_ID(39406, 40481) };
		return func(this, a_poison);
	}

	bool PlayerCharacter::CenterOnCell_Impl(const char* a_cellName, RE::TESObjectCELL* a_cell)
	{
		using func_t = decltype(&PlayerCharacter::CenterOnCell_Impl);
		static REL::Relocation<func_t> func{ RELOCATION_ID(39365, 40437) };
		return func(this, a_cellName, a_cell);
	}

	void PlayerCharacter::AddSkillExperience(ActorValue a_skill, float a_experience)
	{
		using func_t = decltype(&PlayerCharacter::AddSkillExperience);
		static REL::Relocation<func_t> func(RELOCATION_ID(39413, 40488));
		func(this, a_skill, a_experience);
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
