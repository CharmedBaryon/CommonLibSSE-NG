#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	class NiPlane
	{
	public:
		// members
		NiPoint3 normal;    // 00
		float    constant;  // 0C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(NiPlane) == 0x10);
}
