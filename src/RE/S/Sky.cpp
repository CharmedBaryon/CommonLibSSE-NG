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

	void Sky::FillColorBlend(COLOR_BLEND& a_colorBlend, TESWeather* a_currentWeather, float a_weatherPct, TESWeather::ColorTime& a_time1, TESWeather::ColorTime& a_time2)
	{
		using func_t = decltype(&Sky::FillColorBlend);
		static REL::Relocation<func_t> func{ RELOCATION_ID(25706, 26253) };
		func(this, a_colorBlend, a_currentWeather, a_weatherPct, a_time1, a_time2);
	}

	void Sky::FillColorBlendColors(COLOR_BLEND& a_colorBlend, TESWeather* a_currentWeather, TESWeather* a_lastWeather, TESWeather::ColorType a_colorType, TESWeather::ColorTime& a_time1, TESWeather::ColorTime& a_time2)
	{
		if (a_currentWeather) {
			a_colorBlend.RGBVal[0] = a_currentWeather->colorData[a_colorType][a_time1];
			a_colorBlend.RGBVal[1] = a_currentWeather->colorData[a_colorType][a_time2];
			if (a_lastWeather) {
				a_colorBlend.RGBVal[2] = a_lastWeather->colorData[a_colorType][a_time1];
				a_colorBlend.RGBVal[3] = a_lastWeather->colorData[a_colorType][a_time2];
			} else {
				a_colorBlend.RGBVal[2] = Color();
			}
		}
	}

	void Sky::ForceWeather(TESWeather* a_weather, bool a_override)
	{
		using func_t = decltype(&Sky::ForceWeather);
		static REL::Relocation<func_t> func{ RELOCATION_ID(25696, 26243) };
		func(this, a_weather, a_override);
	}

	bool Sky::IsDaytime()
	{
		using func_t = decltype(&Sky::IsDaytime);
		static REL::Relocation<func_t> func{ RELOCATION_ID(25678, 26221) };
		return func(this);
	}

	bool Sky::IsRaining() const
	{
		const bool currentIsRainy = currentWeather && currentWeather->data.flags.any(TESWeather::WeatherDataFlag::kRainy);
		// precipitationBeginFadeIn is negative
		const float currentFadeInPct = currentIsRainy ?
		                                   (1.0f + static_cast<float>(currentWeather->data.precipitationBeginFadeIn) / 255.0f) :
		                                   0.0f;
		const bool  currentlyRaining = currentIsRainy && currentFadeInPct < currentWeatherPct;

		const bool  lastWasRainy = lastWeather && lastWeather->data.flags.any(TESWeather::WeatherDataFlag::kRainy);
		const float endFadeOutPtc = lastWasRainy ?
		                                static_cast<float>(lastWeather->data.precipitationEndFadeOut) / 255.0f :
		                                0.0f;
		const bool  isStillRaining = lastWasRainy && endFadeOutPtc > currentWeatherPct;

		return currentlyRaining || isStillRaining;
	}

	bool Sky::IsSnowing() const
	{
		const bool currentIsSnowy = currentWeather && currentWeather->data.flags.any(TESWeather::WeatherDataFlag::kSnow);
		// precipitationBeginFadeIn is negative
		const float currentFadeInPct = currentIsSnowy ?
		                                   (1.0f + static_cast<float>(currentWeather->data.precipitationBeginFadeIn) / 255.0f) :
		                                   0.0f;
		const bool  currentlyRaining = currentIsSnowy && currentFadeInPct < currentWeatherPct;

		const bool  lastWasSnowy = lastWeather && lastWeather->data.flags.any(TESWeather::WeatherDataFlag::kSnow);
		const float endFadeOutPtc = lastWasSnowy ?
		                                static_cast<float>(lastWeather->data.precipitationEndFadeOut) / 255.0f :
		                                0.0f;
		const bool  isStillRaining = lastWasSnowy && endFadeOutPtc > currentWeatherPct;

		return currentlyRaining || isStillRaining;
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

	void Sky::SetColor(NiColor& a_color, COLOR_BLEND* a_colorBlend, float a_addFlash) const
	{
		using func_t = decltype(&Sky::SetColor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(25691, 26238) };
		func(this, a_color, a_colorBlend, a_addFlash);
	}

	void Sky::SetWeather(TESWeather* a_weather, bool a_override, bool a_accelerate)
	{
		using func_t = decltype(&Sky::SetWeather);
		static REL::Relocation<func_t> func{ RELOCATION_ID(25694, 26241) };
		func(this, a_weather, a_override, a_accelerate);
	}
}
