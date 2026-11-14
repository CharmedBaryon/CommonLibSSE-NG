#pragma once

#include "RE/H/hkbShapeSetup.h"

#include "RE/C/CFilter.h"

namespace RE
{
	struct hkbRigidBodySetup
	{
		enum class Type
		{
			kInvalid = -1,
			kKeyframed,
			kDynamic,
			kFixed,
		};

		// members
		CFilter                         collisionFilterInfo;  // 00
		REX::EnumSet<Type, std::int8_t> type;                 // 04
		hkbShapeSetup                   shapeSetup;           // 05
	};
	static_assert(sizeof(hkbRigidBodySetup) == 0x20);
}
