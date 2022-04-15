#pragma once

#include "RE/B/BSSoundHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IMapCameraCallbacks.h"
#include "RE/I/IMenu.h"
#include "RE/L/LocalMapMenu.h"
#include "RE/M/MapCamera.h"

#if !defined(ENABLE_SKYRIM_AE) && !(ENABLE_SKYRIM_SE)
#	include "RE/W/WorldSpaceMenu.h"
#endif

namespace RE
{
	class BSAudioManager;
	class MapLookHandler;
	class MapMoveHandler;
	class MapZoomHandler;
	class MenuOpenCloseEvent;
	class TESWorldSpace;

	// menuDepth = 3
	// flags = kPausesGame | kUsesCursor | kRendersOffscreenTargets | kCustomRendering
	// context = kMap
	class MapMenu :
#if !defined(ENABLE_SKYRIM_AE) && !(ENABLE_SKYRIM_SE)
		public WorldSpaceMenu,                    // 00000
		public BSTEventSink<MenuOpenCloseEvent>,  // 00058
		public IMapCameraCallbacks                // 00060
#elif !defined(ENABLE_SKYRIM_VR)
		public IMenu,                             // 00000
		public BSTEventSink<MenuOpenCloseEvent>,  // 00030
		public IMapCameraCallbacks                // 00038
#else
		public IMenu
#endif
	{
	public:
		inline static auto                RTTI = RTTI_MapMenu;
		constexpr static std::string_view MENU_NAME = "MapMenu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                               \
	BSTSmartPointer<MapMoveHandler> moveHandler;  /* 00 */ \
	BSTSmartPointer<MapLookHandler> lookHandler;  /* 08 */ \
	BSTSmartPointer<MapZoomHandler> zoomHandler;  /* 10 */ \
	std::uint64_t                   unk00058;     /* 18 */ \
	LocalMapMenu                    localMapMenu; /* 20 */

			RUNTIME_DATA_CONTENT
		};
#ifndef ENABLE_SKYRIM_VR
		static_assert(sizeof(RUNTIME_DATA) == 0x30420);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		static_assert(sizeof(RUNTIME_DATA) == 0x304A0);
#endif

		struct RUNTIME_DATA2
		{
#define RUNTIME_DATA2_CONTENT             \
	RefHandle       unk30460;   /* 000 */ \
	std::uint32_t   unk30464;   /* 004 */ \
	std::uint32_t   unk30468;   /* 008 */ \
	std::uint32_t   unk3046C;   /* 00C */ \
	BSTArray<void*> unk30470;   /* 010 */ \
	BSTArray<void*> unk30488;   /* 028 */ \
	MapCamera       camera;     /* 040 */ \
	std::uint64_t   unk30530;   /* 0D0 */ \
	TESWorldSpace*  worldSpace; /* 0D8 */ \
	GFxValue        unk30540;   /* 0E0 */ \
	std::uint64_t   unk30558;   /* 0F8 */ \
	std::uint64_t   unk30560;   /* 100 */ \
	std::uint64_t   unk30568;   /* 108 */ \
	std::uint32_t   unk30570;   /* 110 */ \
	BSSoundHandle   unk30574;   /* 114 */ \
	std::uint64_t   unk30580;   /* 120 */ \
	std::uint64_t   unk30588;   /* 128 */ \
	std::uint64_t   unk30590;   /* 130 */
            RUNTIME_DATA2_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA2) == 0x138);

		~MapMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;                       // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;                         // 04
		void               AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;  // 05
		void               RefreshPlatform() override;                                            // 08

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource);  // 01

		void PlaceMarker()
		{
			using func_t = decltype(&MapMenu::PlaceMarker);
			REL::Relocation<func_t> func{ REL::RelocationID(52226, 53113) };
			return func(this);
		}

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x40, 0x68);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x40, 0x68);
		}

		[[nodiscard]] inline RUNTIME_DATA2& GetRuntimeData2() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA2>(this, 0x30460, 0x30508);
		}

		[[nodiscard]] inline const RUNTIME_DATA2& GetRuntimeData2() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA2>(this, 0x30460, 0x30508);
		}

		// members
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		RUNTIME_DATA_CONTENT       // 40, 68
			RUNTIME_DATA2_CONTENT  // 30460, 30508
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(MapMenu) == 0x30598);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(MapMenu) == 0x30640);
#endif
}

#undef RUNTIME_DATA_CONTENT
#undef RUNTIME_DATA2_CONTENT
