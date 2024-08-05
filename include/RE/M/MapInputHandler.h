#pragma once

#include "RE/M/MenuEventHandler.h"

namespace RE
{
	class MapMenu;

	class MapInputHandler : public MenuEventHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_MapInputHandler;
		inline static constexpr auto VTABLE = VTABLE_MapInputHandler;

		virtual ~MapInputHandler();  // 00

		// members
		MapMenu* mapMenu;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(MapInputHandler) == 0x18);
}
