#pragma once

#include "RE/N/NiSmartPointer.h"
#include "RE/T/TESObjectREFR.h"

namespace RE
{
	class TESObjectCELL;

	struct TESCellAttachDetachEvent
	{
		NiPointer<TESObjectREFR> reference;  // 00
		bool                     attached;   // 08	- 01 - attached, 00 - detached
	private:
		KEEP_FOR_RE()
	};

	static_assert(sizeof(TESCellAttachDetachEvent) == 0x10);
}
