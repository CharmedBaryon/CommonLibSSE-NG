#pragma once

#include "RE/H/HeldStateHandler.h"

namespace RE
{
	struct SprintHandler : public HeldStateHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_SprintHandler;

		~SprintHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;                                  // 01
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;  // 04
	private:
		KEEP_FOR_RE()
	};
#if !defined(ENABLE_SKYRIM_VR)
	static_assert(sizeof(SprintHandler) == 0x18);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(SprintHandler) == 0x30);
#endif
}
