#pragma once

#include "RE/M/MenuEventHandler.h"

namespace RE
{
	struct ScreenshotHandler : public MenuEventHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_ScreenshotHandler;
		inline static constexpr auto VTABLE = VTABLE_ScreenshotHandler;

		~ScreenshotHandler() override;  // 00

		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		bool ProcessButton(ButtonEvent* a_event) override;  // 05 (VR 08)
#endif

		// members
		bool          screenshotQueued;       // 10
		bool          multiScreenshotQueued;  // 11
		std::uint16_t pad12;                  // 12
		std::uint32_t pad14;                  // 14
	};
	static_assert(sizeof(ScreenshotHandler) == 0x18);
}
