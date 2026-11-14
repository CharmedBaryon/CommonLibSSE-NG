#pragma once

#include "RE/B/BSLookAtModifierBoneData.h"
#include "RE/H/hkArray.h"
#include "RE/H/hkVector4.h"
#include "RE/H/hkbClipGenerator.h"
#include "RE/H/hkbModifier.h"

namespace RE
{
	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0)
	class BSLookAtModifier : public hkbModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSLookAtModifier;
		inline static constexpr auto VTABLE = VTABLE_BSLookAtModifier;

		// members
		bool                              lookAtTarget;                // 50
		std::uint8_t                      pad51[7];                    // 51
		hkArray<BSLookAtModifierBoneData> bones;                       // 58
		hkArray<BSLookAtModifierBoneData> eyeBones;                    // 68
		float                             limitAngleDegrees;           // 78
		float                             limitAngleThresholdDegrees;  // 7C
		bool                              continueLookOutsideOfLimit;  // 80
		std::uint8_t                      pad81[3];                    // 81
		float                             onGain;                      // 84
		float                             offGain;                     // 88
		bool                              useBoneGains;                // 8C
		std::uint8_t                      pad8D[3];                    // 8D
		float                             targetLocation[4];           // 90 (hkVector4)
		bool                              targetOutsideLimits;         // A0
		std::uint8_t                      padA1[7];                    // A1
		hkbEventProperty                  targetOutOfLimitEvent;       // A8
		bool                              lookAtCamera;                // B8
		std::uint8_t                      padB9[3];                    // B9
		float                             lookAtCameraX;               // BC
		float                             lookAtCameraY;               // C0
		float                             lookAtCameraZ;               // C4
		float                             timeStep;                    // C8
		bool                              allBonesValid;               // CC
		std::uint8_t                      padCD[3];                    // CD
		void*                             skeletonMemory;              // D0
		std::uint8_t                      padD8[8];                    // D8
	};
	static_assert(sizeof(BSLookAtModifier) == 0xE0);
}
