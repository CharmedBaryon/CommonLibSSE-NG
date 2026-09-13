#pragma once

#include "RE/P/PlayerInputHandler.h"

namespace RE
{
	struct ToggleRunHandler : public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_ToggleRunHandler;
		inline static constexpr auto VTABLE = VTABLE_ToggleRunHandler;

		~ToggleRunHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;  // 04
#endif
	};
	STATIC_ASSERT_SIZE(ToggleRunHandler, 0x10, 0x28);
}
