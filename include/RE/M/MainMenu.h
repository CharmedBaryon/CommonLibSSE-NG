#pragma once

#include "RE/B/BSScaleformExternalTexture.h"
#include "RE/B/BSTEvent.h"
#include "RE/G/GFxFunctionHandler.h"
#include "RE/I/IMenu.h"

namespace RE
{
	class BSSaveDataEvent;
	class BSSystemEvent;
	struct MapMenuMarker;

	// menuDepth = 0
	// flags = kPausesGame | kDisablePauseMenu | kRequiresUpdate | kUpdateUsesCursor | kApplicationMenu
	// context = kMenuMode
	class MainMenu :
#ifndef SKYRIM_CROSS_VR
		public IMenu,                         // 00
		public BSTEventSink<BSSystemEvent>,   // 30
		public BSTEventSink<BSSaveDataEvent>  // 38
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_MainMenu;
		constexpr static std::string_view MENU_NAME = "Main Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                              \
	BSScaleformExternalTexture gamerIconTexture; /* 00 */ \
	std::uint32_t              unk68;            /* 18 */ \
	std::uint8_t               unk6C;            /* 1C */ \
	std::uint8_t               unk6D;            /* 1D */ \
	std::uint8_t               unk6E;            /* 1E */ \
	std::uint8_t               pad6F;            /* 1F */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x20);

		~MainMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;                       // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;                         // 04
		void               AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;  // 05

#ifndef SKYRIM_CROSS_VR
		// override (BSTEventSink<BSSystemEvent>)
		BSEventNotifyControl ProcessEvent(const BSSystemEvent* a_event, BSTEventSource<BSSystemEvent>* a_eventSource) override;  // 01
		// override (BSTEventSink<BSSaveDataEvent>)
		BSEventNotifyControl ProcessEvent(const BSSaveDataEvent* a_event, BSTEventSource<BSSaveDataEvent>* a_eventSource) override;  // 01
#endif

		[[nodiscard]] BSTEventSink<BSSystemEvent>* AsBSSystemEventSink() noexcept
		{
			return &REL::RelocateMember<BSTEventSink<BSSystemEvent>>(this, 0x30, 0x40);
		}

		[[nodiscard]] const BSTEventSink<BSSystemEvent>* AsBSSystemEventSink() const noexcept
		{
			return const_cast<MainMenu*>(this)->AsBSSystemEventSink();
		}

		[[nodiscard]] BSTEventSink<BSSaveDataEvent>* AsBSSaveDataEventSink() noexcept
		{
			return &REL::RelocateMember<BSTEventSink<BSSaveDataEvent>>(this, 0x38, 0x48);
		}

		[[nodiscard]] const BSTEventSink<BSSaveDataEvent>* AsBSSaveDataEventSink() const noexcept
		{
			return const_cast<MainMenu*>(this)->AsBSSaveDataEventSink();
		}

		[[nodiscard]] GFxFunctionHandler* AsGFxFunctionHandler() noexcept
		{
			return &REL::RelocateMember<GFxFunctionHandler>(this, 0x40, 0x50);
		}

		[[nodiscard]] const GFxFunctionHandler* AsGFxFunctionHandler() const noexcept
		{
			return const_cast<MainMenu*>(this)->AsGFxFunctionHandler();
		}

		[[nodiscard]] BSTEventSink<BSGamerProfileEvent>* AsBSGamerProfileEventSink() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return &REL::RelocateMember<BSTEventSink<BSGamerProfileEvent>>(this, 0, 0x50);
			}
		}

		[[nodiscard]] const BSTEventSink<BSGamerProfileEvent>* AsBSGamerProfileEventSink() const noexcept
		{
			return const_cast<MainMenu*>(this)->AsBSGamerProfileEventSink();
		}

		[[nodiscard]] const MenuEventHandler* AsMenuEventHandler() const noexcept
		{
			return const_cast<MainMenu*>(this)->AsMenuEventHandler();
		}

		[[nodiscard]] MenuEventHandler* AsMenuEventHandler() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return &REL::RelocateMember<MenuEventHandler>(this, 0, 0x58);
			}
		}

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x50, 0x60);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x50, 0x60);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 50, 60
#endif
	private:
		KEEP_FOR_RE();
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(MainMenu) == 0x60);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(MainMenu) == 0x70);
#else
	static_assert(sizeof(MainMenu) == 0x30);
#endif
}
#undef RUNTIME_DATA_CONTENT
