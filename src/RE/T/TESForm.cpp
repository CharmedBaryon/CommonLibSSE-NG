#include "RE/T/TESForm.h"

#include "RE/B/BGSDefaultObjectManager.h"
#include "RE/B/BGSKeywordForm.h"
#include "RE/F/FormTraits.h"
#include "RE/I/IObjectHandlePolicy.h"
#include "RE/I/InventoryEntryData.h"
#include "RE/T/TESDataHandler.h"
#include "RE/T/TESFullName.h"
#include "RE/T/TESGlobal.h"
#include "RE/T/TESModel.h"
#include "RE/T/TESObjectREFR.h"
#include "RE/V/VirtualMachine.h"

namespace RE
{
	std::int32_t TESForm::GetGoldValue() const
	{
		const auto obj = As<TESBoundObject>();
		if (obj) {
			const InventoryEntryData entry{ const_cast<TESBoundObject*>(obj), 1 };
			return entry.GetValue();
		} else {
			return -1;
		}
	}

	const char* TESForm::GetName() const
	{
		const auto fullName = As<TESFullName>();
		if (fullName) {
			const auto str = fullName->GetFullName();
			return str ? str : "";
		} else {
			return "";
		}
	}

	float TESForm::GetWeight() const
	{
		using func_t = decltype(&TESForm::GetWeight);
		REL::Relocation<func_t> func{ RELOCATION_ID(14809, 14988) };
		return func(this);
	}

	bool TESForm::HasAnyKeywordByEditorID(const std::vector<std::string>& editorIDs) const
	{
		// Try to cast to a keyword form interface
		const auto keywordForm = As<BGSKeywordForm>();
		if (!keywordForm) {
			return false;
		}

		// Iterate through the keywords
		bool hasKeyword = false;

		keywordForm->ForEachKeyword([&](const BGSKeyword* a_keyword) {
			if (std::ranges::find(editorIDs, a_keyword->GetFormEditorID()) != editorIDs.end()) {
				hasKeyword = true;
				return BSContainer::ForEachResult::kStop;
			}
			return BSContainer::ForEachResult::kContinue;
		});

		return hasKeyword;
	}

	bool TESForm::HasKeywordByEditorID(std::string_view a_editorID)
	{
		const auto keywordForm = As<BGSKeywordForm>();
		if (!keywordForm) {
			return false;
		}

		return keywordForm->HasKeywordString(a_editorID);
	}

	bool TESForm::HasKeywordInArray(const std::vector<BGSKeyword*>& a_keywords, bool a_matchAll) const
	{
		const auto keywordForm = As<BGSKeywordForm>();
		if (!keywordForm) {
			return false;
		}

		bool hasKeyword = false;

		for (const auto& keyword : a_keywords) {
			hasKeyword = keyword && keywordForm->HasKeyword(keyword);
			if ((a_matchAll && !hasKeyword) || hasKeyword) {
				break;
			}
		}

		return hasKeyword;
	}

	bool TESForm::HasKeywordInList(BGSListForm* a_keywordList, bool a_matchAll) const
	{
		if (!a_keywordList) {
			return false;
		}

		const auto keywordForm = As<BGSKeywordForm>();
		if (!keywordForm) {
			return false;
		}

		bool hasKeyword = false;

		a_keywordList->ForEachForm([&](const TESForm* a_form) {
			const auto keyword = a_form->As<BGSKeyword>();
			hasKeyword = keyword && keywordForm->HasKeyword(keyword);
			if ((a_matchAll && !hasKeyword) || hasKeyword) {
				return BSContainer::ForEachResult::kStop;
			}
			return BSContainer::ForEachResult::kContinue;
		});

		return hasKeyword;
	}

	bool TESForm::HasVMAD() const
	{
		const auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
		if (!vm) {
			return false;
		}

		const auto policy = vm->GetObjectHandlePolicy();
		if (!policy) {
			return false;
		}

		const auto handle = policy->GetHandleForObject(GetFormType(), this);
		return handle != policy->EmptyHandle();
	}

	bool TESForm::HasWorldModel() const noexcept
	{
		return As<TESModel>() != nullptr;
	}

	FormID TESForm::GetRawFormID() const
	{
		const auto* modFile = GetFile(0);
		if (!modFile) {
			return 0;
		}

		const auto* expectedFile = (formID & 0xFF000000) == 0xFE000000 ?
		                               TESDataHandler::GetSingleton()->LookupLoadedLightModByIndex(
										   static_cast<uint16_t>((0x00FFF000 & formID) >> 12)) :
		                               TESDataHandler::GetSingleton()->LookupLoadedModByIndex(
										   static_cast<uint8_t>((0xFF000000 & formID) >> 24));

		std::uint32_t fullMasters = 0;
		std::uint32_t smallMasters = 0;

		if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
			for (std::uint32_t i = 0; i < modFile->masterCount; ++i) {
				const auto* master = modFile->masterPtrs[i];
				if (master == expectedFile) {
					return (fullMasters << 24) | (formID & 0x00FFFFFF);
				}
				++fullMasters;
			}
			return (formID & 0x00FFFFFF) | (fullMasters << 24);
		} else {
			for (std::uint32_t i = 0; i < modFile->masterCount; ++i) {
				const auto* master = modFile->masterPtrs[i];
				if (master == expectedFile) {
					if (master->compileIndex == 0xFE) {
						return 0xFE000000 | (smallMasters << 12) | (formID & 0x00000FFF);
					} else {
						return (fullMasters << 24) | (formID & 0x00FFFFFF);
					}
				}
				if (master->compileIndex == 0xFE) {
					++smallMasters;
				} else {
					++fullMasters;
				}
			}
			if (modFile->compileIndex == 0xFE) {
				return (formID & 0x00000FFF) | 0xFE000000 | (smallMasters << 12);
			} else {
				return (formID & 0x00FFFFFF) | (fullMasters << 24);
			}
		}
	}

	bool TESForm::IsInventoryObject() const
	{
		switch (GetFormType()) {
		case FormType::Scroll:
		case FormType::Armor:
		case FormType::Book:
		case FormType::Ingredient:
		case FormType::Light:
		case FormType::Misc:
		case FormType::Apparatus:
		case FormType::Weapon:
		case FormType::Ammo:
		case FormType::KeyMaster:
		case FormType::AlchemyItem:
		case FormType::Note:
		case FormType::ConstructibleObject:
		case FormType::SoulGem:
		case FormType::LeveledItem:
			return true;
		default:
			return false;
		}
	}

	void TESForm::SetPlayerKnows(bool a_known)
	{
		using func_t = decltype(&TESForm::SetPlayerKnows);
		static REL::Relocation<func_t> func{ RELOCATION_ID(14482, 14639) };
		return func(this, a_known);
	}
}
