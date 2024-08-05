#pragma once

#include "RE/N/NiBound.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiPoint2.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTransform.h"

namespace RE
{
	class ShadowSceneNode;
	class NiTexture;

	class BSShaderManager
	{
	public:
		enum BSShaderTimerMode
		{
			kDefault = 0,
			kDelta,
			kSystem,
			kRealDelta,

			kTotal = 5,
		};

		class State
		{
		public:
			static BSShaderManager::State& GetSingleton()
			{
				REL::Relocation<BSShaderManager::State*> singleton{ RELOCATION_ID(513211, 390951) };
				return *singleton;
			}

			// members
			ShadowSceneNode* shadowSceneNode[4];                      // 000
			float            timerValues[BSShaderTimerMode::kTotal];  // 020
			NiColorA         loadedRange;                             // 034
			bool             interior;                                // 044
			bool             liteBrite;                               // 045
			bool             characterLightEnabled;                   // 046
			std::uint8_t     pad47;                                   // 047
			void*            unk48;                                   // 048
			void*            unk50;                                   // 050
			void*            unk58;                                   // 058
			void*            unk60;                                   // 060
			void*            unk68;                                   // 068
			void*            unk70;                                   // 070
			void*            unk78;                                   // 078
			void*            unk80;                                   // 080
			void*            unk88;                                   // 088
			std::uint64_t    unk90;                                   // 090
			float            landLOFadeSeconds;                       // 098
			float            invFrameBufferRange;                     // 09C
			float            leafAnimDampenDistStartSPU;              // 0A0
			float            leafAnimDampenDistEndSPU;                // 0A4
			NiPoint2         oldGridArrayCenter;                      // 0A8
			NiPoint2         gridArrayCenter;                         // 0B0
			float            gridArrayLerpStart;                      // 0B8
			std::uint32_t    currentShaderTechnique;                  // 0BC
			std::uint8_t     sceneGraph;                              // 0C0
			std::uint32_t    debugMode;                               // 0C4
			NiTransform      directionalAmbientTransform;             // 0C8
			NiColorA         ambientSpecular;                         // 0FC
			float            characterLightParams[4];                 // 10C - { Primary, Secondary, Luminance, Max Luminance }
			bool             ambientSpecularEnabled;                  // 11C
			std::uint32_t    textureTransformCurrentBuffer;           // 120
			std::uint32_t    textureTransformFlipMode;                // 124
			std::uint32_t    cameraInWaterState;                      // 128
			NiBound          cachedPlayerBound;                       // 12C
			std::uint32_t    pad13C;                                  // 13C
			std::uint32_t    pad140;                                  // 140
			float            waterIntersect;                          // 144
		};
		static_assert(sizeof(State) == 0x148);

		static void GetTexture(const char* a_path, bool a_demand, NiPointer<NiTexture>& a_textureOut, bool a_isHeightMap)
		{
			using func_t = decltype(&BSShaderManager::GetTexture);
			static REL::Relocation<func_t> func{ RELOCATION_ID(98986, 105640) };
			return func(a_path, a_demand, a_textureOut, a_isHeightMap);
		}

	private:
		KEEP_FOR_RE()
	};
}
