#pragma once

#include "RE/P/PlayerInputHandler.h"

namespace RE
{
	struct JumpHandler : public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_JumpHandler;
		inline static constexpr auto VTABLE = VTABLE_JumpHandler;

		~JumpHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;  // 04
#endif
	};
	STATIC_ASSERT_SIZE(JumpHandler, 0x10, 0x10, 0x28, 0x10);
}
