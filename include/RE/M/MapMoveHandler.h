#pragma once

#include "RE/B/BSTPoint.h"
#include "RE/M/MapInputHandler.h"

namespace RE
{
	class MapMoveHandler : public MapInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_MapMoveHandler;
		inline static constexpr auto VTABLE = VTABLE_MapMoveHandler;

		~MapMoveHandler() override;  // 00

		// override (MapInputHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03 (VR 06)
#endif

		// members
		BSTPoint2<float> unk18;  // 18
	};
	static_assert(sizeof(MapMoveHandler) == 0x20);
}
