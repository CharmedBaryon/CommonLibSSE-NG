#pragma once

#include "RE/H/hkStringPtr.h"

namespace RE
{
	struct hkbShapeSetup
	{
		enum class Type
		{
			kCapsule = 0,
			kFile,
		};

		// members
		float                               capsuleHeight;  // 00
		float                               capsuleRadius;  // 04
		hkStringPtr                         fileName;       // 08
		stl::enumeration<Type, std::int8_t> type;           // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkbShapeSetup) == 0x18);
}
