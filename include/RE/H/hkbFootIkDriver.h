#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkQuaternion.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkVector4.h"

namespace RE
{
	class hkaFootPlacementIkSolver;

	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0)
	class hkbFootIkDriver : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbFootIkDriver;
		inline static constexpr auto VTABLE = VTABLE_hkbFootIkDriver;

		struct InternalLegData
		{
		public:
			// members
			float                     groundPosition[4];  // 00 (hkVector4)
			float                     groundNormal[4];    // 10 (hkVector4)
			hkaFootPlacementIkSolver* footIkSolver;       // 20
			float                     verticalError;      // 28
			bool                      hitSomething;       // 2C
			bool                      isPlantedMS;        // 2D
		};

		~hkbFootIkDriver() override;  // 00

		// members
		hkArray<InternalLegData> internalLegData;          // 10
		float                    errorOutTranslation[4];   // 20 (hkVector4)
		hkQuaternion             alignWithGroundRotation;  // 30
		std::uint64_t            unk40;                    // 40
		std::uint16_t            unk48;                    // 48
		std::uint8_t             disableFootIk;            // 4A - doFootIk checks this and bails if set
		std::uint8_t             unk4B;                    // 4B
		float                    deltaTime;                // 4C
	};
	static_assert(offsetof(hkbFootIkDriver, disableFootIk) == 0x4A);
	static_assert(sizeof(hkbFootIkDriver) == 0x50);
}
