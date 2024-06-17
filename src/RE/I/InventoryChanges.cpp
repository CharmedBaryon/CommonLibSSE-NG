#pragma once
#include "RE/I/InventoryChanges.h"
#include "RE/A/Actor.h"
#include "RE/F/FormTraits.h"
#include "RE/T/TESObjectREFR.h"
namespace RE
{
	InventoryChanges::InventoryChanges() :
		InventoryChanges(nullptr)
	{}

	InventoryChanges::InventoryChanges(TESObjectREFR* a_ref)
	{
		Ctor(a_ref);
	}

	InventoryChanges::~InventoryChanges()
	{
		Dtor();
		stl::memzero(this);
	}

	void InventoryChanges::AddEntryData(InventoryEntryData* a_entry)
	{
		if (!entryList) {
			entryList = new std::remove_pointer_t<decltype(entryList)>;
		}

		entryList->push_front(a_entry);
		changed = true;
	}

	void InventoryChanges::GenerateLeveledListChanges()
	{
		using func_t = decltype(&InventoryChanges::GenerateLeveledListChanges);
		REL::Relocation<func_t> func{ RELOCATION_ID(15829, 16068) };
		return func(this);
	}

	std::int16_t InventoryChanges::GetItemCount(RE::TESBoundObject* a_obj)
	{
		using func_t = decltype(&InventoryChanges::GetItemCount);
		REL::Relocation<func_t> func{ RELOCATION_ID(15868, 16047) };
		return func(this, a_obj);
	}

	TESObjectARMO* InventoryChanges::GetArmorInSlot(std::int32_t a_slot)
	{
		if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
			auto actor = this->owner ? this->owner->As<RE::Actor>() : nullptr;
			if (!actor) {
				return nullptr;
			}
			auto bipedSlot = (a_slot - 30) >= 0 ? 1 << (a_slot - 30) : 0;
			return actor->GetWornArmor(static_cast<BGSBipedObjectForm::BipedObjectSlot>(bipedSlot));
		} else {
			using func_t = decltype(&InventoryChanges::GetArmorInSlot);
			REL::Relocation<func_t> func{ RELOCATION_ID(15873, 16113) };
			return func(this, a_slot);
		}
	}

	float InventoryChanges::GetInventoryWeight()
	{
		using func_t = decltype(&InventoryChanges::GetInventoryWeight);
		REL::Relocation<func_t> func{ RELOCATION_ID(15883, 16123) };
		return func(this);
	}

	std::uint16_t InventoryChanges::GetNextUniqueID()
	{
		using func_t = decltype(&InventoryChanges::GetNextUniqueID);
		REL::Relocation<func_t> func{ Offset::InventoryChanges::GetNextUniqueID };
		return func(this);
	}

	std::uint32_t InventoryChanges::GetWornMask()
	{
		using func_t = decltype(&InventoryChanges::GetWornMask);
		REL::Relocation<func_t> func{ RELOCATION_ID(15806, 16044) };
		return func(this);
	}

	void InventoryChanges::RemoveFavorite(InventoryEntryData* a_entry, ExtraDataList* a_itemList)
	{
		using func_t = decltype(&InventoryChanges::RemoveFavorite);
		REL::Relocation<func_t> func{ RELOCATION_ID(15859, 16099) };
		return func(this, a_entry, a_itemList);
	}

	void InventoryChanges::RemoveAllItems(TESObjectREFR* a_ref, TESObjectREFR* a_moveToRef, bool a_arg4, bool a_keepOwnership, bool a_arg6)
	{
		using func_t = decltype(&InventoryChanges::RemoveAllItems);
		REL::Relocation<func_t> func{ RELOCATION_ID(15878, 16118) };
		return func(this, a_ref, a_moveToRef, a_arg4, a_keepOwnership, a_arg6);
	}

	void InventoryChanges::SendContainerChangedEvent(ExtraDataList* a_itemExtraList, TESObjectREFR* a_fromRefr, TESForm* a_item, std::int32_t a_count)
	{
		using func_t = decltype(&InventoryChanges::SendContainerChangedEvent);
		REL::Relocation<func_t> func{ Offset::InventoryChanges::SendContainerChangedEvent };
		return func(this, a_itemExtraList, a_fromRefr, a_item, a_count);
	}

	void InventoryChanges::SetFavorite(InventoryEntryData* a_entry, ExtraDataList* a_itemList)
	{
		using func_t = decltype(&InventoryChanges::SetFavorite);
		REL::Relocation<func_t> func{ RELOCATION_ID(15858, 16098) };
		return func(this, a_entry, a_itemList);
	}

	void InventoryChanges::SetUniqueID(ExtraDataList* a_itemList, TESForm* a_oldForm, TESForm* a_newForm)
	{
		using func_t = decltype(&InventoryChanges::SetUniqueID);
		REL::Relocation<func_t> func{ Offset::InventoryChanges::SetUniqueID };
		return func(this, a_itemList, a_oldForm, a_newForm);
	}

	void InventoryChanges::VisitInventory(IItemChangeVisitor& visitor)
	{
		using func_t = decltype(&InventoryChanges::VisitInventory);
		REL::Relocation<func_t> func{ RELOCATION_ID(15855, 16095) };
		return func(this, visitor);
	}

	void InventoryChanges::VisitWornItems(IItemChangeVisitor& visitor)
	{
		using func_t = decltype(&InventoryChanges::VisitWornItems);
		REL::Relocation<func_t> func{ RELOCATION_ID(15856, 16096) };
		return func(this, visitor);
	}

	void InventoryChanges::InitFromContainerExtra()
	{
		using func_t = decltype(&InventoryChanges::InitFromContainerExtra);
		REL::Relocation<func_t> func{ RELOCATION_ID(15890, 16130) };
		return func(this);
	}

	void InventoryChanges::InitLeveledItems()
	{
		using func_t = decltype(&InventoryChanges::InitLeveledItems);
		REL::Relocation<func_t> func{ RELOCATION_ID(15889, 16129) };
		return func(this);
	}

	void InventoryChanges::InitOutfitItems(BGSOutfit* a_outfit, std::uint16_t a_npcLevel)
	{
		using func_t = decltype(&InventoryChanges::InitOutfitItems);
		REL::Relocation<func_t> func{ RELOCATION_ID(15833, 16072) };
		return func(this, a_outfit, a_npcLevel);
	}

	void InventoryChanges::InitScripts()
	{
		using func_t = decltype(&InventoryChanges::InitScripts);
		REL::Relocation<func_t> func{ RELOCATION_ID(15829, 16068) };
		return func(this);
	}

	InventoryChanges* InventoryChanges::Ctor(TESObjectREFR* a_ref)
	{
		using func_t = decltype(&InventoryChanges::Ctor);
		REL::Relocation<func_t> func{ RELOCATION_ID(15812, 16050) };
		return func(this, a_ref);
	}

	void InventoryChanges::Dtor()
	{
		using func_t = decltype(&InventoryChanges::Dtor);
		REL::Relocation<func_t> func{ RELOCATION_ID(15813, 16051) };
		return func(this);
	}
}
