#pragma once

#include "RE/H/hkTransform.h"
#include "RE/H/hkpCdBody.h"

namespace RE
{
	class hkpContactMgr;
	struct hkpProcessCollisionInput;

	// hkpAgent3::ProcessInput
	struct hkpAgent3ProcessInput
	{
	public:
		// members
		const hkpCdBody*                bodyA;          // 00
		const hkpCdBody*                bodyB;          // 08
		const hkpCdBody*                overrideBodyA;  // 10
		const hkpProcessCollisionInput* input;          // 18
		hkpContactMgr*                  contactMgr;     // 20
		std::uint64_t                   pad28;          // 28
		hkTransform                     aTb;            // 30
		float                           distAtT1;       // 70
		std::uint32_t                   pad74;          // 74
		std::uint32_t                   pad78;          // 78
		std::uint32_t                   pad7C;          // 7C
	};
	static_assert(sizeof(hkpAgent3ProcessInput) == 0x80);
}
