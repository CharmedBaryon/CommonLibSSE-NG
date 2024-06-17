#pragma once

#include "RE/P/PlayerInputHandler.h"

namespace RE
{
	struct SneakHandler : public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_SneakHandler;

		~SneakHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;                                  // 01
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;  // 04
	private:
		KEEP_FOR_RE()
	};
#if !defined(ENABLE_SKYRIM_VR)
	static_assert(sizeof(SneakHandler) == 0x10);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(SneakHandler) == 0x28);
#endif
}
