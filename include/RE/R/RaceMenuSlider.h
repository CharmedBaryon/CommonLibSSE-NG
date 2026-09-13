#pragma once

#include "RE/B/BSTArray.h"

namespace RE
{
	class TESRace;

	// RaceSexMenu::RUNTIME_DATA::sliderData element. No RTTI (POD); verified
	// against SkyrimSE.exe: sizeof 0x138, index at +0x124, +0x130 is float
	// (not uint32) with a ~FLT_MAX sentinel for "unset".
	struct RaceMenuSlider
	{
		enum
		{
			kTypeHeadPart = 0,
			kTypeUnk1,
			kTypeDoubleMorph,
			kTypePreset,
			kTypeTintingMask,
			kTypeHairColorPreset,
			kTypeUnk6,
			kTypeUnused7,
			kTypeUnk8,
			kTypeUnk9,
			kTypeUnk10
		};

		float         min;            // 000
		float         max;            // 004
		float         value;          // 008
		float         interval;       // 00C
		std::uint32_t filterFlag;     // 010
		std::uint32_t type;           // 014
		const char*   name;           // 018
		char          callback[260];  // 020
		std::uint32_t index;          // 124 - index into the associated head-part list
		std::uint32_t id;             // 128
		std::uint32_t unk12C;         // 12C
		float         currentValue;   // 130 - selected value; ~FLT_MAX sentinel when unset
		std::uint8_t  unk134;         // 134
		std::uint8_t  pad135[3];      // 135
	};
	static_assert(sizeof(RaceMenuSlider) == 0x138);

	using RaceMenuSliderArray = BSTArray<RaceMenuSlider>;

	// One race+sex slider set. Stride 0x28 verified against SkyrimSE.exe.
	struct RaceComponent
	{
		TESRace*            race;     // 00
		RaceMenuSliderArray sliders;  // 08
		std::uint32_t       unk20;    // 20
		std::uint32_t       pad24;    // 24
	};
	static_assert(sizeof(RaceComponent) == 0x28);
}
