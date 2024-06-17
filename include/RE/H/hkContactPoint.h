#pragma once

#include "RE/H/hkVector4.h"

namespace RE
{
	class hkContactPoint
	{
	public:
		hkVector4 position;          // 00
		hkVector4 separatingNormal;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkContactPoint) == 0x20);
}
