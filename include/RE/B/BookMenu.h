#pragma once

#include "RE/B/BSScaleformExternalTexture.h"
#include "RE/B/BSString.h"
#include "RE/B/BSTEvent.h"
#include "RE/G/GPtr.h"
#include "RE/I/IMenu.h"
#include "RE/N/NiMatrix3.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiRect.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/S/SimpleAnimationGraphManagerHolder.h"
#include "RE/T/TESObjectREFR.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	struct BSAnimationGraphEvent;

	class BSGeometry;
	class ExtraDataList;
	class ExtraTextDisplayData;
	class NiAVObject;
	class NiSourceTexture;
	class TESObjectBOOK;

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

#ifdef ENABLE_SKYRIM_AE
		struct AE1799_RUNTIME_DATA
		{
			NiRect<float> unk98;  // 98
		};
		static_assert(sizeof(AE1799_RUNTIME_DATA) == 0x10);

		RUNTIME_DATA_ACCESSOR_VERSIONED_OPTIONAL_EX(AE1799_RUNTIME_DATA, GetAe1799RuntimeData, SKSE::RUNTIME_SSE_1_7_99, 0x98);
#endif

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

		[[nodiscard]] static ExtraTextDisplayData* GetDisplayData();
		[[nodiscard]] static ExtraDataList*        GetExtraList();
		[[nodiscard]] static TESObjectBOOK*        GetTargetForm();
		[[nodiscard]] static BSString&             GetDescription();
		[[nodiscard]] static TESObjectREFRPtr      GetTargetReference();  // null if opened from inventory/container
		[[nodiscard]] static NiPoint3&             GetDisplayPosition();
		[[nodiscard]] static NiMatrix3&            GetDisplayRotation();
		[[nodiscard]] static float&                GetDisplayScale();

#ifndef SKYRIM_CROSS_VR
		RUNTIME_CAST_ACCESSOR(SimpleAnimationGraphManagerHolder, AsSimpleAnimationGraphManagerHolder, 0x30, 0x40);
		RUNTIME_CAST_ACCESSOR(BSTEventSink<BSAnimationGraphEvent>, AsBSAnimationGraphEventSink, 0x48, 0x58);
#endif

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x50, 0x60);
		static void OpenBookMenu(const BSString& a_description, const ExtraDataList* a_extraList, TESObjectREFR* a_ref, TESObjectBOOK* a_book, const NiPoint3& a_pos, const NiMatrix3& a_rot, float a_scale, bool a_useDefaultPos);

		static void OpenMenuFromReference(TESObjectREFR* a_reference);                                                                                                                  // Can be taken.
		static void OpenMenuFromReference(TESObjectREFR* a_reference, const NiPoint3& a_pos, const NiMatrix3& a_rot, float a_scale, bool a_useDefaultPos);                              // Can be taken.
		static void OpenMenuFromBaseForm(TESObjectBOOK* a_book);                                                                                                                        // Can not be taken.
		static void OpenMenuFromBaseForm(TESObjectBOOK* a_book, const ExtraDataList* a_extraList, const NiPoint3& a_pos, const NiMatrix3& a_rot, float a_scale, bool a_useDefaultPos);  // Can not be taken.

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 50, 60
#endif

	private:
		static void
			OpenMenu_Impl(const BSString& a_description, const ExtraDataList* a_extraList, TESObjectREFR* a_targetReference, TESObjectBOOK* a_targetBook, const NiPoint3& a_pos, const NiMatrix3& a_rot, float a_scale, bool a_useDefaultPos);
	};
	STATIC_ASSERT_SIZE(BookMenu, 0x98, 0x98, 0xA8, 0x30);
}
#undef RUNTIME_DATA_CONTENT
