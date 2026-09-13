#pragma once

#include "RE/B/BGSConstructFormsInAllFilesMap.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/T/TESDataHandler.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BGSCellFormIDArrayMap;
	class BGSConstructFormsInFileMap;
	class BGSSaveLoadChangesMap;
	class TESFile;
	class TESForm;
	struct BGSLoadGameSubBuffer;

	class BGSSaveLoadFormIDMap
	{
	public:
		// members
		BSTHashMap<FormID, std::uint32_t> formIDToIndex;  // 00
		BSTHashMap<std::uint32_t, FormID> indexToFormID;  // 30
		std::uint32_t                     nextIndex;      // 60
		std::uint32_t                     pad64;          // 64
	};
	static_assert(sizeof(BGSSaveLoadFormIDMap) == 0x68);

	class BGSCellNumericIDArrayMap : public BSTHashMap<FormID, BSTArray<FormID>>
	{
	};
	static_assert(sizeof(BGSCellNumericIDArrayMap) == 0x30);

	class BGSSaveLoadReferencesMap
	{
	public:
		// members
		BSTHashMap<FormID, FormID>                           movedReferences;  // 00
		BGSCellNumericIDArrayMap                             cellReferences;   // 30 - interior or sky cells
		BSTHashMap<std::uint32_t, BGSCellNumericIDArrayMap*> worldReferences;  // 60 - grid X/Y packed into 32 bit key
	};
	static_assert(sizeof(BGSSaveLoadReferencesMap) == 0x90);

	struct QUEUED_SUB_BUFFER_TYPES
	{
		enum QUEUED_SUB_BUFFER_TYPE
		{
			kUnk0,
			kUnk1,
			kUnk2,

			kTotal
		};
	};
	using QUEUED_SUB_BUFFER_TYPE = QUEUED_SUB_BUFFER_TYPES::QUEUED_SUB_BUFFER_TYPE;

	class BGSSaveLoadQueuedSubBufferMap
	{
	public:
		BSTHashMap<TESForm*, BGSLoadGameSubBuffer> maps[QUEUED_SUB_BUFFER_TYPES::kTotal];
	};
	static_assert(sizeof(BGSSaveLoadQueuedSubBufferMap) == 0x90);

	class BGSSaveLoadHistory
	{
	public:
		// members
		BSTArray<const char*> notes;  // 00
	};
	static_assert(sizeof(BGSSaveLoadHistory) == 0x18);

	class BGSSaveLoadGame
	{
	public:
		enum class GlobalFlags
		{
			kGlobalAllowChanges = 1 << 0,
			kSaveGameLoading = 1 << 1,
			kSaveGameSaving = 1 << 2,
			kInitingForms = 1 << 3,
			kDeferInitForms = 1 << 4,
			kPositioningPlayerCharacter = 1 << 5,
			kPlayerLocationInvalid = 1 << 6
		};

		static BGSSaveLoadGame* GetSingleton()
		{
			static REL::Relocation<BGSSaveLoadGame**> singleton{ RELOCATION_ID(516851, 403330) };
			return *singleton;
		}

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT \
	TESFileCollection savedFiles; /* 000 */
			RUNTIME_DATA_CONTENT
		};

		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT                                                                                    \
	std::uint8_t saveToLoadOrderIndex[0xFF]; /* 000 - save index -> current load-order index, 0xFF if not found */ \
	std::uint8_t loadOrderToSaveIndex[0xFF]; /* 0FF - reverse: load-order index -> save index */
			VR_RUNTIME_DATA_CONTENT
		};

		struct RUNTIME_DATA2
		{
#define RUNTIME_DATA2_CONTENT                                                          \
	BGSSaveLoadFormIDMap                     worldspaceFormIDMap;        /*030, 1fe */ \
	BSTHashMap<std::uint32_t, ActorHandle>   queuedInitPackageLocations; /*098*/       \
	BGSSaveLoadReferencesMap                 references;                 /*0C8*/       \
	BSTHashMap<FormID, FormID>               changedFormIDs;             /*158*/       \
	BGSConstructFormsInAllFilesMap           reconstructFormsMap;        /*188*/       \
	BGSSaveLoadQueuedSubBufferMap            queuedSubBuffersMap;        /*208*/       \
	BGSSaveLoadFormIDMap                     formIDMap;                  /*298*/       \
	BGSSaveLoadHistory                       history;                    /*300*/       \
	BSTArray<BGSLoadFormData*>               loadFormData;               /*318*/       \
	BGSSaveLoadChangesMap*                   saveLoadChanges;            /*330*/       \
	BGSSaveLoadChangesMap*                   oldChangesMap;              /*338*/       \
	REX::EnumSet<GlobalFlags, std::uint32_t> globalFlags;                /*340*/       \
	std::uint8_t                             currentMinorVersion;        /*344 */
            RUNTIME_DATA2_CONTENT
		};

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x0, 0x0);
		VR_RUNTIME_DATA_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x0);
		RUNTIME_DATA_ACCESSOR_EX(RUNTIME_DATA2, GetRuntimeData2, 0x30, 0x1fe);
		[[nodiscard]] bool GetGlobalAllowChanges() const noexcept { return GetRuntimeData2().globalFlags.all(GlobalFlags::kGlobalAllowChanges); }
		[[nodiscard]] bool GetSaveGameLoading() const noexcept { return GetRuntimeData2().globalFlags.all(GlobalFlags::kSaveGameLoading); }
		[[nodiscard]] bool GetSaveGameSaving() const noexcept { return GetRuntimeData2().globalFlags.all(GlobalFlags::kSaveGameSaving); }
		[[nodiscard]] bool GetInitingForms() const noexcept { return GetRuntimeData2().globalFlags.all(GlobalFlags::kInitingForms); }
		[[nodiscard]] bool GetDeferInitForms() const noexcept { return GetRuntimeData2().globalFlags.all(GlobalFlags::kDeferInitForms); }
		[[nodiscard]] bool GetPositioningPlayerCharacter() const noexcept { return GetRuntimeData2().globalFlags.all(GlobalFlags::kPositioningPlayerCharacter); }

		bool GetChange(TESForm* a_form, std::uint32_t a_changes)
		{
			using func_t = decltype(&BGSSaveLoadGame::GetChange);
			static REL::Relocation<func_t> func{ RELOCATION_ID(34655, 35577) };
			return func(this, a_form, a_changes);
		}

		bool IsFormIDInUse(FormID a_formID)
		{
			using func_t = decltype(&BGSSaveLoadGame::IsFormIDInUse);
			static REL::Relocation<func_t> func{ RELOCATION_ID(34670, 35593) };
			return func(this, a_formID);
		}

// members
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		RUNTIME_DATA_CONTENT;
		RUNTIME_DATA2_CONTENT;
#elif defined(EXCLUSIVE_SKYRIM_VR)
		VR_RUNTIME_DATA_CONTENT;
		RUNTIME_DATA2_CONTENT;
#endif
	};
	STATIC_ASSERT_SIZE(BGSSaveLoadGame, 0x348, 0x348, 0x518, 0x1);
}
#undef RUNTIME_DATA_CONTENT
#undef RUNTIME_DATA2_CONTENT
#undef VR_RUNTIME_DATA_CONTENT
