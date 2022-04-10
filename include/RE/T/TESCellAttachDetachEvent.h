#pragma once

#include "RE/T/TESObjectREFR.h"
#include <cstdint>

namespace RE
{
	class TESObjectCELL;

	struct TESCellAttachDetachEvent
	{
		TESObjectREFR* reference;  // 00
		std::uint8_t   attached;   // 08	- 01 - attached, 00 - detached
	};

	static_assert(sizeof(TESCellAttachDetachEvent) == 0x10);
}
