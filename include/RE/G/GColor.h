#pragma once

namespace RE
{
	class GColor
	{
	public:
		struct RGB32
		{
			std::uint8_t blue;   // 0
			std::uint8_t green;  // 1
			std::uint8_t red;    // 2
			std::uint8_t alpha;  // 3
		};
		static_assert(sizeof(RGB32) == 0x4);

		union ColorData
		{
			RGB32         channels;
			std::uint32_t raw;
		};
		static_assert(sizeof(ColorData) == 0x4);

		constexpr GColor() noexcept :
			colorData{}
		{}

		constexpr GColor(std::uint8_t a_red, std::uint8_t a_green, std::uint8_t a_blue, std::uint8_t a_alpha = 255) noexcept :
			colorData{}
		{
			colorData.channels.red = a_red;
			colorData.channels.green = a_green;
			colorData.channels.blue = a_blue;
			colorData.channels.alpha = a_alpha;

			colorData.raw = (static_cast<std::uint32_t>(a_alpha) << 24) | (static_cast<std::uint32_t>(a_red) << 16) | (static_cast<std::uint32_t>(a_green) << 8) | a_blue;
		}

		constexpr GColor(std::uint32_t a_raw) noexcept :
			colorData{}
		{
			colorData.raw = a_raw;

			colorData.channels.alpha = (a_raw >> 24) & 0xFF;
			colorData.channels.red = (a_raw >> 16) & 0xFF;
			colorData.channels.green = (a_raw >> 8) & 0xFF;
			colorData.channels.blue = a_raw & 0xFF;
		}

		// members
		ColorData colorData;  // 0
	};
	static_assert(sizeof(GColor) == 0x4);
}
