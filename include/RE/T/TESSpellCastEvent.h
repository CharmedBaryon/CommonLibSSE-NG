#pragma once

#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class TESObjectREFR;

	struct TESSpellCastEvent
	{
	public:
		// members
		NiPointer<TESObjectREFR> object;  // 00
		FormID                   spell;   // 08
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESSpellCastEvent) == 0x10);
}
