#pragma once

#include <atomic>

#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSSimpleList.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSingleton.h"
#include "RE/F/FormTypes.h"
#include "RE/I/InventoryChanges.h"
#include "RE/N/NiTArray.h"
#include "RE/N/NiTList.h"
#include "RE/T/TESForm.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BGSPrimitive;
	class InventoryChanges;
	class NiPoint3;
	class TESFile;
	class TESRegionDataManager;
	class TESRegionList;

	struct TESObjectList
	{
	public:
		// members
		std::uint8_t pad0;  // 0
	};
	static_assert(sizeof(TESObjectList) == 0x1);

	struct TESFileCollection
	{
	public:
		// members
		BSTArray<TESFile*> files;       // 00
		BSTArray<TESFile*> smallFiles;  // 18
	};
	static_assert(sizeof(TESFileCollection) == 0x30);

	class TESDataHandler : public BSTSingletonSDM<TESDataHandler>
	{
	public:
		inline static std::atomic<RE::TESFileCollection*> VRcompiledFileCollection{ nullptr };  // used by SkyrimVRESL to store pointer to VR version
		static TESDataHandler*                            GetSingleton(bool a_VRESL = true);
		[[nodiscard]] static TESFileCollection*           GetVRCompiledFileCollection(bool a_allowRefresh = true) noexcept;

		[[nodiscard]] static inline bool HasValidVRCompiledFileCollection(const TESFileCollection* a_collection) noexcept
		{
			if (!a_collection) {
				return false;
			}

			const auto address = reinterpret_cast<std::uintptr_t>(a_collection);
			return address > 0x10000 && (address % alignof(TESFileCollection) == 0);
		}

		bool AddFormToDataHandler(TESForm* a_form);

		std::uint32_t LoadScripts();
		TESForm*      LookupForm(FormID a_localFormID, std::string_view a_modName);
		TESForm*      LookupFormRaw(FormID a_rawFormID, std::string_view a_modName);
		template <class T>
		T* LookupForm(FormID a_localFormID, std::string_view a_modName);
		template <class T>
		T*     LookupFormRaw(FormID a_rawFormID, std::string_view a_modName);
		FormID LookupFormID(FormID a_localFormID, std::string_view a_modName);
		FormID LookupFormIDRaw(FormID a_rawFormID, std::string_view a_modName);

		const TESFile*              LookupModByName(std::string_view a_modName);
		std::optional<std::uint8_t> GetModIndex(std::string_view a_modName);

		const TESFile*              LookupLoadedModByName(std::string_view a_modName);
		const TESFile*              LookupLoadedModByIndex(std::uint8_t a_index);
		std::optional<std::uint8_t> GetLoadedModIndex(std::string_view a_modName);

		const TESFile*               LookupLoadedLightModByName(std::string_view a_modName);
		const TESFile*               LookupLoadedLightModByIndex(std::uint16_t a_index);
		std::optional<std::uint16_t> GetLoadedLightModIndex(std::string_view a_modName);

		TESWorldSpace* GetExtCellDataFromFileByEditorID(const char* a_cellID, std::int32_t& a_outX, std::int32_t& a_outY);

		bool   IsGeneratedID(FormID a_formID);
		FormID GetNextID();

		BSTArray<TESForm*>& GetFormArray(FormType a_formType);
		template <class T>
		BSTArray<T*>& GetFormArray();

		ObjectRefHandle CreateReferenceAtLocation(TESBoundObject* a_base, const NiPoint3& a_location, const NiPoint3& a_rotation, TESObjectCELL* a_targetCell, TESWorldSpace* a_selfWorldSpace, TESObjectREFR* a_alreadyCreatedRef, BGSPrimitive* a_primitive, const ObjectRefHandle& a_linkedRoomRefHandle, bool a_forcePersist, bool a_arg11);

		// Common runtime flags shared by SE/AE and VR (at different offsets)
		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT \
	bool masterSave;         \
	bool blockSave;          \
	bool saveLoadGame;       \
	bool autoSaving;         \
	bool exportingPlugin;    \
	bool clearingData;       \
	bool hasDesiredFiles;    \
	bool checkingModels;     \
	bool loadingFiles;       \
	bool dontRemoveIDs;

			RUNTIME_DATA_CONTENT
		};

		// Common trailing members shared by SE/AE and VR (at different offsets)
#define TRAILING_MEMBERS_CONTENT                                           \
	TESRegionDataManager* regionDataManager; /* DB0 (SE/AE) / 1580 (VR) */ \
	InventoryChanges*     merchantInventory; /* DB8 (SE/AE) / 1588 (VR) */

		RUNTIME_DATA_ACCESSOR_EX(RUNTIME_DATA, GetGeometryRuntimeData, 0xDA0, 0x1570);
		[[nodiscard]] inline TESFile** GetLoadedMods() noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsVR()) {
				const auto collection = GetVRCompiledFileCollection();
				return !HasValidVRCompiledFileCollection(collection) ? &REL::RelocateMember<TESFile*>(this, 0x0, 0xD78) : const_cast<TESFile**>(collection->files.data());
			} else {
				return REL::RelocateMember<TESFileCollection>(this, 0xD70, 0).files.data();
			}
		}

		[[nodiscard]] inline const TESFile* const* GetLoadedMods() const noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsVR()) {
				const auto collection = GetVRCompiledFileCollection();
				return !HasValidVRCompiledFileCollection(collection) ? &REL::RelocateMember<const TESFile*>(this, 0x0, 0xD78) : collection->files.data();
			} else {
				return REL::RelocateMember<const TESFileCollection>(this, 0xD70, 0).files.data();
			}
		}

		[[nodiscard]] inline std::uint8_t GetLoadedModCount() const noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsVR()) {
				const auto collection = GetVRCompiledFileCollection();
				return static_cast<std::uint8_t>(!HasValidVRCompiledFileCollection(collection) ? REL::RelocateMember<std::uint32_t>(this, 0x0, 0xD70) : collection->files.size());
			} else {
				return static_cast<std::uint8_t>(REL::RelocateMember<const TESFileCollection>(this, 0xD70, 0).files.size());
			}
		}

		[[nodiscard]] inline TESFile** GetLoadedLightMods() noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsVR()) {
				const auto collection = GetVRCompiledFileCollection();
				return !HasValidVRCompiledFileCollection(collection) ? nullptr : const_cast<TESFile**>(collection->smallFiles.data());
			} else {
				return REL::RelocateMember<TESFileCollection>(this, 0xD70, 0).smallFiles.data();
			}
		}

		[[nodiscard]] inline const TESFile* const* GetLoadedLightMods() const noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsVR()) {
				const auto collection = GetVRCompiledFileCollection();
				return !HasValidVRCompiledFileCollection(collection) ? nullptr : collection->smallFiles.data();
			} else {
				return REL::RelocateMember<const TESFileCollection>(this, 0xD70, 0).smallFiles.data();
			}
		}

		[[nodiscard]] inline std::uint16_t GetLoadedLightModCount() const noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsVR()) {
				const auto collection = GetVRCompiledFileCollection();
				return (!HasValidVRCompiledFileCollection(collection)) ? 0 : static_cast<std::uint16_t>(collection->smallFiles.size());
			} else {
				return static_cast<std::uint16_t>(REL::RelocateMember<const TESFileCollection>(this, 0xD70, 0).smallFiles.size());
			}
		}

		RUNTIME_DATA_ACCESSOR_EX(std::uint8_t, GetGameSettingsLoadState, 0xDAA, 0x157A)

		RUNTIME_DATA_POINTER_ACCESSOR_EX(TESRegionDataManager*, GetRegionDataManager, 0xDB0, 0x1580);

		RUNTIME_DATA_POINTER_ACCESSOR_EX(InventoryChanges*, GetMerchantInventory, 0xDB8, 0x1588);

		// members
		std::uint8_t                      pad001;                                         // 001
		std::uint16_t                     pad002;                                         // 002
		std::uint32_t                     pad004;                                         // 004
		TESObjectList*                    objectList;                                     // 008
		BSTArray<TESForm*>                formArrays[std::to_underlying(FormType::Max)];  // 010
		TESRegionList*                    regionList;                                     // D00
		NiTPrimitiveArray<TESObjectCELL*> interiorCells;                                  // D08
		NiTPrimitiveArray<BGSAddonNode*>  addonNodes;                                     // D20
		NiTList<TESForm*>                 badForms;                                       // D38
		FormID                            nextID;                                         // D50
		std::uint32_t                     padD54;                                         // D54
		TESFile*                          activeFile;                                     // D58
		BSSimpleList<TESFile*>            files;                                          // D60
#if !defined(SKYRIM_CROSS_VR)
#	if defined(EXCLUSIVE_SKYRIM_FLAT)
		TESFileCollection compiledFileCollection;  // D70
		RUNTIME_DATA_CONTENT
		std::uint8_t  gameSettingsLoadState;  // DAA
		std::uint8_t  padDAB;                 // DAB
		std::uint32_t padDAC;                 // DAC
		TRAILING_MEMBERS_CONTENT
#	elif defined(EXCLUSIVE_SKYRIM_VR)
		std::uint32_t loadedModCount;    // D70 this should be avoided if SkyrimVRESL is available
		std::uint32_t pad14;             // D74
		TESFile*      loadedMods[0xFF];  // D78 this should be avoided if SkyrimVRESL is available
		RUNTIME_DATA_CONTENT
		std::uint8_t gameSettingsLoadState;  // 157A
		std::uint8_t pad157B[4];             // 157B
		TRAILING_MEMBERS_CONTENT
#	endif
#endif
	};

	template <class T>
	T* TESDataHandler::LookupForm(FormID a_localFormID, std::string_view a_modName)
	{
		auto form = LookupForm(a_localFormID, a_modName);
		if (!form) {
			return 0;
		}

		return form->Is(T::FORMTYPE) ? static_cast<T*>(form) : 0;
	}

	template <class T>
	T* TESDataHandler::LookupFormRaw(FormID a_rawFormID, std::string_view a_modName)
	{
		auto form = LookupFormRaw(a_rawFormID, a_modName);
		if (!form) {
			return 0;
		}

		return form->Is(T::FORMTYPE) ? static_cast<T*>(form) : 0;
	}

	template <class T>
	BSTArray<T*>& TESDataHandler::GetFormArray()
	{
		return reinterpret_cast<BSTArray<T*>&>(GetFormArray(T::FORMTYPE));
	}
}

#undef RUNTIME_DATA_CONTENT
#undef TRAILING_MEMBERS_CONTENT
