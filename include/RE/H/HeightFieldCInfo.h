#pragma once

#include <array>
#include <cstdint>

namespace RE
{
	class HeightFieldCInfo
	{
	public:
		std::uint64_t unk00;      // 00
		std::uint64_t unk08;      // 08
		float         scaleX;     // 10 - havok units between grid columns
		float         scaleY;     // 14 - havok units per stored height unit
		float         scaleZ;     // 18 - havok units between grid rows
		float         scaleW;     // 1C
		std::int32_t  xRes;       // 20 - samples along X (17 for the vanilla grid)
		std::int32_t  zRes;       // 24 - samples along Z (17 for the vanilla grid)
		float         minHeight;  // 28 - heightBias plus the lowest sample
		float         maxHeight;  // 2C - heightBias plus the highest sample

		std::uint8_t                 unk30;  // 30
		std::array<std::uint8_t, 15> pad31;  // 31

		const float*  heights;     // 40 - the quadrant's grid, row major
		float         heightBias;  // 48 - world Z of a stored height of zero
		std::uint32_t pad4C;       // 4C
		bool          unk50;       // 50

		std::array<std::uint8_t, 7> pad51;  // 51
	};
	static_assert(offsetof(HeightFieldCInfo, scaleX) == 0x10);
	static_assert(offsetof(HeightFieldCInfo, xRes) == 0x20);
	static_assert(offsetof(HeightFieldCInfo, minHeight) == 0x28);
	static_assert(offsetof(HeightFieldCInfo, heights) == 0x40);
	static_assert(offsetof(HeightFieldCInfo, heightBias) == 0x48);
	static_assert(sizeof(HeightFieldCInfo) == 0x58);
}
