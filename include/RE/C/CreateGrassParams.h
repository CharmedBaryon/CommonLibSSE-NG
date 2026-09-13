#pragma once

#include "RE/G/GrassParam.h"
#include "RE/N/NiPoint3.h"
#include "RE/T/TESObjectLAND.h"

namespace RE
{
	class CreateGrassParams
	{
	public:
		// members
		int                CellX;                   // 00
		int                CellY;                   // 04
		int                quad;                    // 08
		char               pad0C[4];                // 0C
		RE::TESObjectLAND* land;                    // 10
		RE::NiPoint3*      grassPatchStart;         // 18
		RE::GrassParam*    grassParam;              // 20
		float*             grassDensityPcts;        // 28
		float              distanceFromWaterLevel;  // 30
		std::uint32_t      underwaterState;         // 34
		float              waterHeight;             // 38
		std::uint32_t      minSlopeDegrees;         // 3C
		std::uint32_t      maxSlopeDegrees;         // 40
		char               pad44[0xC];              // 44
	};
	static_assert(sizeof(CreateGrassParams) == 0x50);
}
