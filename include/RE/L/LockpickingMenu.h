#pragma once

#include "RE/B/BSResourceHandle.h"
#include "RE/B/BSSoundHandle.h"
#include "RE/B/BSTEvent.h"
#include "RE/I/IMenu.h"
#include "RE/M/MenuEventHandler.h"
#include "RE/N/NiMatrix3.h"
#include "RE/N/NiPoint3.h"
#include "RE/T/TESObjectREFR.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class MenuOpenCloseEvent;
	class NiAVObject;
	class NiControllerManager;
	class NiControllerSequence;

	// menuDepth = 3
	// flags = kPausesGame | kDisablePauseMenu | kRequiresUpdate
	// context = kLockpicking
	class LockpickingMenu :
		public IMenu,  // 00
#ifndef SKYRIM_CROSS_VR
		public MenuEventHandler,                 // 30
		public BSTEventSink<MenuOpenCloseEvent>  // 40
#else
		public MenuEventHandler  // 30
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_LockpickingMenu;
		inline static constexpr auto      VTABLE = VTABLE_LockpickingMenu;
		constexpr static std::string_view MENU_NAME = "Lockpicking Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                            \
	ModelDBHandle         lockpickShiv;        /* 00 */ \
	ModelDBHandle         pickModel;           /* 08 */ \
	NiMatrix3             pickRotation;        /* 10 */ \
	NiPoint3              lockRotCenter;       /* 34 */ \
	NiControllerManager*  lockController;      /* 40 */ \
	NiControllerSequence* lockIntro;           /* 48 */ \
	NiControllerSequence* lockRotate;          /* 50 */ \
	NiControllerManager*  pickController;      /* 58 */ \
	NiControllerSequence* pickIntro;           /* 60 */ \
	NiControllerSequence* pickDamage;          /* 68 */ \
	NiControllerSequence* pickBreak;           /* 70 */ \
	NiControllerSequence* currentPickSequence; /* 78 */ \
	float                 pickKeyTime;         /* 80 */ \
	std::uint32_t         unk0CC;              /* 84 */ \
	NiControllerSequence* currentLockSequence; /* 88 */ \
	float                 lockKeyTime;         /* 90 */ \
	float                 pickAngle;           /* 94 */ \
	float                 lockAngle;           /* 98 */ \
	float                 damagePickAngle;     /* 9C */ \
	float                 pickBreakSeconds;    /* A0 */ \
	BSSoundHandle         pickTensionSound;    /* A4 */ \
	float                 unk0F8;              /* B0 */ \
	float                 sweetSpotAngle;      /* B4 */ \
	float                 partialPickAngle;    /* B8 */ \
	std::uint32_t         numBrokenPicks;      /* BC */ \
	bool                  init3DElements;      /* C0 */ \
	bool                  animating;           /* C1 */ \
	bool                  unk10A;              /* C2 */ \
	bool                  menuCleared;         /* C3 */ \
	bool                  animationFinished;   /* C4 */ \
	bool                  isLockpickingCrime;  /* C5 */ \
	std::uint8_t          unk10E;              /* C6 */ \
	std::uint8_t          pad10F;              /* C7 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0xC8);

#ifdef ENABLE_SKYRIM_AE
		struct AE1799_RUNTIME_DATA
		{
			float         unk110;     // 110
			float         unk114;     // 114
			std::uint32_t unk118;     // 118
			bool          unk11C;     // 11C
			bool          unk11D;     // 11D
			bool          unk11E;     // 11E
			bool          unk11F;     // 11F
			bool          unk120;     // 120
			bool          unk121;     // 121
			bool          unk122;     // 122
			std::uint8_t  pad123[5];  // 123
		};
		static_assert(sizeof(AE1799_RUNTIME_DATA) == 0x18);

		RUNTIME_DATA_ACCESSOR_VERSIONED_OPTIONAL_EX(AE1799_RUNTIME_DATA, GetAe1799RuntimeData, SKSE::RUNTIME_SSE_1_7_99, 0x110);
#endif

		~LockpickingMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04

		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03
		bool ProcessMouseMove(MouseMoveEvent* a_event) override;    // 04
		bool ProcessButton(ButtonEvent* a_event) override;          // 05
#endif

#ifndef SKYRIM_CROSS_VR
		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;  // 01
#endif

		[[nodiscard]] static TESObjectREFRPtr GetTargetReference();
		[[nodiscard]] static std::int32_t     GetCurrentLockDifficulty();

		static void OpenMenu(TESObjectREFR* a_target);  // a_ref must be locked and player must have lockpicks

		RUNTIME_CAST_ACCESSOR(MenuEventHandler, AsMenuEventHandler, 0x30, 0x40);
#ifndef SKYRIM_CROSS_VR
		RUNTIME_CAST_ACCESSOR(BSTEventSink<MenuOpenCloseEvent>, AsMenuOpenCloseEventSink, 0x40, 0x50);
#endif

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x48, 0x58);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 48, 58
#endif
	};
	STATIC_ASSERT_SIZE(LockpickingMenu, 0x110, 0x110, 0x120, 0x40);
}
#undef RUNTIME_DATA_CONTENT
