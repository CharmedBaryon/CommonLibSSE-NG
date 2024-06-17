#pragma once

#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BGSLocation;
	class TESObjectREFR;

	struct TESActorLocationChangeEvent
	{
	public:
		// members
		NiPointer<TESObjectREFR> actor;
		BGSLocation*             oldLoc;
		BGSLocation*             newLoc;

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESActorLocationChangeEvent) == 0x18);
}
