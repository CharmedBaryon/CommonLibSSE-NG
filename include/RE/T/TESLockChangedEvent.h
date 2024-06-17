#pragma once

#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class TESObjectREFR;

	struct TESLockChangedEvent
	{
	public:
		// members
		NiPointer<TESObjectREFR> lockedObject;  // 0
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESLockChangedEvent) == 0x8);
}
