#pragma once

#include "RE/P/PlayerInputHandler.h"

namespace RE
{
	struct LookHandler : public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_LookHandler;
		inline static constexpr auto VTABLE = VTABLE_LookHandler;

		~LookHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;                                          // 01
		void ProcessThumbstick(ThumbstickEvent* a_event, PlayerControlsData* a_data) override;  // 02
		void ProcessMouseMove(MouseMoveEvent* a_event, PlayerControlsData* a_data) override;    // 03
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(LookHandler) == 0x28);
#else
	static_assert(sizeof(LookHandler) == 0x10);
#endif
}
