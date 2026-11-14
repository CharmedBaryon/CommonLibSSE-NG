#pragma once

#include "RE/H/hkArray.h"

namespace RE
{
	class hkpDynamicsCpIdMgr
	{
	public:
		enum
		{
			kMaxIDsPerObject = 0x8
		};

		enum
		{
			kFreeValue = 0xff
		};

		// members
		hkInplaceArray<unsigned char, kMaxIDsPerObject> values;  // 00
	};
	static_assert(sizeof(hkpDynamicsCpIdMgr) == 0x18);
}
