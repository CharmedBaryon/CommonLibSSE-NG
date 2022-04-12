#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/G/GPtr.h"
#include "RE/I/IMenu.h"
#include "RE/I/ImageData.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/S/SimpleAnimationGraphManagerHolder.h"

namespace RE
{
	struct BSAnimationGraphEvent;

	class NiAVObject;
	class TESObjectBOOK;
	class TESObjectREFR;

	// menuDepth = 1
	// flags = kPausesGame | kUsesMenuContext | kDisablePauseMenu | kRequiresUpdate | kTopmostRenderedMenu | kRendersOffscreenTargets
	// context = kBook
	class BookMenu :
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		public IMenu,                               // 00
		public SimpleAnimationGraphManagerHolder,   // 30
		public BSTEventSink<BSAnimationGraphEvent>  // 48
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static auto                RTTI = RTTI_BookMenu;
		inline static auto                VTABLE = VTABLE_BookMenu;
		constexpr static std::string_view MENU_NAME = "Book Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                              \
	BSTArray<ImageData>   unk50;     /* 00 */             \
	GPtr<GFxMovieView>    book;      /* 18 */             \
	NiPointer<NiAVObject> book3D;    /* 20 */             \
	std::uint32_t         unk78;     /* 28 */             \
	std::uint32_t         pad7C;     /* 2C */             \
	std::uint64_t         unk80;     /* 30 */             \
	void*                 unk88;     /* 38 - smart ptr */ \
	std::uint16_t         unk90;     /* 40 */             \
	std::uint16_t         unk92;     /* 42 */             \
	bool                  closeMenu; /* 44 */             \
	bool                  isNote;    /* 45 */             \
	std::uint8_t          unk96;     /* 46 */             \
	std::uint8_t          pad97;     /* 47 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x48);

		~BookMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;                         // 04
		void               AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;  // 05
		void               PostDisplay() override;                                                // 06
		void               PreDisplay() override;                                                 // 07

#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		// override (BSTEventSink<BSAnimationGraphEvent>)
		BSEventNotifyControl ProcessEvent(const BSAnimationGraphEvent* a_event, BSTEventSource<BSAnimationGraphEvent>* a_eventSource) override;  // 01
#endif

		[[nodiscard]] static TESObjectBOOK* GetTargetForm();
		[[nodiscard]] static TESObjectREFR* GetTargetReference();  // returns null if opened from inventory

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x50, 0x60);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x50, 0x60);
		}

		// members
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		RUNTIME_DATA_CONTENT  // 50, 60
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(BookMenu) == 0x98);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(BookMenu) == 0xA8);
#endif
}
#undef RUNTIME_DATA_CONTENT
