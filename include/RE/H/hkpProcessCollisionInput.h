#pragma once

#include "RE/H/hkStepInfo.h"
#include "RE/H/hkpCollisionAgentConfig.h"
#include "RE/H/hkpCollisionInput.h"
#include "RE/H/hkpCollisionQualityInfo.h"

namespace RE
{
	struct hkpAgent1nSector;

	struct hkpProcessCollisionInput : public hkpCollisionInput
	{
	public:
		// members
		hkStepInfo               stepInfo;                       // 60
		hkpCollisionQualityInfo* collisionQualityInfo;           // 70
		hkpAgent1nSector*        spareAgentSector;               // 78
		void*                    dynamicsInfo;                   // 80
		bool                     enableDeprecatedWelding;        // 88
		bool                     allowToSkipConfirmedCallbacks;  // 89
		std::uint16_t            pad8A;                          // 8A
		std::uint32_t            pad8C;                          // 8C
		hkpCollisionAgentConfig* config;                         // 90
																 // tail padded to 0xA0: hkStepInfo is alignas(0x10), so the struct is 16-aligned (members end at 0x98)
	};
	static_assert(sizeof(hkpProcessCollisionInput) == 0xA0);
}
