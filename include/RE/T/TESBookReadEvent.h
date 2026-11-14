#pragma once

#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class TESObjectREFR;

	struct TESBookReadEvent
	{
	public:
		// members
		NiPointer<TESObjectREFR> ref;         // 00
		FormID                   baseFormID;  // 08
		std::uint16_t            uniqueID;    // 0C
		std::uint16_t            pad0E;       // 0E
	};
	static_assert(sizeof(TESBookReadEvent) == 0x10);
}
