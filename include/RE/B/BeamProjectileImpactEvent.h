#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	class BeamProjectile;

	struct BeamProjectileImpactEvent
	{
	public:
		// members
		BeamProjectile* source;     // 00
		NiPoint3        impactPos;  // 08
	};
	static_assert(sizeof(BeamProjectileImpactEvent) == 0x18);
}
