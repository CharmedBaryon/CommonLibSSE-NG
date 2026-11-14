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

		// AE 1.7.99 inserts a float density multiplier at 0x30, which moves every member
		// from distanceFromWaterLevel on down by 4. The members above are the layout up to
		// AE 1.6.x and VR; on 1.7.99+ read them through these accessors.
		[[nodiscard]] float* GetDensityMultiplier() noexcept
		{
			return REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99) ? &REL::RelocateMember<float>(this, 0x30) : nullptr;
		}

		[[nodiscard]] float&         GetDistanceFromWaterLevel() noexcept { return REL::RelocateMemberIfNewer<float>(SKSE::RUNTIME_SSE_1_7_99, this, 0x30, 0x34); }
		[[nodiscard]] std::uint32_t& GetUnderwaterState() noexcept { return REL::RelocateMemberIfNewer<std::uint32_t>(SKSE::RUNTIME_SSE_1_7_99, this, 0x34, 0x38); }
		[[nodiscard]] float&         GetWaterHeight() noexcept { return REL::RelocateMemberIfNewer<float>(SKSE::RUNTIME_SSE_1_7_99, this, 0x38, 0x3C); }
		[[nodiscard]] std::uint32_t& GetMinSlopeDegrees() noexcept { return REL::RelocateMemberIfNewer<std::uint32_t>(SKSE::RUNTIME_SSE_1_7_99, this, 0x3C, 0x40); }
		[[nodiscard]] std::uint32_t& GetMaxSlopeDegrees() noexcept { return REL::RelocateMemberIfNewer<std::uint32_t>(SKSE::RUNTIME_SSE_1_7_99, this, 0x40, 0x44); }
	};
	static_assert(sizeof(CreateGrassParams) == 0x50);
}
