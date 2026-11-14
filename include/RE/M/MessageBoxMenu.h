#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSString.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IMenu.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class IMessageBoxCallback;
	class MessageBoxData;

	// menuDepth = 10
	// flags = kPausesGame | kAlwaysOpen | kUsesCursor | kModal
	// context = kMenuMode
	class MessageBoxMenu : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_MessageBoxMenu;
		inline static constexpr auto      VTABLE = VTABLE_MessageBoxMenu;
		constexpr static std::string_view MENU_NAME = "MessageBoxMenu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT            \
	bool          isPopulated; /* 00 */ \
	std::uint8_t  pad31;       /* 01 */ \
	std::uint16_t pad32;       /* 02 */ \
	std::uint32_t pad34;       /* 04 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x8);

		~MessageBoxMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04

		template <class... Args>
		static bool Create(const char* a_message, void (*a_callback)(std::uint8_t), std::uint8_t a_buttonPressOffset, std::int32_t a_warningType, std::int32_t a_menuDepth, Args... a_buttons)
		{
			// It reads the buttons starting with the first button until it reaches nullptr
			static_assert((std::is_same_v<std::decay_t<Args>, const char*> && ...), "arguments must all be const char*");
			using func_t = bool(const char*, void (*)(std::uint8_t), std::uint8_t, std::int32_t, std::int32_t, ...);
			static REL::Relocation<func_t> func{ RELOCATION_ID(51420, 52269) };
			return func(a_message, a_callback, a_buttonPressOffset, a_warningType, a_menuDepth, a_buttons..., nullptr);
		}

		static bool Create(RE::BSString& a_message, const BSTSmartPointer<IMessageBoxCallback>& a_callback, std::uint8_t a_buttonPressOffset, std::int32_t a_warningType, std::int32_t a_menuDepth, const BSTArray<BSString>& a_buttons);

		static MessageBoxMenu*            GetCurrentMessageBoxMenu();  // inlined in SE
		static BSTArray<MessageBoxData*>& GetQueue();
		static BSSpinLock&                GetQueueLock();  // used while adding and removing
		static std::uint32_t              GetQueueSize();
		static void                       QueueMessage(MessageBoxData* a_data);

		// The currently-displayed message (the most recently queued; the queue is LIFO), or nullptr if
		// no message box is active. Read bodyText/buttonText/warningType/buttonPressOffset from it.
		static MessageBoxData* GetCurrentMessageBoxData();
		// Removes a_data from the message-box queue and destroys it.
		static void RemoveMessageFromQueue(MessageBoxData* a_data);
		// Programmatically answer the active message box as if button a_buttonIndex (0-based into
		// buttonText) was clicked: pops the message, hides the menu if the queue empties, then invokes
		// the data's IMessageBoxCallback with (buttonPressOffset + a_buttonIndex).
		static void SelectOption(std::int32_t a_buttonIndex);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x30, 0x40);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 30, 40
#endif
	};
	STATIC_ASSERT_SIZE(MessageBoxMenu, 0x38, 0x38, 0x48, 0x30);
}
#undef RUNTIME_DATA_CONTENT
