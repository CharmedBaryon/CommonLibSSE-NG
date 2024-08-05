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
		bool CanProcess(InputEvent* a_event) override;                                  // 01
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;  // 04
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(JumpHandler) == 0x28);
#else
	static_assert(sizeof(JumpHandler) == 0x10);
#endif
}
