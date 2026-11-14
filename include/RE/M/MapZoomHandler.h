#pragma once

#include "RE/M/MapInputHandler.h"

namespace RE
{
	class MapZoomHandler : public MapInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_MapZoomHandler;
		inline static constexpr auto VTABLE = VTABLE_MapZoomHandler;

		~MapZoomHandler() override;  // 00

		// override (MapInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		bool ProcessButton(ButtonEvent* a_event) override;  // 05 (VR 08)
#endif
	};
	static_assert(sizeof(MapZoomHandler) == 0x18);
}
