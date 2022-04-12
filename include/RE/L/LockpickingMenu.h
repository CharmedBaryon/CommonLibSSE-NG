#pragma once

#include "RE/B/BSSoundHandle.h"
#include "RE/B/BSTEvent.h"
#include "RE/I/IMenu.h"
#include "RE/M/MenuEventHandler.h"
#include "RE/N/NiMatrix3.h"

namespace RE
{
	class MenuOpenCloseEvent;
	class NiAVObject;
	class NiControllerManager;
	class NiControllerSequence;
	class TESObjectREFR;

	class ModelData
	{
	public:
		std::uint64_t unk00;   // 00
		std::uint64_t unk08;   // 08
		std::uint64_t unk10;   // 10
		std::uint64_t unk18;   // 00
		std::uint64_t unk20;   // 00
		NiAVObject*   object;  // 28
	};

	// menuDepth = 3
	// flags = kPausesGame | kDisablePauseMenu | kRequiresUpdate
	// context = kLockpicking
	class LockpickingMenu :
		public IMenu,  // 00
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		public MenuEventHandler,                 // 30
		public BSTEventSink<MenuOpenCloseEvent>  // 40
#else
		public MenuEventHandler  // 30
#endif
	{
	public:
		inline static auto                RTTI = RTTI_LockpickingMenu;
		constexpr static std::string_view MENU_NAME = "Lockpicking Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                            \
	ModelData*            lockpickShiv;        /* 00 */ \
	ModelData*            lockpick;            /* 08 */ \
	NiMatrix3             unk058;              /* 10 */ \
	NiPoint3              lockRotCenter;       /* 34 */ \
	NiControllerManager*  shivController;      /* 40 */ \
	NiControllerSequence* shivIntro;           /* 48 */ \
	NiControllerSequence* shivRotate;          /* 50 */ \
	NiControllerManager*  pickController;      /* 58 */ \
	NiControllerSequence* pickIntro;           /* 60 */ \
	NiControllerSequence* pickDamage;          /* 68 */ \
	NiControllerSequence* pickBreak;           /* 70 */ \
	NiControllerSequence* currentPickSequence; /* 78 */ \
	float                 pickKeyTime;         /* 80 */ \
	std::uint32_t         unk0CC;              /* 84 */ \
	NiControllerSequence* currentShivSequence; /* 88 */ \
	float                 shivKeyTime;         /* 90 */ \
	std::uint32_t         unk0DC;              /* 94 */ \
	float                 currentAngle;        /* 98 */ \
	float                 lockAngle;           /* 9C */ \
	std::uint32_t         unk0E8;              /* A0 */ \
	BSSoundHandle         unk0EC;              /* A4 */ \
	std::uint32_t         unk0F8;              /* B0 */ \
	std::uint32_t         unk0FC;              /* B4 */ \
	std::uint32_t         unk100;              /* B8 */ \
	std::uint32_t         unk104;              /* BC */ \
	std::uint16_t         unk108;              /* C0 */ \
	std::uint8_t          unk10A;              /* C2 */ \
	std::uint8_t          unk10B;              /* C3 */ \
	std::uint8_t          unk10C;              /* C4 */ \
	std::uint8_t          unk10D;              /* C5 */ \
	std::uint8_t          unk10E;              /* C6 */ \
	std::uint8_t          pad10F;              /* C7 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0xC8);

		~LockpickingMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04

#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;              // 01
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03
		bool ProcessMouseMove(MouseMoveEvent* a_event) override;    // 04
		bool ProcessButton(ButtonEvent* a_event) override;          // 05

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;  // 01
#endif

		[[nodiscard]] static TESObjectREFR* GetTargetReference();

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x48, 0x58);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x48, 0x58);
		}

		// members
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		RUNTIME_DATA_CONTENT  // 48, 58
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(LockpickingMenu) == 0x110);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(LockpickingMenu) == 0x120);
#endif
}
#undef RUNTIME_DATA_CONTENT
