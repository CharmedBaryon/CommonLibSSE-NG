#pragma once

#include "RE/P/PlayerInputHandler.h"

namespace RE
{
	struct MovementHandler : public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandler;
		inline static constexpr auto VTABLE = VTABLE_MovementHandler;

		~MovementHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		void ProcessThumbstick(ThumbstickEvent* a_event, PlayerControlsData* a_data) override;  // 02
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;          // 04
#endif
	};
	STATIC_ASSERT_SIZE(MovementHandler, 0x10, 0x28);
}
