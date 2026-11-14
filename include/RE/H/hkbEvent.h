#pragma once

#include "RE/H/hkbEventBase.h"

namespace RE
{
	class hkbNode;

	class hkbEvent : public hkbEventBase
	{
	public:
		// members
		hkbNode* sender;  // 10
	};
	static_assert(sizeof(hkbEvent) == 0x18);
}
