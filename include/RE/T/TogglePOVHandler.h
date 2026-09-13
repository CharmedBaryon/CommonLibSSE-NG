#pragma once

#include "RE/H/HeldStateHandler.h"

namespace RE
{
	struct TogglePOVHandler : public HeldStateHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_TogglePOVHandler;
		inline static constexpr auto VTABLE = VTABLE_TogglePOVHandler;

		~TogglePOVHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;  // 04
#endif

		// members
		bool          pressRegistered;  // 18
		std::uint8_t  pad19;            // 19
		std::uint16_t pad1A;            // 1A
		std::uint32_t pad1C;            // 1C
	};
	STATIC_ASSERT_SIZE(TogglePOVHandler, 0x20, 0x38);
}
