#pragma once

namespace RE
{
	class TESGlobal;
	class TESWeather;

	struct WeatherType
	{
	public:
		// members
		TESWeather*   weather;  // 00
		std::uint32_t chance;   // 08
		std::uint32_t unk0C;    // 0C
		TESGlobal*    global;   // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(WeatherType) == 0x18);
}
