#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTSingleton.h"
#include "RE/B/BSTSmartPointer.h"

namespace RE
{
	class InputEvent;
	class MenuEventHandler;
	class MenuModeChangeEvent;
	struct ClickHandler;
	struct ConsoleOpenHandler;
	struct DirectionHandler;
	struct FavoritesHandler;
	struct MenuOpenHandler;
	struct QuickSaveLoadHandler;
	struct ScreenshotHandler;

	class MenuControls :
		public BSTEventSink<InputEvent*>,         // 00
		public BSTSingletonSDM<MenuControls>,     // 10
		public BSTEventSink<MenuModeChangeEvent>  // 08
	{
	public:
		struct QueuedReg
		{
		public:
			QueuedReg(MenuEventHandler* a_handler, bool a_add);
			~QueuedReg() = default;

			// members
			MenuEventHandler* handler;  // 00
			bool              add;      // 08
			std::uint8_t      pad08;    // 09
			std::uint16_t     pad09;    // 0A
			std::uint32_t     pad0A;    // 0C
		};
		static_assert(sizeof(QueuedReg) == 0x10);

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                    \
	bool          isProcessing; /* 80, VR 88 */ \
	bool          beastForm;    /* 81, VR 89 */ \
	bool          remapMode;    /* 82, VR 8A */ \
	std::uint8_t  unk83;        /* 83, VR 8B */ \
	std::uint32_t unk84;        /* 84, VR 8C */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x8);

		~MenuControls() override;  // 00

		// override (BSTEventSink<InputEvent*>)
		BSEventNotifyControl ProcessEvent(InputEvent* const* a_event, BSTEventSource<InputEvent*>* a_eventSource) override;  // 01

		// override (BSTEventSink<MenuModeChangeEvent>)
		BSEventNotifyControl ProcessEvent(const MenuModeChangeEvent* a_event, BSTEventSource<MenuModeChangeEvent>* a_eventSource) override;  // 01

		static MenuControls* GetSingleton();

		void               AddHandler(MenuEventHandler* a_handler);
		[[nodiscard]] bool InBeastForm() const noexcept { return GetRuntimeData().beastForm; }
		void               RegisterHandler(MenuEventHandler* a_handler);
		void               RemoveHandler(MenuEventHandler* a_handler);
		bool               QueueScreenshot();
		void               UnregisterHandler(MenuEventHandler* a_handler);

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x80, 0x88);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x80, 0x88);
		}

		[[nodiscard]] std::uint64_t GetOcclusionCullingToggleHandler() noexcept
		{
			if SKYRIM_REL_CONSTEXPR (!REL::Module::IsVR()) {
				return 0;
			}
			return REL::RelocateMember<std::uint64_t>(this, 0, 0x80);
		}

		// members
		std::uint8_t                pad11;                 // 11
		std::uint16_t               pad12;                 // 12
		std::uint32_t               pad14;                 // 14
		BSTArray<MenuEventHandler*> handlers;              // 18
		BSTArray<QueuedReg>         regBuffer;             // 30
		ClickHandler*               clickHandler;          // 48
		DirectionHandler*           directionHandler;      // 50
		ConsoleOpenHandler*         consoleOpenHandler;    // 58
		QuickSaveLoadHandler*       quickSaveLoadHandler;  // 60
		MenuOpenHandler*            menuOpenHandler;       // 68
		FavoritesHandler*           favoritesHandler;      // 70
		ScreenshotHandler*          screenshotHandler;     // 78
#ifndef ENABLE_SKYRIM_VR
#elif defined(EXCLUSIVE_SKYRIM_VR)
		std::uint64_t occlusionCullingToggleHandler;  // 80
#endif
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 80, 88
#endif
	private:
		KEEP_FOR_RE()
	};
	static_assert(offsetof(MenuControls, handlers) == 0x18);

#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(MenuControls) == 0x88);
	static_assert(offsetof(MenuControls, remapMode) == 0x82);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(offsetof(MenuControls, remapMode) == 0x8A);
	static_assert(sizeof(MenuControls) == 0x90);
#else
	static_assert(sizeof(MenuControls) == 0x80);
#endif
}
#undef RUNTIME_DATA_CONTENT
