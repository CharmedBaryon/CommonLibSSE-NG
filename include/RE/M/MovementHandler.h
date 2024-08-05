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
		bool CanProcess(InputEvent* a_event) override;                                          // 01
		void ProcessThumbstick(ThumbstickEvent* a_event, PlayerControlsData* a_data) override;  // 02
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;          // 04
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(MovementHandler) == 0x10);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(MovementHandler) == 0x28);
#endif
}
