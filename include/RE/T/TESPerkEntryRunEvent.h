#pragma once

#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class TESObjectREFR;

	struct TESPerkEntryRunEvent
	{
	public:
		// members
		NiPointer<TESObjectREFR> targetRef;     // 00
		NiPointer<TESObjectREFR> perkOwnerRef;  // 08
		FormID                   perkFormID;    // 10
		std::uint16_t            perkEntryID;   // 14
	};
	static_assert(sizeof(TESPerkEntryRunEvent) == 0x18);
}
