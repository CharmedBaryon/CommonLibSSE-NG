#include "catch2/catch_all.hpp"

#include "../../../src/RE/S/SkyPrecipitation.h"

#include <bit>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

static_assert(std::is_same_v<decltype(RE::TESWeather::Data::precipitationBeginFadeIn), std::uint8_t>);
static_assert(std::is_same_v<decltype(RE::TESWeather::Data::precipitationEndFadeOut), std::uint8_t>);
static_assert(offsetof(RE::TESWeather::Data, precipitationBeginFadeIn) == 0x6);
static_assert(offsetof(RE::TESWeather::Data, precipitationEndFadeOut) == 0x7);

namespace
{
	using Runtime = REL::Module::Runtime;
	constexpr Runtime supportedRuntimes[]{
#ifdef ENABLE_SKYRIM_SE
		Runtime::SE,
#endif
#ifdef ENABLE_SKYRIM_AE
		Runtime::AE,
#endif
#ifdef ENABLE_SKYRIM_VR
		Runtime::VR,
#endif
	};

	struct RuntimeFixture
	{
		explicit RuntimeFixture(Runtime a_runtime)
		{
			const auto version = a_runtime == Runtime::AE ? REL::Version{ 1, 6, 1170, 0 } :
			                     a_runtime == Runtime::VR ? REL::Version{ 1, 4, 15, 0 } :
			                                                REL::Version{ 1, 5, 97, 0 };
			REQUIRE(REL::Module::mock(version, a_runtime, L"WeatherTest.exe", 0x1000));
		}
		~RuntimeFixture() { REL::Module::reset(); }
	};

	struct Weather
	{
		RE::TESWeather::Data data{};
	};

	struct WeatherState
	{
		const Weather* currentWeather{};
		const Weather* lastWeather{};
		float          currentWeatherPct{};
	};

	void CheckPrecipitation(const WeatherState& a_sky, bool a_rain, bool a_snow)
	{
		CHECK(RE::detail::HasPrecipitation(a_sky, RE::TESWeather::WeatherDataFlag::kRainy) == a_rain);
		CHECK(RE::detail::HasPrecipitation(a_sky, RE::TESWeather::WeatherDataFlag::kSnow) == a_snow);
	}
}

TEST_CASE("Sky/Precipitation covers every stored byte", "[unit][weather]")
{
	const auto runtime = GENERATE(Catch::Generators::from_range(supportedRuntimes));
	CAPTURE(runtime);
	RuntimeFixture fixture(runtime);
	WeatherState   sky;
	Weather        weather;

	for (auto flag : { RE::TESWeather::WeatherDataFlag::kRainy, RE::TESWeather::WeatherDataFlag::kSnow }) {
		weather.data.flags = flag;
		for (unsigned value = 0; value <= 255; ++value) {
			weather.data.precipitationBeginFadeIn = static_cast<std::uint8_t>(value);
			weather.data.precipitationEndFadeOut = static_cast<std::uint8_t>(value);
			for (float progress : { 0.0F, 0.25F, 0.5F, 0.75F, 1.0F }) {
				CAPTURE(flag, value, progress);
				sky.currentWeatherPct = progress;
				sky.currentWeather = &weather;
				sky.lastWeather = nullptr;
				// Integer-scaled thresholds keep the oracle independent of float rounding.
				const bool started = value * 999.0 < progress * 255000.0;
				CheckPrecipitation(sky, started && flag == RE::TESWeather::WeatherDataFlag::kRainy,
					started && flag == RE::TESWeather::WeatherDataFlag::kSnow);
				sky.currentWeather = nullptr;
				sky.lastWeather = &weather;
				const bool remaining = value * 999.0 + 255.0 > progress * 255000.0;
				CheckPrecipitation(sky, remaining && flag == RE::TESWeather::WeatherDataFlag::kRainy,
					remaining && flag == RE::TESWeather::WeatherDataFlag::kSnow);
			}
		}
	}
}

TEST_CASE("Sky/Precipitation preserves native endpoint margins", "[unit][weather]")
{
	const auto runtime = GENERATE(Catch::Generators::from_range(supportedRuntimes));
	CAPTURE(runtime);
	RuntimeFixture fixture(runtime);
	WeatherState   sky;
	Weather        weather;
	weather.data.flags.set(RE::TESWeather::WeatherDataFlag::kRainy, RE::TESWeather::WeatherDataFlag::kSnow);
	auto check = [&](bool a_expected) { CheckPrecipitation(sky, a_expected, a_expected); };

	sky.currentWeather = &weather;
	weather.data.precipitationBeginFadeIn = 0;
	sky.currentWeatherPct = 0.0F;
	check(false);
	sky.currentWeatherPct = 0.0005F;
	check(true);
	weather.data.precipitationBeginFadeIn = 255;
	sky.currentWeatherPct = 0.998F;
	check(false);
	sky.currentWeatherPct = 0.9995F;
	check(true);
	sky.currentWeatherPct = 1.0F;
	check(true);

	sky.currentWeather = nullptr;
	sky.lastWeather = &weather;
	weather.data.precipitationEndFadeOut = 0;
	sky.currentWeatherPct = 0.0F;
	check(true);
	sky.currentWeatherPct = 0.0005F;
	check(true);
	sky.currentWeatherPct = 0.001F;
	check(false);
	weather.data.precipitationEndFadeOut = 255;
	sky.currentWeatherPct = 0.9995F;
	check(true);
	sky.currentWeatherPct = 1.0F;
	check(false);
}

TEST_CASE("Sky/Precipitation combines matching weather only", "[unit][weather]")
{
	const auto runtime = GENERATE(Catch::Generators::from_range(supportedRuntimes));
	CAPTURE(runtime);
	RuntimeFixture fixture(runtime);
	WeatherState   sky;
	Weather        current;
	Weather        last;
	CheckPrecipitation(sky, false, false);
	sky.currentWeather = &current;
	sky.lastWeather = &last;
	current.data.flags = RE::TESWeather::WeatherDataFlag::kSnow;
	current.data.precipitationBeginFadeIn = 64;
	last.data.flags = RE::TESWeather::WeatherDataFlag::kRainy;
	last.data.precipitationEndFadeOut = 192;
	sky.currentWeatherPct = 0.25F;
	CheckPrecipitation(sky, true, false);
	sky.currentWeatherPct = 0.5F;
	CheckPrecipitation(sky, true, true);
	sky.currentWeatherPct = 0.754F;
	CheckPrecipitation(sky, false, true);
	current.data.flags = RE::TESWeather::WeatherDataFlag::kPleasant;
	last.data.flags = RE::TESWeather::WeatherDataFlag::kCloudy;
	CheckPrecipitation(sky, false, false);
}

TEST_CASE("Sky/Precipitation preserves native float boundaries", "[unit][weather]")
{
	const auto runtime = GENERATE(Catch::Generators::from_range(supportedRuntimes));
	CAPTURE(runtime);
	RuntimeFixture fixture(runtime);
	WeatherState   sky;
	Weather        weather;
	weather.data.flags.set(RE::TESWeather::WeatherDataFlag::kRainy, RE::TESWeather::WeatherDataFlag::kSnow);

	struct NativeFade
	{
		std::uint8_t  value;
		std::uint32_t aeIncoming;
		std::uint32_t aeOutgoing;
		std::uint32_t vrIncoming;
		std::uint32_t vrOutgoing;
	};
	constexpr NativeFade nativeFades[]{
		{ 1, 0x3B805F9C, 0x3BA12437, 0x3B805F9C, 0x3BA12438 },
		{ 5, 0x3CA07783, 0x3CA8A8A9, 0x3CA07782, 0x3CA8A8A9 },
		{ 255, 0x3F7FBE79, 0x3F800000, 0x3F7FBE77, 0x3F800000 },
	};

	for (const auto& native : nativeFades) {
		CAPTURE(native.value);
		weather.data.precipitationBeginFadeIn = native.value;
		weather.data.precipitationEndFadeOut = native.value;
		const float incoming = std::bit_cast<float>(runtime == Runtime::AE ? native.aeIncoming : native.vrIncoming);
		const float outgoing = std::bit_cast<float>(runtime == Runtime::AE ? native.aeOutgoing : native.vrOutgoing);
		for (int step : { -1, 0, 1 }) {
			CAPTURE(step);
			const float direction = step < 0 ? -std::numeric_limits<float>::infinity() : std::numeric_limits<float>::infinity();
			sky.currentWeather = &weather;
			sky.lastWeather = nullptr;
			sky.currentWeatherPct = step == 0 ? incoming : std::nextafter(incoming, direction);
			CheckPrecipitation(sky, step > 0, step > 0);
			sky.currentWeather = nullptr;
			sky.lastWeather = &weather;
			sky.currentWeatherPct = step == 0 ? outgoing : std::nextafter(outgoing, direction);
			CheckPrecipitation(sky, step < 0, step < 0);
		}
	}
}
