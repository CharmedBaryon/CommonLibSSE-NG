#pragma once

#include "RE/P/PlayerInputHandler.h"

namespace RE
{
	struct ToggleRunHandler : public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_ToggleRunHandler;

		~ToggleRunHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;                                  // 01
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;  // 04
	private:
		KEEP_FOR_RE()
	};
#if !defined(ENABLE_SKYRIM_VR)
	static_assert(sizeof(ToggleRunHandler) == 0x10);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(ToggleRunHandler) == 0x28);
#endif
}
