#pragma once

#include "RE/B/BSKeyboardDevice.h"

namespace RE
{
	class BSVirtualKeyboardDevice : public BSKeyboardDevice
	{
	public:
		struct kbInfo
		{
			using DoneCallback = void(void*, const char*);
			using CancelCallback = void();

			// members
			const char*     startingText;    // 00
			DoneCallback*   doneCallback;    // 08
			CancelCallback* cancelCallback;  // 10
			void*           userParam;       // 18
			std::uint32_t   maxChars;        // 20
		};
		static_assert(sizeof(kbInfo) == 0x28);

		inline static constexpr auto RTTI = RTTI_BSVirtualKeyboardDevice;
		inline static constexpr auto VTABLE = VTABLE_BSVirtualKeyboardDevice;

		~BSVirtualKeyboardDevice() override;  // 00

		// override (BSKeyboardDevice)
		void Unk_09(void) override;  // 09 - { return; }
		void Unk_0A(void) override;  // 0A - { return; }

		// add
		virtual void Start(const kbInfo* a_info) = 0;  // 0B
		virtual void Stop() = 0;                       // 0C
		virtual void UserCancelled() = 0;              // 0D

	protected:
		BSVirtualKeyboardDevice();  // The virtual keyboard device constructor does not set the device type to virtualKeyboard, it remains 'kKeyboard'
	};
	STATIC_ASSERT_SIZE(BSVirtualKeyboardDevice, 0x70, 0x70, 0x78, 0x8);
}
