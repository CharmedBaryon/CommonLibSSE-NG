#pragma once

namespace RE
{
	struct GrassParam
	{
	public:
		// members
		const char*   modelName;          // 00
		FormID        grassFormID;        // 08
		float         positionRange;      // 0C
		float         heightRange;        // 10
		float         colorRange;         // 14
		std::uint32_t waveOffsetRange;    // 18
		float         wavePeriod;         // 1C
		bool          hasVertexLighting;  // 20
		bool          hasUniformScaling;  // 21
		bool          fitsToSlope;        // 22
		std::uint8_t  pad23;              // 23
		std::uint32_t pad24;              // 24
		float         unk28;              // 28
		float         unk2C;              // 2C
		float         unk30;              // 30
		float         unk34;              // 34
		float         unk38;              // 38
		float         unk3C;              // 3C
		float         unk40;              // 40
		float         unk44;              // 44
		float         unk48;              // 48
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GrassParam) == 0x50);
}
