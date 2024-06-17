#pragma once

#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class TESObjectREFR;

	struct TESResetEvent
	{
	public:
		// members
		NiPointer<TESObjectREFR> object;  // 0
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESResetEvent) == 0x8);
}
