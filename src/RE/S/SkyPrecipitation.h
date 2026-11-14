#pragma once

#include "RE/T/TESWeather.h"
#include "REL/Module.h"

#include <bit>
#include <cstdint>

namespace RE::detail
{
	inline float GetPrecipitationFade(std::uint8_t a_value, bool a_outgoing)
	{
		float fade;
		if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
			// AE folds the byte scale differently for incoming and outgoing fades.
			constexpr float incomingScale = std::bit_cast<float>(0x3B805F9CU);
			constexpr float outgoingScale = std::bit_cast<float>(0x3B805F9BU);
			fade = static_cast<float>(a_value) * (a_outgoing ? outgoingScale : incomingScale);
		} else {
			constexpr float byteToUnit = 1.0F / 255.0F;
			constexpr float fadeRange = 0.999F;
			fade = static_cast<float>(a_value) * byteToUnit * fadeRange;
		}
		constexpr float fadeOutOffset = 0.001F;
		return a_outgoing ? fade + fadeOutOffset : fade;
	}

	template <class SkyType>
	bool HasPrecipitation(const SkyType& a_sky, TESWeather::WeatherDataFlag a_flag)
	{
		const auto* current = a_sky.currentWeather;
		if (current && current->data.flags.any(a_flag)) {
			const float fadeIn = GetPrecipitationFade(current->data.precipitationBeginFadeIn, false);
			if (fadeIn < a_sky.currentWeatherPct) {
				return true;
			}
		}

		const auto* last = a_sky.lastWeather;
		return last && last->data.flags.any(a_flag) &&
		       GetPrecipitationFade(last->data.precipitationEndFadeOut, true) > a_sky.currentWeatherPct;
	}
}
