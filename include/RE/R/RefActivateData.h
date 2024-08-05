#pragma once

#include "RE/B/BSPointerHandle.h"

namespace RE
{
	struct REF_ACTIVATE_DATA
	{
	public:
		// members
		ObjectRefHandle activateRef;    // 00
		float           activateDelay;  // 04
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(REF_ACTIVATE_DATA) == 0x8);
}
