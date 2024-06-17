#pragma once

#include "RE/H/hkMatrix3.h"

namespace RE
{
	class alignas(0x10) hkRotation : public hkMatrix3
	{
	public:
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkRotation) == 0x30);
}
