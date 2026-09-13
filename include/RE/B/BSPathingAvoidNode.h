#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSPathingAvoidNode
	{
	public:
		enum class AvoidNodeType
		{
			AVOID_NODE_SPHERE = 0,
			AVOID_NODE_CYLINDER,
			AVOID_NODE_SPHERE_ACTOR,
			AVOID_NODE_SPHERE_TARGET,
			AVOID_NODE_SPHERE_THREAT,
			AVOID_NODE_SPHERE_OBSTACLE
		};

		NiPoint3                    point1;         // 00
		NiPoint3                    point2;         // 0C
		float                       radius;         // 18
		float                       cost;           // 1C
		REX::EnumSet<AvoidNodeType> avoidNodeType;  // 20
	};
	static_assert(sizeof(BSPathingAvoidNode) == 0x24);

}
