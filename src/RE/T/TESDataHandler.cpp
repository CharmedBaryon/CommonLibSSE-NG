#include "RE/T/TESDataHandler.h"

#include "RE/T/TESFile.h"
#include "RE/T/TESForm.h"

#include "REX/W32/BASE.h"
#include <atomic>
#include <chrono>
#undef GetModuleHandle

namespace RE
{
	namespace
	{
		using GetCompiledFileCollection_t = const RE::TESFileCollection* (*)();

		inline std::atomic<GetCompiledFileCollection_t> g_getCompiledFileCollectionExtern{ nullptr };
		inline std::atomic<std::uint64_t>               g_nextVRESLProbeTimeMs{ 0 };
		constexpr std::uint64_t                         kVRESLProbeIntervalMs = 5000;

		[[nodiscard]] std::uint64_t GetMonotonicMs() noexcept
		{
			using namespace std::chrono;
			return static_cast<std::uint64_t>(duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count());
		}

		[[nodiscard]] GetCompiledFileCollection_t ResolveGetCompiledFileCollectionExtern() noexcept
		{
			auto getter = g_getCompiledFileCollectionExtern.load(std::memory_order_acquire);
			if (getter) {
				return getter;
			}

			const auto vreslModule = REX::W32::GetModuleHandleW(L"skyrimvresl");
			if (vreslModule == NULL) {
				return nullptr;
			}

			getter = reinterpret_cast<GetCompiledFileCollection_t>(REX::W32::GetProcAddress(vreslModule, "GetCompiledFileCollectionExtern"));
			if (getter) {
				g_getCompiledFileCollectionExtern.store(getter, std::memory_order_release);
			}

			return getter;
		}
	}

	TESFileCollection* TESDataHandler::GetVRCompiledFileCollection(bool a_allowRefresh) noexcept
	{
		if (!REL::Module::IsVR()) {
			return nullptr;
		}

		auto collection = VRcompiledFileCollection.load(std::memory_order_acquire);
		if (HasValidVRCompiledFileCollection(collection)) {
			return collection;
		}

		VRcompiledFileCollection.compare_exchange_strong(collection, nullptr, std::memory_order_release, std::memory_order_relaxed);

		if (!a_allowRefresh) {
			return nullptr;
		}

		const auto now = GetMonotonicMs();
		auto       nextProbeTime = g_nextVRESLProbeTimeMs.load(std::memory_order_acquire);
		if (now < nextProbeTime) {
			return nullptr;
		}

		const auto desiredNextProbeTime = now + kVRESLProbeIntervalMs;
		if (!g_nextVRESLProbeTimeMs.compare_exchange_strong(nextProbeTime, desiredNextProbeTime, std::memory_order_acq_rel, std::memory_order_acquire) && now < nextProbeTime) {
			return nullptr;
		}

		const auto getter = ResolveGetCompiledFileCollectionExtern();
		if (!getter) {
			return nullptr;
		}

		collection = const_cast<TESFileCollection*>(getter());
		if (!HasValidVRCompiledFileCollection(collection)) {
			return nullptr;
		}

		VRcompiledFileCollection.store(collection, std::memory_order_release);
		return collection;
	}

	TESDataHandler* TESDataHandler::GetSingleton(bool a_VRESL)
	{
		static REL::Relocation<TESDataHandler**> singleton{ RELOCATION_ID(514141, 400269) };
		if (a_VRESL && REL::Module::IsVR()) {
			(void)GetVRCompiledFileCollection(true);
		}
		return *singleton;
	}

	bool TESDataHandler::AddFormToDataHandler(TESForm* a_form)
	{
		using func_t = decltype(&TESDataHandler::AddFormToDataHandler);
		static REL::Relocation<func_t> func{ RELOCATION_ID(13597, 13693) };
		return func(this, a_form);
	}

	std::uint32_t TESDataHandler::LoadScripts()
	{
		using func_t = decltype(&TESDataHandler::LoadScripts);
		static REL::Relocation<func_t> func{ RELOCATION_ID(13657, 13766) };
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

		if (REL::Module::IsVR() && !HasValidVRCompiledFileCollection(GetVRCompiledFileCollection(false))) {
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
		if (REL::Module::IsVR() && !HasValidVRCompiledFileCollection(GetVRCompiledFileCollection(false))) {
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

	TESWorldSpace* TESDataHandler::GetExtCellDataFromFileByEditorID(const char* a_cellID, std::int32_t& a_outX, std::int32_t& a_outY)
	{
		using func_t = decltype(&TESDataHandler::GetExtCellDataFromFileByEditorID);
		static REL::Relocation<func_t> func{ RELOCATION_ID(13618, 13716) };
		return func(this, a_cellID, a_outX, a_outY);
	}

	bool TESDataHandler::IsGeneratedID(FormID a_formID)
	{
		return a_formID >= 0xFF000000;
	}

	FormID TESDataHandler::GetNextID()
	{
		using func_t = decltype(&TESDataHandler::GetNextID);
		static REL::Relocation<func_t> func{ RELOCATION_ID(13635, 13740) };
		return func(this);
	}

	BSTArray<TESForm*>& TESDataHandler::GetFormArray(FormType a_formType)
	{
		return formArrays[std::to_underlying(a_formType)];
	}

	ObjectRefHandle TESDataHandler::CreateReferenceAtLocation(TESBoundObject* a_base, const NiPoint3& a_location, const NiPoint3& a_rotation, TESObjectCELL* a_targetCell, TESWorldSpace* a_selfWorldSpace, TESObjectREFR* a_alreadyCreatedRef, BGSPrimitive* a_primitive, const ObjectRefHandle& a_linkedRoomRefHandle, bool a_forcePersist, bool a_arg11)
	{
		using func_t = decltype(&TESDataHandler::CreateReferenceAtLocation);
		static REL::Relocation<func_t> func{ RELOCATION_ID(13625, 13723) };
		return func(this, a_base, a_location, a_rotation, a_targetCell, a_selfWorldSpace, a_alreadyCreatedRef, a_primitive, a_linkedRoomRefHandle, a_forcePersist, a_arg11);
	}
}
