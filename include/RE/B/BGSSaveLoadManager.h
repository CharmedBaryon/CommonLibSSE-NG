#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTMessageQueue.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/B/BSThread.h"
#include "RE/R/RaceSexMenuEvent.h"
#include "RE/R/Request.h"
#include "REL/RuntimeDataAccessors.h"
#include <SKSE/Version.h>

namespace RE
{
	class BSSaveDataEvent;
	class BSSystemEvent;
	struct BGSSaveLoadManagerEvent;

	class BGSSaveLoadFileEntry
	{
	public:
		enum class SaveType
		{
			kAutosave = 0x0,
			kSave = 0x1,
			kQuicksave = 0x2,
			kCustom = 0x3
		};

		bool PopulateFileEntryData();

		// members
		BSFixedString                         fileName;            // 00
		BSFixedString                         characterName;       // 08
		BSFixedString                         characterTitle;      // 10
		BSFixedString                         currentLocation;     // 18
		BSFixedString                         playTime;            // 20
		BSFixedString                         characterRace;       // 28
		std::int32_t                          saveVersion;         // 30
		std::uint32_t                         saveNumber;          // 34
		std::uint32_t                         characterLevel;      // 38
		float                                 currentExperience;   // 3C
		float                                 requiredExperience;  // 40
		std::uint32_t                         screenshotWidth;     // 44
		std::uint32_t                         screenshotHeight;    // 48
		std::uint32_t                         unk4C;               // 4C
		REX::W32::FILETIME                    fileTime;            // 50
		REX::W32::FILETIME                    saveTime;            // 58
		std::int32_t                          unk60;               // 60
		bool                                  loaded;              // 64
		bool                                  unk65;               // 65
		bool                                  unk66;               // 66
		std::uint8_t                          unk67;               // 67
		std::uint8_t                          unk68;               // 68
		bool                                  modded;              // 69
		std::uint16_t                         pad6A;               // 6A
		std::uint32_t                         characterID;         // 6C
		REX::EnumSet<SaveType, std::uint32_t> saveType;            // 70
		std::uint32_t                         pad74;               // 74
	};
	static_assert(sizeof(BGSSaveLoadFileEntry) == 0x78);

	class BGSSaveLoadManager :
		public BSTEventSink<BSSaveDataEvent>,                     // 000
		public BSTEventSink<RaceSexMenuEvent::NameChangedEvent>,  // 008
		public BSTEventSource<BGSSaveLoadManagerEvent>,           // 018
		public BSTEventSink<BSSystemEvent>                        // 010
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSSaveLoadManager;
		inline static constexpr auto VTABLE = VTABLE_BGSSaveLoadManager;

		class Thread : public BSThread
		{
		public:
			inline static constexpr auto RTTI = RTTI_BGSSaveLoadManager__Thread;
			inline static constexpr auto VTABLE = VTABLE_BGSSaveLoadManager__Thread;

			~Thread() override;  // 00

			std::uint32_t ThreadProc() override;  // 01
			void          Unk_02(void) override;  // 02

			// members
			bool                                                                    isRunnning;                   // 50
			bool                                                                    isBusy;                       // 51
			std::uint16_t                                                           pad52;                        // 52
			std::uint32_t                                                           pad54;                        // 54
			BSEventFlag                                                             haveTask;                     // 58
			BSTCommonStaticMessageQueue<BSTSmartPointer<bgs::saveload::Request>, 8> asyncSaveLoadOperationQueue;  // 60
		};
		static_assert(sizeof(Thread) == 0xC0);

		struct SaveEntry
		{
			std::uint32_t                            characterID;      // 00
			std::uint32_t                            isModded;         // 04
			std::uint32_t                            manualSaveCount;  // 08
			std::uint32_t                            autoSaveCount;    // 0C
			BSTHashMap<std::uint32_t, BSFixedString> autoSaves;        // 18
			BSFixedString                            lastQuicksave;    // 40
		};
		static_assert(sizeof(SaveEntry) == 0x48);

		~BGSSaveLoadManager() override;  // 00

		// override (BSTEventSink<BSSaveDataEvent>)
		BSEventNotifyControl ProcessEvent(const BSSaveDataEvent* a_event, BSTEventSource<BSSaveDataEvent>* a_eventSource) override;  // 01

		// override (BSTEventSink<RaceSexMenuEvent::NameChangedEvent>)
		BSEventNotifyControl ProcessEvent(const RaceSexMenuEvent::NameChangedEvent* a_event, BSTEventSource<RaceSexMenuEvent::NameChangedEvent>* a_eventSource) override;  // 01

		// override (BSTEventSink<BSSystemEvent>)
		BSEventNotifyControl ProcessEvent(const BSSystemEvent* a_event, BSTEventSource<BSSystemEvent>* a_eventSource) override;  // 01

		static BGSSaveLoadManager* GetSingleton();

		void GenerateCharacterID();
		void Save(const char* a_fileName);
		void Load(const char* a_fileName);
		void Load(const char* a_fileName, bool a_checkForMods);
		bool LoadMostRecentSaveGame();
		bool PopulateSaveList();

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                  \
	Thread                                                                  thread; /* 2B0 */ \
	BSTCommonStaticMessageQueue<BSTSmartPointer<bgs::saveload::Request>, 8> unk370; /* 370 */ \
	uint64_t                                                                unk3D0; /* 3D0 */
            RUNTIME_DATA_CONTENT
		};

		// 1130 and later
		struct AE_RUNTIME_DATA
		{
#define AE_RUNTIME_DATA_CONTENT                                                                                                                                   \
	std::uint16_t                                                           unk2B0;           /* 2B0 */                                                           \
	std::uint16_t                                                           unk2B2;           /* 2B2 */                                                           \
	BGSSaveLoadFileEntry*                                                   pendingSaveEntry; /* 2B8 - single cached/pending entry, separate from saveGameList */ \
	BSTArray<BSFixedString>                                                 unk2C0;           /* 2C0 */                                                           \
	BSTArray<BSFixedString>                                                 unk2D8;           /* 2D8 */                                                           \
	std::uint8_t                                                            unk2F0;           /* 2F0 */                                                           \
	Thread                                                                  thread;           /* 2F8 */                                                           \
	BSTCommonStaticMessageQueue<BSTSmartPointer<bgs::saveload::Request>, 8> unk370;           /* 370 */                                                           \
	uint64_t                                                                unk3D0;           /* 3D0 */
            AE_RUNTIME_DATA_CONTENT
		};
		static_assert(offsetof(AE_RUNTIME_DATA, thread) == 0x48);

		RUNTIME_DATA_ACCESSOR_VERSIONED(RUNTIME_DATA, SKSE::RUNTIME_SSE_1_6_1130, 0x2b0, 0x2f8);
		AE_ONLY_POINTER_ACCESSOR_VERSIONED(AE_RUNTIME_DATA, GetAERuntimeData, SKSE::RUNTIME_SSE_1_6_1130, 0x2b0);

		// members
		BSTHashMap<std::uint64_t, BSFixedString> characterIDNameMap;      // 078
		std::uint64_t                            unk0A0;                  // 0A0
		std::uint32_t                            unk0A8;                  // 0A8
		std::uint32_t                            unk0AC;                  // 0AC
		std::uint32_t                            unk0B0;                  // 0B0
		std::uint32_t                            unk0B4;                  // 0B4
		std::uint64_t                            unk0B8;                  // 0B8
		std::uint64_t                            unk0C0;                  // 0C0
		std::uint64_t                            unk0C8;                  // 0C8
		std::uint32_t                            currentCharacterID;      // 0D0
		std::uint32_t                            currentCharacterModded;  // 0D4
		std::uint32_t                            displayCharacterID;      // 0D8
		std::uint32_t                            displayCharacterModded;  // 0DC
		std::uint32_t                            unk0E0;                  // 0E0
		std::uint32_t                            unk0E4;                  // 0E4
		BSTArray<SaveEntry>                      loadedEntries;           // 0E8

		BSTArray<BGSSaveLoadFileEntry*> saveGameList;             // 100
		std::uint8_t                    unk118;                   // 118
		std::uint8_t                    pad119;                   // 119
		std::uint16_t                   pad11A;                   // 11A
		std::uint32_t                   saveCount;                // 11C
		std::uint8_t                    unk120;                   // 120
		std::uint8_t                    pad121;                   // 121
		std::uint16_t                   pad122;                   // 122
		std::uint32_t                   pad124;                   // 124
		std::uint64_t                   tickCount;                // 128
		std::uint8_t                    unk130;                   // 130
		std::uint8_t                    pad131;                   // 131
		std::uint16_t                   pad132;                   // 132
		std::uint32_t                   pad134;                   // 134
		const char                      lastFileFullName[0x104];  // 138
		std::uint32_t                   pad23C;                   // 23C
		BSFixedString                   lastFileName;             // 240
		std::uint16_t                   lastFileNameLength;       // 248
		std::uint16_t                   maxFileNameLength;        // 24A
		std::uint32_t                   unk24C;                   // 24C
		std::int32_t                    unk250;                   // 250
		std::uint32_t                   pad254;                   // 254
		std::uint64_t                   unk258;                   // 258
		std::uint16_t                   unk260;                   // 260
		std::uint16_t                   unk262;                   // 262
		std::uint32_t                   unk264;                   // 264
		std::uint64_t                   unk268;                   // 268
		std::uint32_t                   unk270;                   // 270
		std::uint32_t                   unk274;                   // 274
		std::uint64_t                   unk278;                   // 278
		std::uint64_t                   unk280;                   // 280
		std::uint32_t                   unk288;                   // 288
		std::uint32_t                   unk28C;                   // 28C
		std::uint64_t                   unk290;                   // 290
		std::uint64_t                   unk298;                   // 298
		std::uint32_t                   unk2A0;                   // 2A0
		std::uint32_t                   unk2A4;                   // 2A4
		std::uint64_t                   unk2A8;                   // 2A8
#if defined(EXCLUSIVE_SKYRIM_AE)                                  // AE 1130 specific change
		std::uint16_t           unk2B0;                           // 2B0
		std::uint16_t           unk2B2;                           // 2B2
		BGSSaveLoadFileEntry*   pendingSaveEntry;                 // 2B8
		BSTArray<BSFixedString> unk2C0;                           // 2C0
		BSTArray<BSFixedString> unk2D8;                           // 2D8
		std::uint8_t            unk2F0;                           // 2F0
#endif
#if !defined(SKYRIM_CROSS_VR)
		RUNTIME_DATA_CONTENT;
#endif
	protected:
		bool Save_Impl(std::int32_t a_deviceID, std::uint32_t a_outputStats, const char* a_fileName);
		bool Load_Impl(const char* a_fileName, std::int32_t a_deviceID, std::uint32_t a_outputStats, bool a_checkForMods);
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
#	if defined(EXCLUSIVE_SKYRIM_AE)
	static_assert(sizeof(BGSSaveLoadManager) == 0x420);
#	else
	static_assert(sizeof(BGSSaveLoadManager) == 0x3D8);
#	endif
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BGSSaveLoadManager) == 0x3D8);
#else
	static_assert(sizeof(BGSSaveLoadManager) == 0x2B0);
#endif
}

#undef RUNTIME_DATA_CONTENT
#undef AE_RUNTIME_DATA_CONTENT