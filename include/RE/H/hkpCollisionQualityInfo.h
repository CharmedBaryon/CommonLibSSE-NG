#pragma once

namespace RE
{
	struct hkpCollisionQualityInfo
	{
	public:
		// members
		float         keepContact;               // 00
		float         create4dContact;           // 04
		float         createContact;             // 08
		float         manifoldTimDistance;       // 0C
		std::int32_t  useContinuousPhysics;      // 10 - hkBool32
		bool          useSimpleToiHandling;      // 14
		std::uint8_t  pad15;                     // 15
		std::uint16_t pad16;                     // 16
		float         minSeparation;             // 18
		float         minExtraSeparation;        // 1C
		float         minSafeDeltaTime;          // 20
		float         minAbsoluteSafeDeltaTime;  // 24
		float         toiSeparation;             // 28
		float         toiExtraSeparation;        // 2C
		float         toiAccuracy;               // 30
		float         maxContraintViolation;     // 34
		float         minToiDeltaTime;           // 38
		std::uint16_t constraintPriority;        // 3C
		bool          enableToiWeldRejection;    // 3E
		std::uint8_t  pad3F;                     // 3F
	};
	static_assert(sizeof(hkpCollisionQualityInfo) == 0x40);
}
