#include "RE/S/Sky.h"

#include "RE/T/TESClimate.h"
#include "RE/T/TESWeather.h"

namespace RE
{
	Sky* Sky::GetSingleton()
	{
		using func_t = decltype(&Sky::GetSingleton);
		static REL::Relocation<func_t> func{ RELOCATION_ID(13789, 13878) };
		return func();
	}

	float Sky::GetSunriseBegin()
	{
		float& cache = *REL::Relocation<float*>{ RELOCATION_ID(515516, 401655) };

		if (flags.none(Flags::kUpdateSunriseBegin) || !currentClimate) {
			return cache;
		}

		cache = currentClimate->timing.sunrise.begin * 0.16666667f;
		flags.reset(Flags::kUpdateSunriseBegin);

		return cache;
	}

	float Sky::GetSunriseEnd()
	{
		float& cache = *REL::Relocation<float*>{ RELOCATION_ID(515517, 401656) };

		if (flags.none(Flags::kUpdateSunriseEnd) || !currentClimate) {
			return cache;
		}

		cache = currentClimate->timing.sunrise.end * 0.16666667f;
		flags.reset(Flags::kUpdateSunriseEnd);

		return cache;
	}

	float Sky::GetSunsetBegin()
	{
		float& cache = *REL::Relocation<float*>{ RELOCATION_ID(515518, 401657) };

		if (flags.none(Flags::kUpdateSunsetBegin) || !currentClimate) {
			return cache;
		}

		cache = currentClimate->timing.sunset.begin * 0.16666667f;
		flags.reset(Flags::kUpdateSunsetBegin);

		return cache;
	}

	float Sky::GetSunsetEnd()
	{
		float& cache = *REL::Relocation<float*>{ RELOCATION_ID(515519, 401658) };

		if (flags.none(Flags::kUpdateSunsetEnd) || !currentClimate) {
			return cache;
		}

		cache = currentClimate->timing.sunset.end * 0.16666667f;
		flags.reset(Flags::kUpdateSunsetEnd);

		return cache;
	}

	void Sky::ForceWeather(TESWeather* a_weather, bool a_override)
	{
		using func_t = decltype(&Sky::ForceWeather);
		static REL::Relocation<func_t> func{ RELOCATION_ID(25696, 26243) };
		func(this, a_weather, a_override);
	}

	bool Sky::IsRaining() const
	{
		return (currentWeather && currentWeather->data.flags.any(TESWeather::WeatherDataFlag::kRainy) && (currentWeather->data.precipitationBeginFadeIn * (1.0f / 255.0f)) < currentWeatherPct) ||
		       (lastWeather && lastWeather->data.flags.any(TESWeather::WeatherDataFlag::kRainy) && ((lastWeather->data.precipitationEndFadeOut * (1.0f / 255.0f)) + 0.001f) > currentWeatherPct);
	}

	bool Sky::IsSnowing() const
	{
		return (currentWeather && currentWeather->data.flags.any(TESWeather::WeatherDataFlag::kSnow) && (currentWeather->data.precipitationBeginFadeIn * (1.0f / 255.0f)) < currentWeatherPct) ||
		       (lastWeather && lastWeather->data.flags.any(TESWeather::WeatherDataFlag::kSnow) && ((lastWeather->data.precipitationEndFadeOut * (1.0f / 255.0f)) + 0.001f) > currentWeatherPct);
	}

	void Sky::ReleaseWeatherOverride()
	{
		if (overrideWeather) {
			flags.set(Flags::kReleaseWeatherOverride);
			overrideWeather = nullptr;
		}
	}

	void Sky::ResetWeather()
	{
		using func_t = decltype(&Sky::ResetWeather);
		static REL::Relocation<func_t> func{ RELOCATION_ID(25695, 26242) };
		func(this);
	}

	void Sky::SetWeather(TESWeather* a_weather, bool a_override, bool a_accelerate)
	{
		using func_t = decltype(&Sky::SetWeather);
		static REL::Relocation<func_t> func{ RELOCATION_ID(25694, 26241) };
		func(this, a_weather, a_override, a_accelerate);
	}
}
