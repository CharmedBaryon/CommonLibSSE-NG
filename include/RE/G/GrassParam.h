#pragma once

namespace RE
{
	struct GrassParam
	{
	public:
		// members
		const char*   modelName;                    // 00
		FormID        grassFormID;                  // 08
		float         positionRange;                // 0C
		float         heightRange;                  // 10
		float         colorRange;                   // 14
		std::uint32_t waveOffsetRange;              // 18
		float         wavePeriod;                   // 1C
		bool          hasVertexLighting;            // 20
		bool          hasUniformScaling;            // 21
		bool          fitsToSlope;                  // 22
		std::uint8_t  pad23;                        // 23
		std::uint32_t pad24;                        // 24
		float         denstityPctPerQuadVertex[9];  // 28
	};
	static_assert(sizeof(GrassParam) == 0x50);
}
