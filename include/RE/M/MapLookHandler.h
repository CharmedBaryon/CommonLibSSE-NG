#pragma once

#include "RE/M/MapInputHandler.h"

namespace RE
{
	class MapLookHandler : public MapInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_MapLookHandler;
		inline static constexpr auto VTABLE = VTABLE_MapLookHandler;

		~MapLookHandler() override;  // 00

		// override (MapInputHandler)
#ifdef EXCLUSIVE_SKYRIM_VR
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03 (VR 06)
		bool ProcessMouseMove(MouseMoveEvent* a_event) override;    // 04 (VR 07)
		bool ProcessButton(ButtonEvent* a_event) override;          // 05 (VR 08)
#endif

		// members
		std::uint64_t unk18;  // 18
#ifdef EXCLUSIVE_SKYRIM_VR
		std::uint8_t unkVr20[0x8];
#endif
	};
	STATIC_ASSERT_SIZE(MapLookHandler, 0x20, 0x28);
}
