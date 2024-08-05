#pragma once

#include "RE/H/hkContactPoint.h"
#include "RE/H/hkpCdBody.h"

namespace RE
{
	struct hkpCdPoint
	{
		hkContactPoint   contact;         // 00
		hkVector4        unweldedNormal;  // 20
		const hkpCdBody* cdBodyA;         // 20
		const hkpCdBody* cdBodyB;         // 38
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpCdPoint) == 0x40);
}
