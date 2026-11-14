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
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSAudioManager;
	class MapClickHandler;
	class MapLookHandler;
	class MapMoveHandler;
	class MapTouchpadHandler;
	class MapZoomHandler;
	class MenuOpenCloseEvent;
	class NiAVObject;
	class TESWorldSpace;

	// menuDepth = 3
	// flags = kPausesGame | kUsesCursor | kRendersOffscreenTargets | kCustomRendering
	// context = kMap
	class MapMenu :
#if defined(EXCLUSIVE_SKYRIM_VR)
		// VR has no IMapCameraCallbacks base; its members start at 0x60.
		public WorldSpaceMenu,                   // 00000
		public BSTEventSink<MenuOpenCloseEvent>  // 00058
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

		// Common handlers shared by SE/AE and VR
#define COMMON_HANDLERS_CONTENT                           \
	BSTSmartPointer<MapMoveHandler> moveHandler; /* 00 */ \
	BSTSmartPointer<MapLookHandler> lookHandler; /* 08 */ \
	BSTSmartPointer<MapZoomHandler> zoomHandler; /* 10 */

		// VR-specific extra handlers
#define VR_EXTRA_HANDLERS_CONTENT                                 \
	BSTSmartPointer<MapClickHandler>    clickHandler;    /* 18 */ \
	BSTSmartPointer<MapTouchpadHandler> touchpadHandler; /* 20 */ \
	BSTSmartPointer<void*>              unk00088;        /* 28 */ \
	BSTSmartPointer<void*>              unk00090;        /* 30 */ \
	BSTSmartPointer<void*>              unk00098;        /* 38 */ \
	BSTSmartPointer<void*>              unk000A0;        /* 40 */

		// Common map data shared by SE/AE and VR (at different offsets)
#define COMMON_MAP_DATA_CONTENT                              \
	ObjectRefHandle mapMarker;    /* 18 (SE/AE) / A8 (VR) */ \
	LocalMapMenu    localMapMenu; /* 20 (SE/AE) / B0 (VR) */

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT \
	COMMON_HANDLERS_CONTENT  \
	COMMON_MAP_DATA_CONTENT

			RUNTIME_DATA_CONTENT
		};
		STATIC_ASSERT_SIZE(RUNTIME_DATA, 0x30420, 0x30420, 0x304A0, 0x30320);

		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT \
	COMMON_HANDLERS_CONTENT     \
	VR_EXTRA_HANDLERS_CONTENT   \
	COMMON_MAP_DATA_CONTENT

			VR_RUNTIME_DATA_CONTENT;
		};
		STATIC_ASSERT_SIZE(VR_RUNTIME_DATA, 0x30450, 0x30450, 0x304D0, 0x30350);

		// Common map data 2 shared by SE/AE and VR
#define COMMON_MAP_DATA2_CONTENT                                                     \
	RefHandle               cameraRootRef;        /* 000 - defaults to player ref */ \
	NiPoint3                playerMarkerPosition; /* 004 */                          \
	BSTArray<MapMenuMarker> mapMarkers;           /* 010 */                          \
	BSTArray<GFxValue>      markerData;           /* 028 */

		struct RUNTIME_DATA2
		{
#define RUNTIME_DATA2_CONTENT                        \
	COMMON_MAP_DATA2_CONTENT                         \
	MapCamera      camera;                 /* 040 */ \
	std::uint64_t  unk30530;               /* 0D0 */ \
	TESWorldSpace* worldSpace;             /* 0D8 */ \
	GFxValue       mapMovie;               /* 0E0 */ \
	std::int32_t   selectedMarker;         /* 0F8 */ \
	NiPoint3       cameraPickOrigin;       /* 0FC */ \
	NiPoint3       cameraPickDirection;    /* 108 */ \
	BSSoundHandle  unk30574;               /* 114 */ \
	std::int32_t   pickCountdown;          /* 120 */ \
	bool           savedPlayerUnderwater;  /* 124 */ \
	bool           markersEnabled;         /* 125 */ \
	bool           nonDoorMarkersEnabled;  /* 126 */ \
	std::uint8_t   pad30587;               /* 127 */ \
	std::uint8_t   unk30588;               /* 128 */ \
	std::uint8_t   unk30589;               /* 129 */ \
	bool           overrodeTESWorldSpace;  /* 12A */ \
	bool           cameraSetupPending;     /* 12B */ \
	bool           controlsReady;          /* 12C */ \
	bool           currentLocationEnabled; /* 12D */ \
	bool           fastTravelConfirmed;    /* 12E */ \
	bool           mapMarkersAllowed;      /* 12F */ \
	bool           ownsTempMarkerRef;      /* 130 */ \
	std::uint8_t   pad30591[7];            /* 131 */

			RUNTIME_DATA2_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA2) == 0x138);

		struct VR_RUNTIME_DATA2
		{
#define VR_RUNTIME_DATA2_CONTENT                     \
	COMMON_MAP_DATA2_CONTENT                         \
	NiPoint3       unk30570;               /* 040 */ \
	float          savedNearDistance;      /* 04C */ \
	float          savedFarDistance;       /* 050 */ \
	std::uint32_t  unk30584;               /* 054 */ \
	std::uint64_t  unk30588;               /* 058 */ \
	TESWorldSpace* worldSpace;             /* 060 */ \
	GFxValue       mapMovie;               /* 068 */ \
	BSSoundHandle  unk305B0;               /* 080 */ \
	std::uint8_t   unk305BC;               /* 08C */ \
	std::uint8_t   unk305BD;               /* 08D */ \
	std::uint8_t   unk305BE;               /* 08E */ \
	std::uint8_t   unk305BF;               /* 08F */ \
	std::uint8_t   unk305C0;               /* 090 */ \
	std::uint8_t   unk305C1;               /* 091 */ \
	bool           overrodeTESWorldSpace;  /* 092 */ \
	bool           initialized;            /* 093 */ \
	bool           refreshPlayerMarker;    /* 094 */ \
	bool           refreshMapAngle;        /* 095 */ \
	bool           closing;                /* 096 */ \
	bool           controlsReady;          /* 097 */ \
	bool           currentLocationEnabled; /* 098 */ \
	bool           fastTravelConfirmed;    /* 099 */ \
	bool           mapMarkersAllowed;      /* 09A */ \
	bool           ownsTempMarkerRef;      /* 09B */ \
	std::uint32_t  pad305CC;               /* 09C */ \
	NiAVObject*    crosshairParent;        /* 0A0 */ \
	NiAVObject*    locationBeaconParent;   /* 0A8 */ \
	NiAVObject*    markerText3DNode;       /* 0B0 */ \
	IMenu*         markerText3DMenu;       /* 0B8 */

			VR_RUNTIME_DATA2_CONTENT;
		};
		static_assert(sizeof(VR_RUNTIME_DATA2) == 0xC0);

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
			static REL::Relocation<func_t> func{ RELOCATION_ID(52226, 53113) };
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

#ifndef SKYRIM_CROSS_VR
		RUNTIME_CAST_ACCESSOR(BSTEventSink<MenuOpenCloseEvent>, AsMenuOpenCloseEventSink, 0x30, 0x58);

		// VR has no IMapCameraCallbacks subobject, so this is flat-only.
		[[nodiscard]] inline IMapCameraCallbacks* AsIMapCameraCallbacks() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return &REL::RelocateMember<IMapCameraCallbacks>(this, 0x38, 0);
			} else {
				return nullptr;
			}
		}

		[[nodiscard]] inline const IMapCameraCallbacks* AsIMapCameraCallbacks() const noexcept
		{
			return const_cast<MapMenu*>(this)->AsIMapCameraCallbacks();
		}
#endif

		[[nodiscard]] inline RUNTIME_DATA* GetRuntimeData() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return &REL::RelocateMember<RUNTIME_DATA>(this, 0x40, 0);
			} else {
				return nullptr;
			}
		}

		[[nodiscard]] inline const RUNTIME_DATA* GetRuntimeData() const noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return &REL::RelocateMember<RUNTIME_DATA>(this, 0x40, 0);
			} else {
				return nullptr;
			}
		}

		[[nodiscard]] inline RUNTIME_DATA2* GetRuntimeData2() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return &REL::RelocateMember<RUNTIME_DATA2>(this, 0x30460, 0);
			} else {
				return nullptr;
			}
		}

		[[nodiscard]] inline const RUNTIME_DATA2* GetRuntimeData2() const noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return &REL::RelocateMember<RUNTIME_DATA2>(this, 0x30460, 0);
			} else {
				return nullptr;
			}
		}

		[[nodiscard]] inline VR_RUNTIME_DATA* GetVRRuntimeData() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return &REL::RelocateMember<VR_RUNTIME_DATA>(this, 0, 0x60);
			}
		}

		[[nodiscard]] inline const VR_RUNTIME_DATA* GetVRRuntimeData() const noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return &REL::RelocateMember<VR_RUNTIME_DATA>(this, 0, 0x60);
			}
		}

		[[nodiscard]] inline VR_RUNTIME_DATA2* GetVRRuntimeData2() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return &REL::RelocateMember<VR_RUNTIME_DATA2>(this, 0, 0x30530);
			}
		}

		[[nodiscard]] inline const VR_RUNTIME_DATA2* GetVRRuntimeData2() const noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return &REL::RelocateMember<VR_RUNTIME_DATA2>(this, 0, 0x30530);
			}
		}
		// members
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		RUNTIME_DATA_CONTENT;   // 40, 60
		RUNTIME_DATA2_CONTENT;  // 30460, 30530
#elif defined(EXCLUSIVE_SKYRIM_VR)
		VR_RUNTIME_DATA_CONTENT;                  // 40, 60
		VR_RUNTIME_DATA2_CONTENT;                 // 30460, 30530
#endif
	};
	STATIC_ASSERT_SIZE(MapMenu, 0x30598, 0x30598, 0x305f0, 0x30);
}

// Clean up sub-macros
#undef COMMON_HANDLERS_CONTENT
#undef VR_EXTRA_HANDLERS_CONTENT
#undef COMMON_MAP_DATA_CONTENT
#undef COMMON_MAP_DATA2_CONTENT

// Clean up main macros
#undef RUNTIME_DATA_CONTENT
#undef VR_RUNTIME_DATA_CONTENT
#undef RUNTIME_DATA2_CONTENT
#undef VR_RUNTIME_DATA2_CONTENT
