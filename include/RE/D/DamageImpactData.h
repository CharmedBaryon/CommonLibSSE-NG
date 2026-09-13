#pragma once

#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class bhkRigidBody;

	struct DamageImpactData
	{
	public:
		// members
		NiPointer<bhkRigidBody> body;      // 00
		NiPoint3                location;  // 08
		NiPoint3                normal;    // 14
		NiPoint3                velocity;  // 20
		float                   unk2C;     // 2C
		float                   unk30;     // 30
	};
	static_assert(sizeof(DamageImpactData) == 0x38);
}
