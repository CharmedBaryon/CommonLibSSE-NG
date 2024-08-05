#pragma once

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
		bool CanProcess(InputEvent* a_event) override;              // 01
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03

		// members
		std::uint64_t unk18;  // 18
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(MapMoveHandler) == 0x20);
}
