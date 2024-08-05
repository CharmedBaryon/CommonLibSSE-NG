#include "RE/I/InventoryEntryData.h"

#include "RE/E/ExtraCharge.h"
#include "RE/E/ExtraEnchantment.h"
#include "RE/E/ExtraHotkey.h"
#include "RE/E/ExtraLeveledItem.h"
#include "RE/E/ExtraPoison.h"
#include "RE/E/ExtraTextDisplayData.h"
#include "RE/E/ExtraWorn.h"
#include "RE/E/ExtraWornLeft.h"
#include "RE/F/FormTraits.h"
#include "RE/G/GameSettingCollection.h"
#include "RE/T/TESBoundObject.h"
#include "RE/T/TESEnchantableForm.h"
#include "RE/T/TESSoulGem.h"

namespace RE
{
	InventoryEntryData::InventoryEntryData(const InventoryEntryData& a_rhs) :
		object(a_rhs.object),
		countDelta(a_rhs.countDelta)
	{
		if (a_rhs.extraLists) {
			extraLists = new BSSimpleList<ExtraDataList*>(*a_rhs.extraLists);
		}
	}

	InventoryEntryData::~InventoryEntryData()
	{
		delete extraLists;
	}

	InventoryEntryData& InventoryEntryData::operator=(const InventoryEntryData& a_rhs)
	{
		if (this != std::addressof(a_rhs)) {
			object = a_rhs.object;

			delete extraLists;
			extraLists =
				a_rhs.extraLists ?
					new BSSimpleList<ExtraDataList*>(*a_rhs.extraLists) :
					nullptr;

			countDelta = a_rhs.countDelta;
		}
		return *this;
	}

	InventoryEntryData& InventoryEntryData::operator=(InventoryEntryData&& a_rhs)
	{
		if (this != std::addressof(a_rhs)) {
			delete extraLists;

			object = std::exchange(a_rhs.object, nullptr);
			extraLists = std::exchange(a_rhs.extraLists, nullptr);
			countDelta = std::exchange(a_rhs.countDelta, 0);
		}
		return *this;
	}

	void InventoryEntryData::AddExtraList(ExtraDataList* a_extra)
	{
		if (!a_extra) {
			return;
		}

		if (!extraLists) {
			extraLists = new BSSimpleList<ExtraDataList*>;
		}

		extraLists->push_front(a_extra);
	}

	const char* InventoryEntryData::GetDisplayName()
	{
		const char* name = nullptr;
		if (extraLists) {
			for (auto& xList : *extraLists) {
				if (xList) {
					name = xList->GetDisplayName(object);
				}
			}
		}

		if ((!name || name[0] == '\0') && object) {
			name = object->GetName();
		}

		if (!name || name[0] == '\0') {
			auto gmst = GameSettingCollection::GetSingleton();
			auto sMissingName = gmst ? gmst->GetSetting("sMissingName") : nullptr;
			name = sMissingName ? sMissingName->GetString() : "";
		}

		return name;
	}

	EnchantmentItem* InventoryEntryData::GetEnchantment() const
	{
		using func_t = decltype(&InventoryEntryData::GetEnchantment);
		static REL::Relocation<func_t> func{ RELOCATION_ID(15788, 16026) };
		return func(this);
	}

	std::optional<double> InventoryEntryData::GetEnchantmentCharge() const
	{
		std::optional<double> result;
		auto                  obj = GetObject();
		auto                  ench = obj ? obj->As<TESEnchantableForm>() : nullptr;
		if (ench && ench->formEnchanting && ench->amountofEnchantment != 0) {
			result.emplace(100.0);
		}

		if (extraLists) {
			for (auto& xList : *extraLists) {
				if (xList) {
					auto xCharge = xList->GetByType<ExtraCharge>();
					auto xEnch = xList->GetByType<ExtraEnchantment>();
					if (xEnch && xEnch->enchantment && xEnch->charge != 0) {
						if (xCharge) {
							result.emplace((static_cast<double>(xCharge->charge) /
											   static_cast<double>(xEnch->charge)) *
										   100.0);
						} else {
							result.emplace(100.0);
						}
						break;
					} else if (xCharge && ench && ench->formEnchanting && ench->amountofEnchantment != 0) {
						result.emplace((static_cast<double>(xCharge->charge) /
										   static_cast<double>(ench->amountofEnchantment)) *
									   100.0);
						break;
					}
				}
			}
		}

		return result;
	}

	TESForm* InventoryEntryData::GetOwner()
	{
		if (extraLists) {
			for (auto& xList : *extraLists) {
				auto owner = xList ? xList->GetOwner() : nullptr;
				if (owner) {
					return owner;
				}
			}
		}
		return nullptr;
	}

	SOUL_LEVEL InventoryEntryData::GetSoulLevel() const
	{
		if (extraLists) {
			for (auto& xList : *extraLists) {
				if (xList) {
					auto lvl = xList->GetSoulLevel();
					if (lvl > SOUL_LEVEL::kNone) {
						return lvl;
					}
				}
			}
		}

		if (object && object->Is(FormType::SoulGem)) {
			auto soulGem = static_cast<const TESSoulGem*>(object);
			return soulGem->GetContainedSoul();
		}

		return SOUL_LEVEL::kNone;
	}

	float InventoryEntryData::GetWeight() const
	{
		return object ? object->GetWeight() : -1.0F;
	}

	std::int32_t InventoryEntryData::GetValue() const
	{
		using func_t = decltype(&InventoryEntryData::GetValue);
		static REL::Relocation<func_t> func{ RELOCATION_ID(15757, 15995) };
		return func(this);
	}

	bool InventoryEntryData::IsEnchanted() const
	{
		if (object) {
			auto ench = object->As<TESEnchantableForm>();
			if (ench && ench->formEnchanting) {
				return true;
			}
		}

		if (extraLists) {
			for (const auto& xList : *extraLists) {
				const auto xEnch = xList->GetByType<ExtraEnchantment>();
				if (xEnch && xEnch->enchantment) {
					return true;
				}
			}
		}

		return false;
	}

	bool InventoryEntryData::IsFavorited() const
	{
		return HasExtraDataType<ExtraHotkey>();
	}

	bool InventoryEntryData::IsLeveled() const
	{
		return HasExtraDataType<ExtraLeveledItem>();
	}

	bool InventoryEntryData::IsPoisoned() const
	{
		return HasExtraDataType<ExtraPoison>();
	}

	bool InventoryEntryData::IsWorn() const
	{
		if (extraLists) {
			for (const auto& xList : *extraLists) {
				if (xList && (xList->HasType<ExtraWorn>() || xList->HasType<ExtraWornLeft>())) {
					return true;
				}
			}
		}

		return false;
	}

	bool InventoryEntryData::IsOwnedBy(Actor* a_testOwner, bool a_defaultTo)
	{
		return IsOwnedBy(a_testOwner, GetOwner(), a_defaultTo);
	}

	bool InventoryEntryData::IsOwnedBy(Actor* a_testOwner, TESForm* a_itemOwner, bool a_defaultTo)
	{
		return IsOwnedBy_Impl(a_testOwner, a_itemOwner, a_defaultTo);
	}

	bool InventoryEntryData::IsQuestObject() const
	{
		if (extraLists) {
			for (const auto& xList : *extraLists) {
				if (xList && xList->HasQuestObjectAlias()) {
					return true;
				}
			}
		}

		return false;
	}

	void InventoryEntryData::PoisonObject(AlchemyItem* a_alchItem, std::uint32_t a_count)
	{
		using func_t = decltype(&InventoryEntryData::PoisonObject);
		static REL::Relocation<func_t> func{ RELOCATION_ID(15786, 16024) };
		return func(this, a_alchItem, a_count);
	}

	bool InventoryEntryData::IsOwnedBy_Impl(Actor* a_testOwner, TESForm* a_itemOwner, bool a_defaultTo)
	{
		using func_t = decltype(&InventoryEntryData::IsOwnedBy_Impl);
		static REL::Relocation<func_t> func{ RELOCATION_ID(15782, 16020) };
		return func(this, a_testOwner, a_itemOwner, a_defaultTo);
	}
}
