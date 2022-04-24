#include "RE/T/TESDataHandler.h"

#include "RE/T/TESFile.h"
#include "RE/T/TESForm.h"

namespace RE
{
	TESDataHandler* TESDataHandler::GetSingleton()
	{
		REL::Relocation<TESDataHandler**> singleton{ Offset::TESDataHandler::Singleton };
		return *singleton;
	}

	std::uint32_t TESDataHandler::LoadScripts()
	{
		using func_t = decltype(&TESDataHandler::LoadScripts);
		REL::Relocation<func_t> func{ Offset::TESDataHandler::LoadScripts };
		return func(this);
	}

	TESForm* TESDataHandler::LookupForm(FormID a_rawFormID, std::string_view a_modName)
	{
		auto file = LookupModByName(a_modName);
		if (!file || file->compileIndex == 0xFF) {
			return nullptr;
		}

		if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
			// Use SkyrimVR lookup logic, ignore light plugin index which doesn't exist in VR
			return TESForm::LookupByID((a_rawFormID & 0xFFFFFF) | (file->compileIndex << 24));
		} else {
			FormID formID = file->compileIndex << (3 * 8);
			formID += file->smallFileCompileIndex << ((1 * 8) + 4);
			formID += a_rawFormID;

			return TESForm::LookupByID(formID);
		}
	}

	FormID TESDataHandler::LookupFormID(FormID a_rawFormID, std::string_view a_modName)
	{
		auto file = LookupModByName(a_modName);
		if (!file || file->compileIndex == 0xFF) {
			return 0;
		}

		FormID formID = file->compileIndex << (3 * 8);
		formID += file->smallFileCompileIndex << ((1 * 8) + 4);
		formID += a_rawFormID;

		return formID;
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
		for (auto& file : compiledFileCollection.files) {
			if (a_modName.size() == strlen(file->fileName) &&
				_strnicmp(file->fileName, a_modName.data(), a_modName.size()) == 0) {
				return file;
			}
		}
		return nullptr;
	}

	const TESFile* TESDataHandler::LookupLoadedModByIndex(std::uint8_t a_index)
	{
		for (auto& file : compiledFileCollection.files) {
			if (file->compileIndex == a_index) {
				return file;
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
		for (auto& smallFile : compiledFileCollection.smallFiles) {
			if (a_modName.size() == strlen(smallFile->fileName) &&
				_strnicmp(smallFile->fileName, a_modName.data(), a_modName.size()) == 0) {
				return smallFile;
			}
		}
		return nullptr;
	}

	const TESFile* TESDataHandler::LookupLoadedLightModByIndex(std::uint16_t a_index)
	{
		for (auto& smallFile : compiledFileCollection.smallFiles) {
			if (smallFile->smallFileCompileIndex == a_index) {
				return smallFile;
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
		return formArrays[stl::to_underlying(a_formType)];
	}

	ObjectRefHandle TESDataHandler::CreateReferenceAtLocation(TESBoundObject* a_base, const NiPoint3& a_location, const NiPoint3& a_rotation, TESObjectCELL* a_targetCell, TESWorldSpace* a_selfWorldSpace, TESObjectREFR* a_alreadyCreatedRef, BGSPrimitive* a_primitive, const ObjectRefHandle& a_linkedRoomRefHandle, bool a_forcePersist, bool a_arg11)
	{
		using func_t = decltype(&TESDataHandler::CreateReferenceAtLocation);
		REL::Relocation<func_t> func{ REL::RelocationID(13625, 13723) };
		return func(this, a_base, a_location, a_rotation, a_targetCell, a_selfWorldSpace, a_alreadyCreatedRef, a_primitive, a_linkedRoomRefHandle, a_forcePersist, a_arg11);
	}
}
