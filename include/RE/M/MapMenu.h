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
#include "RE/W/WorldSpaceMenu.h"

namespace RE
{
	class BSAudioManager;
	class MapLookHandler;
	class MapMoveHandler;
	class MapZoomHandler;
	class MenuOpenCloseEvent;
	class TESWorldSpace;
	struct MapMenuMarker;

	// menuDepth = 3
	// flags = kPausesGame | kUsesCursor | kRendersOffscreenTargets | kCustomRendering
	// context = kMap
	class MapMenu :
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
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
		inline static constexpr auto      RTTI = RTTI_MapMenu;
		constexpr static std::string_view MENU_NAME = "MapMenu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                \
	BSTSmartPointer<MapMoveHandler> moveHandler;   /* 00 */ \
	BSTSmartPointer<MapLookHandler> lookHandler;   /* 08 */ \
	BSTSmartPointer<MapZoomHandler> zoomHandler;   /* 10 */ \
	ObjectRefHandle                 mapMarker;     /* 18 */ \
	LocalMapMenu                    localMapMenu;  /* 20 */

			RUNTIME_DATA_CONTENT
		};
#ifndef ENABLE_SKYRIM_VR
		static_assert(sizeof(RUNTIME_DATA) == 0x30420);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		static_assert(sizeof(RUNTIME_DATA) == 0x304A0);
#endif

		struct RUNTIME_DATA2
		{
#define RUNTIME_DATA2_CONTENT                                 \
	RefHandle                unk30460;              /* 000 */ \
	NiPoint3                 playerMarkerPosition;  /* 004 */ \
	BSTArray<MapMenuMarker>  mapMarkers;            /* 010 */ \
	BSTArray<GFxValue>       markerData;            /* 028 */ \
	MapCamera                camera;                /* 040 */ \
	std::uint64_t            unk30530;              /* 0D0 */ \
	TESWorldSpace*           worldSpace;            /* 0D8 */ \
	GFxValue                 mapMovie;              /* 0E0 */ \
	std::int32_t             selectedMarker;        /* 0F8 */ \
	NiPoint3                 cameraPickOrigin;      /* 0FC */ \
	NiPoint3                 cameraPickDirection;   /* 108 */ \
	BSSoundHandle            unk30574;              /* 114 */ \
	std::uint64_t            unk30580;              /* 120 */ \
	std::uint32_t            unk30588;              /* 128 */ \
	bool                     controlsReady;         /* 12C */ \
	std::uint8_t             unk3058D;              /* 12D */ \
	std::uint16_t            unk3058E;              /* 12E */ \
	std::uint64_t            unk30590;              /* 130 */
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
#ifndef SKYRIM_CROSS_VR
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;  // 01
#endif

		void PlaceMarker()
		{
			using func_t = decltype(&MapMenu::PlaceMarker);
			REL::Relocation<func_t> func{ RELOCATION_ID(52226, 53113) };
			return func(this);
		}

		[[nodiscard]] WorldSpaceMenu* AsWorldSpaceMenu() noexcept
		{
			if SKYRIM_REL_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			}
			return &REL::RelocateMember<WorldSpaceMenu>(this, 0, 0);
		}

		[[nodiscard]] const WorldSpaceMenu* AsWorldSpaceMenu() const noexcept
		{
			return const_cast<MapMenu*>(this)->AsWorldSpaceMenu();
		}

		[[nodiscard]] BSTEventSink<MenuOpenCloseEvent>* AsMenuOpenCloseEventSink() noexcept
		{
			return &REL::RelocateMember<BSTEventSink<MenuOpenCloseEvent>>(this, 0x30, 0x58);
		}

		[[nodiscard]] const BSTEventSink<MenuOpenCloseEvent>* AsMenuOpenCloseEventSink() const noexcept
		{
			return const_cast<MapMenu*>(this)->AsMenuOpenCloseEventSink();
		}

		[[nodiscard]] IMapCameraCallbacks* AsIMapCameraCallbacks() noexcept
		{
			return &REL::RelocateMember<IMapCameraCallbacks>(this, 0x38, 0x60);
		}

		[[nodiscard]] const IMapCameraCallbacks* AsIMapCameraCallbacks() const noexcept
		{
			return const_cast<MapMenu*>(this)->AsIMapCameraCallbacks();
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
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT       // 40, 68
		RUNTIME_DATA2_CONTENT  // 30460, 30508
#endif
	};

#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(MapMenu) == 0x30598);
#endif
}

#undef RUNTIME_DATA_CONTENT
#undef RUNTIME_DATA2_CONTENT
