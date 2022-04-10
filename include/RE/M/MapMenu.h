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
		public IMenu,                             // 00000
		public BSTEventSink<MenuOpenCloseEvent>,  // 00030
		public IMapCameraCallbacks                // 00038
	{
	public:
		inline static auto                RTTI = RTTI_MapMenu;
		constexpr static std::string_view MENU_NAME = "MapMenu";

		struct RUNTIME_DATA
		{
			BSTSmartPointer<MapMoveHandler> moveHandler;   // 00000
			BSTSmartPointer<MapLookHandler> lookHandler;   // 00008
			BSTSmartPointer<MapZoomHandler> zoomHandler;   // 00010
			std::uint64_t                   unk00058;      // 00018
			LocalMapMenu                    localMapMenu;  // 00020
			RefHandle                       unk30460;      // 30420
			std::uint32_t                   unk30464;      // 30424
			std::uint32_t                   unk30468;      // 30428
			std::uint32_t                   unk3046C;      // 3042C
			BSTArray<void*>                 unk30470;      // 30430
			BSTArray<void*>                 unk30488;      // 30448
			MapCamera                       camera;        // 30460
			std::uint64_t                   unk30530;      // 304F0
			TESWorldSpace*                  worldSpace;    // 304F8
			GFxValue                        unk30540;      // 30500
			std::uint64_t                   unk30558;      // 30518
			std::uint64_t                   unk30560;      // 30520
			std::uint64_t                   unk30568;      // 30528
			std::uint32_t                   unk30570;      // 30530
			BSSoundHandle                   unk30574;      // 30534
			std::uint64_t                   unk30580;      // 30540
			std::uint64_t                   unk30588;      // 30548
			std::uint64_t                   unk30590;      // 30550
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x30558);

		~MapMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;                       // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;                         // 04
		void               AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;  // 05
		void               RefreshPlatform() override;                                            // 08

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;  // 01

		void PlaceMarker()
		{
			using func_t = decltype(&MapMenu::PlaceMarker);
			REL::Relocation<func_t> func{ REL::RelocationID(52226, 53113) };
			return func(this);
		}

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x40, 0x50);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x40, 0x50);
		}

		// members
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		RUNTIME_DATA runtimeData; // 40, 50
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(MapMenu) == 0x30598);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(MapMenu) == 0x305A8);
#endif
}
