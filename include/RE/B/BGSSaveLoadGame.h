#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"

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
		BSTHashMap<FormID, FormID> unk00;  // 00
		BSTHashMap<FormID, FormID> unk30;  // 30
		std::uint32_t              unk60;  // 60
		std::uint32_t              pad64;  // 64
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSSaveLoadFormIDMap) == 0x68);

	class BGSSaveLoadReferencesMap
	{
	public:
		// members
		BSTHashMap<FormID, FormID>                 unk00;  // 00
		BSTHashMap<FormID, BSTArray<FormID>>       unk30;  // 30
		BSTHashMap<FormID, BGSCellFormIDArrayMap*> unk60;  // 60
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSSaveLoadReferencesMap) == 0x90);

	class BGSConstructFormsInAllFilesMap
	{
	public:
		// members
		BSTHashMap<TESFile*, BGSConstructFormsInFileMap*> unk00;     // 00
		BSTArray<void*>                                   unk30[3];  // 30
		std::uint32_t                                     unk78;     // 78
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSConstructFormsInAllFilesMap) == 0x80);

	class BGSSaveLoadQueuedSubBufferMap
	{
	public:
		// members
		BSTHashMap<TESForm*, BGSLoadGameSubBuffer> queuedSubBuffers[3];  // 00
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSSaveLoadQueuedSubBufferMap) == 0x90);

	class BGSSaveLoadGame
	{
	public:
		enum class Flags
		{
			kGlobalAllowChanges = 1 << 0,
			kLoading = 1 << 1,
			kSaving = 1 << 2,
			kInitingForms = 1 << 3,
			kDeferInitForms = 1 << 4,
			kPositioningPlayer = 1 << 5,
			kPlayerLocationInvalid = 1 << 6
		};

		static BGSSaveLoadGame* GetSingleton()
		{
			REL::Relocation<BGSSaveLoadGame**> singleton{ RELOCATION_ID(516851, 403330) };
			return *singleton;
		}

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                 \
	BSTArray<TESFile*> pluginList; /* 000 */ \
	BSTArray<void*>    unk18;      /* 018 */
            RUNTIME_DATA_CONTENT
		};

		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT              \
	std::uint8_t pluginList[0xFF]; /* 000 */ \
	std::uint8_t unk18[0xFF];      /* 0FF */
			VR_RUNTIME_DATA_CONTENT
		};

		struct RUNTIME_DATA2
		{
#define RUNTIME_DATA2_CONTENT                                                 \
	BGSSaveLoadFormIDMap                   worldspaceFormIDMap; /*030, 1fe */ \
	BSTHashMap<FormID, ActorHandle>        unk98;               /*098*/       \
	BGSSaveLoadReferencesMap               unkC8;               /*0C8*/       \
	BSTHashMap<FormID, FormID>             unk158;              /*158*/       \
	BGSConstructFormsInAllFilesMap         reconstructFormsMap; /*188*/       \
	BGSSaveLoadQueuedSubBufferMap          queuedSubBuffersMap; /*208*/       \
	BGSSaveLoadFormIDMap                   formIDMap;           /*298*/       \
	BSTArray<void*>                        saveLoadHistory;     /*300*/       \
	BSTArray<void*>                        unk318;              /*318*/       \
	BGSSaveLoadChangesMap*                 saveLoadChanges;     /*330*/       \
	std::uint64_t                          unk338;              /*338*/       \
	stl::enumeration<Flags, std::uint32_t> flags;               /*340*/       \
	std::uint8_t                           currentMinorVersion; /*344 */
            RUNTIME_DATA2_CONTENT
		};

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x0, 0x0);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x0, 0x0);
		}

		[[nodiscard]] inline VR_RUNTIME_DATA& GetVRRuntimeData() noexcept
		{
			return REL::RelocateMember<VR_RUNTIME_DATA>(this, 0x0, 0x0);
		}

		[[nodiscard]] inline const VR_RUNTIME_DATA& GetVRRuntimeData() const noexcept
		{
			return REL::RelocateMember<VR_RUNTIME_DATA>(this, 0x0, 0x0);
		}

		[[nodiscard]] inline RUNTIME_DATA2& GetRuntimeData2() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA2>(this, 0x30, 0x1fe);
		}

		[[nodiscard]] inline const RUNTIME_DATA2& GetRuntimeData2() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA2>(this, 0x30, 0x1fe);
		}

		bool GetChange(TESForm* a_form, std::uint32_t a_changes)
		{
			using func_t = decltype(&BGSSaveLoadGame::GetChange);
			static REL::Relocation<func_t> func{ RELOCATION_ID(34655, 35577) };
			return func(this, a_form, a_changes);
		}

// members
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		RUNTIME_DATA_CONTENT;
		RUNTIME_DATA2_CONTENT;
#elif defined(EXCLUSIVE_SKYRIM_VR)
		VR_RUNTIME_DATA_CONTENT;
		RUNTIME_DATA2_CONTENT;
#endif
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(BGSSaveLoadGame) == 0x348);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BGSSaveLoadGame) == 0x518);
#else
	static_assert(sizeof(BGSSaveLoadGame) == 0x1);
#endif
}
#undef RUNTIME_DATA_CONTENT
#undef RUNTIME_DATA2_CONTENT
#undef VR_RUNTIME_DATA_CONTENT
