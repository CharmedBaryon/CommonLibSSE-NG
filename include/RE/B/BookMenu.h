#pragma once

#include "RE/B/BSScaleformExternalTexture.h"
#include "RE/B/BSString.h"
#include "RE/B/BSTEvent.h"
#include "RE/G/GPtr.h"
#include "RE/I/IMenu.h"
#include "RE/N/NiMatrix3.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/S/SimpleAnimationGraphManagerHolder.h"

namespace RE
{
	struct BSAnimationGraphEvent;

	class BSGeometry;
	class ExtraDataList;
	class NiAVObject;
	class NiSourceTexture;
	class TESObjectBOOK;
	class TESObjectREFR;

	// menuDepth = 1
	// flags = kPausesGame | kUsesMenuContext | kDisablePauseMenu | kRequiresUpdate | kTopmostRenderedMenu | kRendersOffscreenTargets
	// context = kBook
	class BookMenu :
#ifndef SKYRIM_CROSS_VR
		public IMenu,                               // 00
		public SimpleAnimationGraphManagerHolder,   // 30
		public BSTEventSink<BSAnimationGraphEvent>  // 48
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_BookMenu;
		inline static constexpr auto      VTABLE = VTABLE_BookMenu;
		constexpr static std::string_view MENU_NAME = "Book Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                    \
	BSTArray<BSScaleformExternalTexture> bookTextures;     /* 00 */             \
	GPtr<GFxMovieView>                   book;             /* 18 */             \
	NiPointer<NiAVObject>                bookModel;        /* 20 */             \
	std::uint32_t                        numRenderTargets; /* 28 */             \
	std::uint32_t                        pad7C;            /* 2C */             \
	NiSourceTexture*                     pageTexture;      /* 80*/              \
	NiPointer<BSGeometry>                pageTextGeo;      /* 88 - smart ptr */ \
	std::uint16_t                        unk90;            /* 90 */             \
	std::uint16_t                        startAnimating;   /* 92*/              \
	bool                                 closeMenu;        /* 94*/              \
	bool                                 isNote;           /* 95 */             \
	bool                                 bookInitialized;  /* 96 */             \
	std::uint8_t                         pad97;            /* 97 */
            RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x48);

		~BookMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;                         // 04
		void               AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;  // 05
		void               PostDisplay() override;                                                // 06
		void               PreDisplay() override;                                                 // 07

#ifndef SKYRIM_CROSS_VR
		// override (BSTEventSink<BSAnimationGraphEvent>)
		BSEventNotifyControl ProcessEvent(const BSAnimationGraphEvent* a_event, BSTEventSource<BSAnimationGraphEvent>* a_eventSource) override;  // 01
#endif

		[[nodiscard]] static TESObjectBOOK* GetTargetForm();
		[[nodiscard]] static TESObjectREFR* GetTargetReference();  // returns null if opened from inventory

		[[nodiscard]] SimpleAnimationGraphManagerHolder* AsSimpleAnimationGraphManagerHolder() noexcept
		{
			return &REL::RelocateMember<SimpleAnimationGraphManagerHolder>(this, 0x30, 0x40);
		}

		[[nodiscard]] const SimpleAnimationGraphManagerHolder* AsSimpleAnimationGraphManagerHolder() const noexcept
		{
			return const_cast<BookMenu*>(this)->AsSimpleAnimationGraphManagerHolder();
		}

		[[nodiscard]] BSTEventSink<BSAnimationGraphEvent>* AsBSAnimationGraphEventSink() noexcept
		{
			return &REL::RelocateMember<BSTEventSink<BSAnimationGraphEvent>>(this, 0x48, 0x58);
		}

		[[nodiscard]] const BSTEventSink<BSAnimationGraphEvent>* AsBSAnimationGraphEventSink() const noexcept
		{
			return const_cast<BookMenu*>(this)->AsBSAnimationGraphEventSink();
		}

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x50, 0x60);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x50, 0x60);
		}

		static void OpenBookMenu(const BSString& a_description, const ExtraDataList* a_extraList, TESObjectREFR* a_ref, TESObjectBOOK* a_book, const NiPoint3& a_pos, const NiMatrix3& a_rot, float a_scale, bool a_useDefaultPos);

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT  // 50, 60
#endif
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(BookMenu) == 0x98);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BookMenu) == 0xA8);
#else
	static_assert(sizeof(BookMenu) == 0x30);
#endif
}
#undef RUNTIME_DATA_CONTENT
