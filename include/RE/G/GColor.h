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

		constexpr std::uint8_t GetRed() const noexcept { return colorData.channels.red; }
		constexpr std::uint8_t GetGreen() const noexcept { return colorData.channels.green; }
		constexpr std::uint8_t GetBlue() const noexcept { return colorData.channels.blue; }
		constexpr std::uint8_t GetAlpha() const noexcept { return colorData.channels.alpha; }

		constexpr void GetRGBAFloat(float& a_red, float& a_green, float& a_blue, float& a_alpha) const noexcept
		{
			a_red = GetRed() == 0 ? 0.0f : GetRed() / 255.0f;
			a_green = GetGreen() == 0 ? 0.0f : GetGreen() / 255.0f;
			a_blue = GetBlue() == 0 ? 0.0f : GetBlue() / 255.0f;
			a_alpha = GetAlpha() == 0 ? 0.0f : GetAlpha() / 255.0f;
		}

		bool operator==(const GColor& a_rhs) const { return colorData.raw == a_rhs.colorData.raw; }
		bool operator!=(const GColor& a_rhs) const { return !(*this == a_rhs); }

		// members
		ColorData colorData;  // 0
	};
	static_assert(sizeof(GColor) == 0x4);
}
