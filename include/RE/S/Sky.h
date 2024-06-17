#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTList.h"
#include "RE/B/BSTextureSet.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/S/SkyEffectController.h"

namespace RE
{
	class Atmosphere;
	class BGSLightingTemplate;
	class BSMultiBoundNode;
	class Clouds;
	class ImageSpaceModifierInstanceForm;
	class Moon;
	class NiNode;
	class NiTexture;
	class Precipitation;
	class ReferenceEffect;
	class SkySound;
	class Stars;
	class Sun;
	class TESClimate;
	class TESRegion;
	class TESWeather;

	class Sky
	{
	public:
		inline static constexpr auto RTTI = RTTI_Sky;

		enum class Mode
		{
			kNone = 0,
			kInterior,
			kSkyDomeOnly,
			kFull,

			kTotal
		};

		enum class Flags
		{
			kNone = 0,
			kFastTravel = 1 << 4,
			kHideSky = 1 << 7,
			kUpdateSunriseBegin = 1 << 9,
			kUpdateSunriseEnd = 1 << 10,
			kUpdateSunsetBegin = 1 << 11,
			kUpdateSunsetEnd = 1 << 12,
			kUpdateColorsSunriseBegin = 1 << 13,
			kUpdateColorsSunsetEnd = 1 << 14,
			kUpdateWind = 1 << 20,
			kReleaseWeatherOverride = 1 << 21
		};

		struct SkyStaticRefData
		{
		public:
		};

		virtual ~Sky();  // 00

		static Sky* GetSingleton();

		[[nodiscard]] float GetSunriseBegin();
		[[nodiscard]] float GetSunriseEnd();
		[[nodiscard]] float GetSunsetBegin();
		[[nodiscard]] float GetSunsetEnd();
		void                ForceWeather(TESWeather* a_weather, bool a_override);
		[[nodiscard]] bool  IsRaining() const;
		[[nodiscard]] bool  IsSnowing() const;
		void                ReleaseWeatherOverride();
		void                ResetWeather();
		void                SetWeather(TESWeather* a_weather, bool a_override, bool a_accelerate);

		// members
		NiPointer<BSMultiBoundNode>            root;                            // 008
		NiPointer<NiNode>                      moonsRoot;                       // 010
		NiPointer<NiNode>                      auroraRoot;                      // 018
		void*                                  auroraDBHandle;                  // 020
		BGSLightingTemplate*                   extLightingOverride;             // 028
		ObjectRefHandle                        currentRoom;                     // 030
		ObjectRefHandle                        previousRoom;                    // 034
		float                                  lightingTransition;              // 038
		float                                  lightingTransitionTimer;         // 03C
		TESClimate*                            currentClimate;                  // 040
		TESWeather*                            currentWeather;                  // 048
		TESWeather*                            lastWeather;                     // 050
		TESWeather*                            defaultWeather;                  // 058
		TESWeather*                            overrideWeather;                 // 060
		TESRegion*                             region;                          // 068
		Atmosphere*                            atmosphere;                      // 070
		Stars*                                 stars;                           // 078
		Sun*                                   sun;                             // 080
		Clouds*                                clouds;                          // 088
		Moon*                                  masser;                          // 090
		Moon*                                  secunda;                         // 098
		Precipitation*                         precip;                          // 0A0
		NiColor                                skyColor[17];                    // 0A8
		std::uint32_t                          unk174;                          // 174
		std::uint64_t                          unk178;                          // 178
		NiColor                                unk180;                          // 180
		float                                  windSpeed;                       // 18C
		float                                  windAngle;                       // 190
		float                                  fogNear;                         // 194
		float                                  fogFar;                          // 198
		std::uint32_t                          unk19C;                          // 19C
		std::uint32_t                          unk1A0;                          // 1A0
		std::uint32_t                          unk1A4;                          // 1A4
		float                                  fogPower;                        // 1A8
		float                                  fogClamp;                        // 1AC
		float                                  currentGameHour;                 // 1B0
		float                                  lastWeatherUpdate;               // 1B4
		float                                  currentWeatherPct;               // 1B8
		stl::enumeration<Mode, std::uint32_t>  mode;                            // 1BC
		BSSimpleList<SkySound*>*               skySoundList;                    // 1C0
		float                                  flash;                           // 1C8
		std::uint32_t                          pad1CC;                          // 1CC
		std::time_t                            flashTime;                       // 1D0
		std::uint32_t                          lastMoonPhaseUpdate;             // 1D8
		stl::enumeration<Flags, std::uint32_t> flags;                           // 1DC
		ImageSpaceModifierInstanceForm*        currentWeatherImageSpaceMod;     // 1E0
		ImageSpaceModifierInstanceForm*        currentWeatherImageSpaceMod2;    // 1E8
		ImageSpaceModifierInstanceForm*        lastWeatherImageSpaceMod;        // 1F0
		ImageSpaceModifierInstanceForm*        lastWeatherImageSpaceMod2;       // 1F8
		NiColor                                directionalAmbientColors[3][2];  // 200
		NiColor                                ambientSpecularTint;             // 248
		float                                  ambientSpecularFresnel;          // 254
		float                                  auroraInStart;                   // 258
		float                                  auroraIn;                        // 25C
		float                                  auroraOutStart;                  // 260
		float                                  auroraOut;                       // 264
		NiPointer<ReferenceEffect>             currentReferenceEffect;          // 268
		NiPointer<ReferenceEffect>             lastReferenceEffect;             // 270
		SkyEffectController                    effectController;                // 278
		BSTArray<NiPointer<NiTexture>>         storedCloudTextures;             // 280
		BSTArray<NiPointer<NiTexture>>         storedWorldMapCloudTextures;     // 298
		BSTArray<SkyStaticRefData>             skyStaticRefData;                // 2B0
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(Sky) == 0x2C8);
}
