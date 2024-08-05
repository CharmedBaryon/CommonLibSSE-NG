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
#include <SKSE/Version.h>

namespace RE
{
	class BSSaveDataEvent;
	class BSSystemEvent;
	struct BGSSaveLoadManagerEvent;

	class BGSSaveLoadFileEntry
	{
	public:
		// members
		BSFixedString fileName;     // 00
		BSFixedString playerName;   // 08
		BSFixedString playerTitle;  // 10
		BSFixedString location;     // 18
		BSFixedString playTime;     // 20
		BSFixedString raceName;     // 28
		std::uint32_t unk30;        // 30
		std::uint32_t unk34;        // 34
		std::uint32_t unk38;        // 38
		std::uint32_t unk3C;        // 3C
		std::uint32_t unk40;        // 40
		std::uint32_t unk44;        // 44
		std::uint64_t unk48;        // 48
		std::uint64_t unk50;        // 50
		std::uint64_t unk58;        // 58
		std::uint64_t unk60;        // 60
		std::uint64_t unk68;        // 68
		std::uint64_t unk70;        // 70
	private:
		KEEP_FOR_RE()
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

			void Unk_01(void) override;  // 01
			void Unk_02(void) override;  // 02

			// members
			bool                                                                    isRunnning;                   // 50
			bool                                                                    isBusy;                       // 51
			std::uint16_t                                                           pad52;                        // 52
			std::uint32_t                                                           pad54;                        // 54
			BSEventFlag                                                             haveTask;                     // 58
			BSTCommonStaticMessageQueue<BSTSmartPointer<bgs::saveload::Request>, 8> asyncSaveLoadOperationQueue;  // 60
		};
		static_assert(sizeof(Thread) == 0xC0);

		~BGSSaveLoadManager() override;  // 00

		// override (BSTEventSink<BSSaveDataEvent>)
		BSEventNotifyControl ProcessEvent(const BSSaveDataEvent* a_event, BSTEventSource<BSSaveDataEvent>* a_eventSource) override;  // 01

		// override (BSTEventSink<RaceSexMenuEvent::NameChangedEvent>)
		BSEventNotifyControl ProcessEvent(const RaceSexMenuEvent::NameChangedEvent* a_event, BSTEventSource<RaceSexMenuEvent::NameChangedEvent>* a_eventSource) override;  // 01

		// override (BSTEventSink<BSSystemEvent>)
		BSEventNotifyControl ProcessEvent(const BSSystemEvent* a_event, BSTEventSource<BSSystemEvent>* a_eventSource) override;  // 01

		static BGSSaveLoadManager* GetSingleton();

		void Save(const char* a_fileName);
		void Load(const char* a_fileName);
		void Load(const char* a_fileName, bool a_checkForMods);
		bool PopulateSaveList();

		bool LoadMostRecentSaveGame();

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
#define AE_RUNTIME_DATA_CONTENT                                                               \
	std::uint16_t                                                           unk2B0; /* 2B0 */ \
	std::uint16_t                                                           unk2B2; /* 2B2 */ \
	std::uint64_t                                                           unk2B8; /* 2B8 */ \
	BSTArray<void*>                                                         unk2C0; /* 2C0 */ \
	BSTArray<void*>                                                         unk2D8; /* 2D8 */ \
	std::uint8_t                                                            unk2F0; /* 2F0 */ \
	Thread                                                                  thread; /* 2F8 */ \
	BSTCommonStaticMessageQueue<BSTSmartPointer<bgs::saveload::Request>, 8> unk370; /* 370 */ \
	uint64_t                                                                unk3D0; /* 3D0 */
            AE_RUNTIME_DATA_CONTENT
		};
		static_assert(offsetof(AE_RUNTIME_DATA, thread) == 0x48);

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMemberIfNewer<RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_1130, this, 0x2b0, 0x2f8);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMemberIfNewer<RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_1130, this, 0x2b0, 0x2f8);
		}

		[[nodiscard]] inline AE_RUNTIME_DATA* GetAERuntimeData() noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
				if (REL::Module::get().version().compare(SKSE::RUNTIME_SSE_1_6_1130) != std::strong_ordering::less) {
					return REL::RelocateMember<AE_RUNTIME_DATA*>(this, 0x2b0);
				}
			}
			return nullptr;
		}

		[[nodiscard]] inline const AE_RUNTIME_DATA& GetAERuntimeData() const noexcept
		{
			return this->GetAERuntimeData();
		}

		// members
		BSTHashMap<std::uint64_t, BSFixedString> playerIDNameMap;  // 078
		std::uint64_t                            unk0A0;           // 0A0
		std::uint32_t                            unk0A8;           // 0A8
		std::uint32_t                            unk0AC;           // 0AC
		std::uint32_t                            unk0B0;           // 0B0
		std::uint32_t                            unk0B4;           // 0B4
		std::uint64_t                            unk0B8;           // 0B8
		std::uint64_t                            unk0C0;           // 0C0
		std::uint64_t                            unk0C8;           // 0C8
		std::uint64_t                            currentPlayerID;  // 0D0
		std::uint64_t                            displayPlayerID;  // 0D8
		std::uint32_t                            unk0E0;           // 0E0
		std::uint32_t                            unk0E4;           // 0E4
		BSTArray<void*>                          unk0E8;           // 0E8

		BSTArray<BGSSaveLoadFileEntry*> saveGameList;  // 100
		std::uint8_t                    unk118;        // 118
		std::uint8_t                    unk119;        // 119
		std::uint16_t                   unk11A;        // 11A
		std::uint32_t                   unk11C;        // 11C
		std::uint16_t                   unk120;        // 120
		std::uint16_t                   unk122;        // 122
		std::uint32_t                   unk124;        // 124
		std::uint32_t                   tickCount;     // 128
		std::uint32_t                   unk12C;        // 12C
		std::uint8_t                    unk130;        // 130
		std::uint8_t                    unk131;        // 131
		std::uint16_t                   unk132;        // 132
		std::uint32_t                   unk134;        // 134
		std::uint64_t                   unk138;        // 138
		std::uint64_t                   unk140;        // 140
		std::uint64_t                   unk148;        // 148
		std::uint64_t                   unk150;        // 150
		std::uint64_t                   unk158;        // 158
		std::uint64_t                   unk160;        // 160
		std::uint64_t                   unk168;        // 168
		std::uint64_t                   unk170;        // 170
		std::uint64_t                   unk178;        // 178
		std::uint64_t                   unk180;        // 180
		std::uint64_t                   unk188;        // 188
		std::uint64_t                   unk190;        // 190
		std::uint64_t                   unk198;        // 198
		std::uint64_t                   unk1A0;        // 1A0
		std::uint64_t                   unk1A8;        // 1A8
		std::uint64_t                   unk1B0;        // 1B0
		std::uint64_t                   unk1B8;        // 1B8
		std::uint64_t                   unk1C0;        // 1C0
		std::uint64_t                   unk1C8;        // 1C8
		std::uint64_t                   unk1D0;        // 1D0
		std::uint64_t                   unk1D8;        // 1D8
		std::uint64_t                   unk1E0;        // 1E0
		std::uint64_t                   unk1E8;        // 1E8
		std::uint64_t                   unk1F0;        // 1F0
		std::uint64_t                   unk1F8;        // 1F8

		std::uint64_t unk200;                                                               // 200
		std::uint64_t unk208;                                                               // 208
		std::uint64_t unk210;                                                               // 210
		std::uint64_t unk218;                                                               // 218
		std::uint64_t unk220;                                                               // 220
		std::uint64_t unk228;                                                               // 228
		std::uint64_t unk230;                                                               // 230
		std::uint64_t unk238;                                                               // 238
		std::uint64_t unk240;                                                               // 240
		std::uint64_t unk248;                                                               // 248
		std::uint32_t unk250;                                                               // 250
		std::uint32_t unk254;                                                               // 254
		std::uint64_t unk258;                                                               // 258
		std::uint16_t unk260;                                                               // 260
		std::uint16_t unk262;                                                               // 262
		std::uint32_t unk264;                                                               // 264
		std::uint64_t unk268;                                                               // 268
		std::uint32_t unk270;                                                               // 270
		std::uint32_t unk274;                                                               // 274
		std::uint64_t unk278;                                                               // 278
		std::uint64_t unk280;                                                               // 280
		std::uint32_t unk288;                                                               // 288
		std::uint32_t unk28C;                                                               // 28C
		std::uint64_t unk290;                                                               // 290
		std::uint64_t unk298;                                                               // 298
		std::uint32_t unk2A0;                                                               // 2A0
		std::uint32_t unk2A4;                                                               // 2A4
		std::uint64_t unk2A8;                                                               // 2A8
#if defined(EXCLUSIVE_SKYRIM_AE)  // AE 1130 specific change
		std::uint16_t   unk2B0;                                                             // 2B0
		std::uint16_t   unk2B2;                                                             // 2B2
		std::uint64_t   unk2B8;                                                             // 2B8
		BSTArray<void*> unk2C0;                                                             // 2C0
		BSTArray<void*> unk2D8;                                                             // 2D8
		std::uint8_t    unk2F0;                                                             // 2F0
#endif
#if !defined(SKYRIM_CROSS_VR)
		RUNTIME_DATA_CONTENT;
#endif
	protected:
		bool Save_Impl(std::int32_t a_deviceID, std::uint32_t a_outputStats, const char* a_fileName);
		bool Load_Impl(const char* a_fileName, std::int32_t a_deviceID, std::uint32_t a_outputStats, bool a_checkForMods);

	private:
		KEEP_FOR_RE()
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
