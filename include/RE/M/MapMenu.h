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
	class MapClickHandler;
	class MapLookHandler;
	class MapMoveHandler;
	class MapTouchpadHandler;
	class MapZoomHandler;
	class MenuOpenCloseEvent;
	class TESWorldSpace;

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

		struct Unk30470Entry
		{
			TESFullName*  unk00;
			std::uint32_t unk08;
			std::uint32_t unk0C;
			TESForm*      unk10;
			std::uint32_t unk18;
			std::uint32_t unk1C;
			std::uint32_t unk20;
			std::uint32_t unk24;
			std::uint32_t unk28;
			std::uint32_t unk2C;
			std::uint32_t unk30;
			std::uint32_t unk34;
		};
		static_assert(sizeof(Unk30470Entry) == 0x38);

		struct Unk30488Entry
		{
			std::uint32_t unk00;
			std::uint32_t unk04;
			std::uint32_t unk08;
			std::uint32_t unk0C;
			const char*   label;
			std::uint32_t unk18;
			std::uint32_t unk1C;
			std::uint32_t unk20;
			std::uint32_t unk24;
			std::uint32_t unk28;
			std::uint32_t unk2C;
			std::uint32_t unk30;
			std::uint32_t unk34;
			std::uint32_t unk38;
			std::uint32_t unk3C;
			std::uint32_t unk40;
			std::uint32_t unk44;
		};
		static_assert(sizeof(Unk30488Entry) == 0x48);

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                               \
	BSTSmartPointer<MapMoveHandler> moveHandler;  /* 00 */ \
	BSTSmartPointer<MapLookHandler> lookHandler;  /* 08 */ \
	BSTSmartPointer<MapZoomHandler> zoomHandler;  /* 10 */ \
	ObjectRefHandle                 mapMarker;    /* 18 */ \
	LocalMapMenu                    localMapMenu; /* 20 */

			RUNTIME_DATA_CONTENT
		};
#if !defined(ENABLE_SKYRIM_VR)
		static_assert(sizeof(RUNTIME_DATA) == 0x30420);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		static_assert(sizeof(RUNTIME_DATA) == 0x304A0);
#else
		static_assert(sizeof(RUNTIME_DATA) == 0x30420);
#endif

		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT                                      \
	BSTSmartPointer<MapMoveHandler>     moveHandler;     /* 00060 */ \
	BSTSmartPointer<MapLookHandler>     lookHandler;     /* 00068*/  \
	BSTSmartPointer<MapZoomHandler>     zoomHandler;     /* 00070*/  \
	BSTSmartPointer<MapClickHandler>    clickHandler;    /* 00078*/  \
	BSTSmartPointer<MapTouchpadHandler> touchpadHandler; /* 00080*/  \
	BSTSmartPointer<void*>              unk00088;        /* 00088*/  \
	BSTSmartPointer<void*>              unk00090;        /* 00090*/  \
	BSTSmartPointer<void*>              unk00098;        /* 00098*/  \
	BSTSmartPointer<void*>              unk000A0;        /* 000A0*/  \
	ObjectRefHandle                     mapMarker;       /* 000A8*/  \
	LocalMapMenu                        localMapMenu;    /* 000B0*/
            VR_RUNTIME_DATA_CONTENT;
		};
#if !defined(ENABLE_SKYRIM_VR)
		static_assert(sizeof(VR_RUNTIME_DATA) == 0x30450);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		static_assert(sizeof(VR_RUNTIME_DATA) == 0x304D0);
#else
		static_assert(sizeof(VR_RUNTIME_DATA) == 0x30450);
#endif

		struct RUNTIME_DATA2
		{
#define RUNTIME_DATA2_CONTENT                                \
	RefHandle                unk30460;             /* 000 */ \
	NiPoint3                 playerMarkerPosition; /* 004 */ \
	BSTArray<Unk30470Entry*> unk30470;             /* 010 */ \
	BSTArray<Unk30488Entry*> unk30488;             /* 028 */ \
	MapCamera                camera;               /* 040 */ \
	std::uint64_t            unk30530;             /* 0D0 */ \
	TESWorldSpace*           worldSpace;           /* 0D8 */ \
	GFxValue                 unk30540;             /* 0E0 */ \
	std::uint64_t            unk30558;             /* 0F8 */ \
	std::uint64_t            unk30560;             /* 100 */ \
	std::uint64_t            unk30568;             /* 108 */ \
	std::uint32_t            unk30570;             /* 110 */ \
	BSSoundHandle            unk30574;             /* 114 */ \
	std::uint64_t            unk30580;             /* 120 */ \
	std::uint64_t            unk30588;             /* 128 */ \
	std::uint64_t            unk30590;             /* 130 */
            RUNTIME_DATA2_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA2) == 0x138);

		struct VR_RUNTIME_DATA2
		{
#define VR_RUNTIME_DATA2_CONTENT                               \
	RefHandle                unk30530;             /* 000 */   \
	NiPoint3                 playerMarkerPosition; /* 004 */   \
	BSTArray<Unk30470Entry*> unk30540;             /* 010 */   \
	BSTArray<Unk30488Entry*> unk30558;             /* 028 */   \
	NiPoint3                 unk30570;             /* 040 */   \
	std::uint32_t            unk3057C;             /* 30540 */ \
	std::uint64_t            unk30580;             /* 30558 */ \
	std::uint64_t            unk30588;             /* 30570 */ \
	TESWorldSpace*           worldSpace;           /* 0D8 */   \
	GFxValue                 unk30598;             /* 0E0 */   \
	BSSoundHandle            unk305B0;             /* 114 */   \
	std::uint64_t            unk305C0;             /* 120 */   \
	std::uint64_t            unk305C8;             /* 128 */   \
	std::uint64_t            unk305D0;             /* 128 */   \
	std::uint64_t            unk305D8;             /* 128 */   \
	std::uint64_t            unk305E0;             /* 128 */   \
	std::uint64_t            unk305E8;             /* 130 */
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

		[[nodiscard]] inline RUNTIME_DATA* GetRuntimeData() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return REL::RelocateMember<RUNTIME_DATA*>(this, 0x40, 0);
			} else {
				return nullptr;
			}
		}

		[[nodiscard]] inline const RUNTIME_DATA* GetRuntimeData() const noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return REL::RelocateMember<RUNTIME_DATA*>(this, 0x40, 0);
			} else {
				return nullptr;
			}
		}

		[[nodiscard]] inline RUNTIME_DATA2* GetRuntimeData2() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return REL::RelocateMember<RUNTIME_DATA2*>(this, 0x30460, 0);
			} else {
				return nullptr;
			}
		}

		[[nodiscard]] inline const RUNTIME_DATA2* GetRuntimeData2() const noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return REL::RelocateMember<RUNTIME_DATA2*>(this, 0x30460, 0);
			} else {
				return nullptr;
			}
		}

		[[nodiscard]] inline VR_RUNTIME_DATA* GetVRRuntimeData() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return REL::RelocateMember<VR_RUNTIME_DATA*>(this, 0, 0x60);
			}
		}

		[[nodiscard]] inline const VR_RUNTIME_DATA* GetVRRuntimeData() const noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return REL::RelocateMember<VR_RUNTIME_DATA*>(this, 0, 0x60);
			}
		}

		[[nodiscard]] inline VR_RUNTIME_DATA2* GetVRRuntimeData2() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return REL::RelocateMember<VR_RUNTIME_DATA2*>(this, 0, 0x30530);
			}
		}

		[[nodiscard]] inline const VR_RUNTIME_DATA2* GetVRRuntimeData2() const noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return REL::RelocateMember<VR_RUNTIME_DATA2*>(this, 0, 0x30530);
			}
		}
		// members
#if !defined(ENABLE_SKYRIM_VR)
		VR_RUNTIME_DATA_CONTENT;   // 40, 60
		VR_RUNTIME_DATA2_CONTENT;  // 30460, 30530
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		RUNTIME_DATA_CONTENT;   // 40, 60
		RUNTIME_DATA2_CONTENT;  // 30460, 30530
#endif
	private:
		KEEP_FOR_RE()
	};
#if !defined(ENABLE_SKYRIM_VR)
#	ifdef ENABLE_SKYRIM_AE
	static_assert(sizeof(MapMenu) == 0x30560);
#	else
	static_assert(sizeof(MapMenu) == 0x30598);
#	endif
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(MapMenu) == 0x30640);
#else
	static_assert(sizeof(MapMenu) == 0x40);
#endif
}

#undef RUNTIME_DATA_CONTENT
#undef VR_RUNTIME_DATA_CONTENT
#undef RUNTIME_DATA2_CONTENT
#undef VR_RUNTIME_DATA2_CONTENT
