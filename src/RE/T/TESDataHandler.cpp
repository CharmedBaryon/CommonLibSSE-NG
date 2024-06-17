#include "RE/T/TESDataHandler.h"

#include "RE/T/TESFile.h"
#include "RE/T/TESForm.h"

#include "REX/W32/BASE.h"
#undef GetModuleHandle

namespace RE
{

	TESDataHandler* TESDataHandler::GetSingleton(bool a_VRESL)
	{
		REL::Relocation<TESDataHandler**> singleton{ Offset::TESDataHandler::Singleton };
		if (REL::Module::IsVR() && a_VRESL && !VRcompiledFileCollection) {
			const auto VRhandle = REX::W32::GetModuleHandleW(L"skyrimvresl");
			if (VRhandle != NULL) {
				const auto GetCompiledFileCollection = reinterpret_cast<const RE::TESFileCollection* (*)()>(REX::W32::GetProcAddress(VRhandle, "GetCompiledFileCollectionExtern"));
				if (GetCompiledFileCollection != nullptr) {
					TESDataHandler::VRcompiledFileCollection = const_cast<RE::TESFileCollection*>(GetCompiledFileCollection());
				}
			}
		}
		return *singleton;
	}

	bool TESDataHandler::AddFormToDataHandler(TESForm* a_form)
	{
		using func_t = decltype(&TESDataHandler::AddFormToDataHandler);
		REL::Relocation<func_t> func{ RELOCATION_ID(13597, 13693) };
		return func(this, a_form);
	}

	std::uint32_t TESDataHandler::LoadScripts()
	{
		using func_t = decltype(&TESDataHandler::LoadScripts);
		REL::Relocation<func_t> func{ Offset::TESDataHandler::LoadScripts };
		return func(this);
	}

	TESForm* TESDataHandler::LookupForm(FormID a_localFormID, std::string_view a_modName)
	{
		auto formID = LookupFormID(a_localFormID, a_modName);
		return formID ? TESForm::LookupByID(formID) : nullptr;
	}

	TESForm* TESDataHandler::LookupFormRaw(FormID a_rawFormID, std::string_view a_modName)
	{
		auto formID = LookupFormIDRaw(a_rawFormID, a_modName);
		return formID ? TESForm::LookupByID(formID) : nullptr;
	}

	FormID TESDataHandler::LookupFormID(FormID a_localFormID, std::string_view a_modName)
	{
		auto file = LookupModByName(a_modName);
		if (!file || file->compileIndex == 0xFF) {
			return 0;
		}

		if (REL::Module::IsVR() && !VRcompiledFileCollection) {
			// Use SkyrimVR lookup logic, ignore light plugin index which doesn't exist in VR
			return (a_localFormID & 0xFFFFFF) | (file->compileIndex << 24);
		} else {
			FormID formID = file->compileIndex << (3 * 8);
			formID += file->smallFileCompileIndex << ((1 * 8) + 4);
			formID += a_localFormID;
			return formID;
		}
	}

	FormID TESDataHandler::LookupFormIDRaw(FormID a_rawFormID, std::string_view a_modName)
	{
		auto file = LookupModByName(a_modName);
		if (!file || file->compileIndex == 0xFF) {
			return 0;
		}

		auto rawIndex = (a_rawFormID & 0xFF000000) >> 24;
		if (REL::Module::IsVR() && !VRcompiledFileCollection) {
			if (rawIndex >= file->masterCount) {
				return 0;
			}
			auto* master = file->masterPtrs[rawIndex];
			return (a_rawFormID & 0x00FFFFFF) | (master->compileIndex << 24);
		} else {
			bool isLight = rawIndex == 0xFE;
			if (isLight) {
				rawIndex = (a_rawFormID & 0x00FFF000) >> 12;
			}
			std::uint32_t index = 0;
			for (std::uint32_t i = 0; i < file->masterCount; ++i) {
				auto* master = file->masterPtrs[i];
				if ((master->compileIndex == 0xFE) != isLight) {
					continue;
				}
				if (index++ == rawIndex) {
					return (a_rawFormID & 0x00FFFFFF) | (master->compileIndex << 24);
				}
			}
			return 0;
		}
	}

	const TESFile* TESDataHandler::LookupModByName(std::string_view a_modName)
	{
		for (auto& file : files) {
			if (a_modName.size() == strlen(file->fileName) &&
				_strnicmp(file->fileName, a_modName.data(), a_modName.size()) == 0) {
				return file;
			}
		}
		return nullptr;
	}

	std::optional<std::uint8_t> TESDataHandler::GetModIndex(std::string_view a_modName)
	{
		auto mod = LookupModByName(a_modName);
		return mod ? std::make_optional(mod->compileIndex) : std::nullopt;
	}

	const TESFile* TESDataHandler::LookupLoadedModByName(std::string_view a_modName)
	{
		auto  size = GetLoadedModCount();
		auto* file = GetLoadedMods();
		for (auto i = 0; i < size; ++i, ++file) {
			if (a_modName.size() == strlen((*file)->fileName) &&
				_strnicmp((*file)->fileName, a_modName.data(), a_modName.size()) == 0) {
				return *file;
			}
		}
		return nullptr;
	}

	const TESFile* TESDataHandler::LookupLoadedModByIndex(std::uint8_t a_index)
	{
		auto  size = GetLoadedModCount();
		auto* file = GetLoadedMods();
		for (auto i = 0; i < size; ++i, ++file) {
			if ((*file)->compileIndex == a_index) {
				return *file;
			}
		}
		return nullptr;
	}

	std::optional<std::uint8_t> TESDataHandler::GetLoadedModIndex(std::string_view a_modName)
	{
		auto mod = LookupLoadedModByName(a_modName);
		return mod ? std::make_optional(mod->compileIndex) : std::nullopt;
	}

	const TESFile* TESDataHandler::LookupLoadedLightModByName(std::string_view a_modName)
	{
		auto  size = GetLoadedLightModCount();
		auto* file = GetLoadedLightMods();
		for (auto i = 0; i < size; ++i, ++file) {
			if (a_modName.size() == strlen((*file)->fileName) &&
				_strnicmp((*file)->fileName, a_modName.data(), a_modName.size()) == 0) {
				return *file;
			}
		}
		return nullptr;
	}

	const TESFile* TESDataHandler::LookupLoadedLightModByIndex(std::uint16_t a_index)
	{
		auto  size = GetLoadedLightModCount();
		auto* file = GetLoadedLightMods();
		for (auto i = 0; i < size; ++i, ++file) {
			if ((*file)->smallFileCompileIndex == a_index) {
				return *file;
			}
		}
		return nullptr;
	}

	std::optional<std::uint16_t> TESDataHandler::GetLoadedLightModIndex(std::string_view a_modName)
	{
		auto mod = LookupLoadedLightModByName(a_modName);
		return mod ? std::make_optional(mod->smallFileCompileIndex) : std::nullopt;
	}

	bool TESDataHandler::IsGeneratedID(FormID a_formID)
	{
		return a_formID >= 0xFF000000;
	}

	BSTArray<TESForm*>& TESDataHandler::GetFormArray(FormType a_formType)
	{
		return formArrays[std::to_underlying(a_formType)];
	}

	ObjectRefHandle TESDataHandler::CreateReferenceAtLocation(TESBoundObject* a_base, const NiPoint3& a_location, const NiPoint3& a_rotation, TESObjectCELL* a_targetCell, TESWorldSpace* a_selfWorldSpace, TESObjectREFR* a_alreadyCreatedRef, BGSPrimitive* a_primitive, const ObjectRefHandle& a_linkedRoomRefHandle, bool a_forcePersist, bool a_arg11)
	{
		using func_t = decltype(&TESDataHandler::CreateReferenceAtLocation);
		REL::Relocation<func_t> func{ RELOCATION_ID(13625, 13723) };
		return func(this, a_base, a_location, a_rotation, a_targetCell, a_selfWorldSpace, a_alreadyCreatedRef, a_primitive, a_linkedRoomRefHandle, a_forcePersist, a_arg11);
	}
}
