#pragma once

#include <array>
#include <cstdint>

#include "RE/B/BSShaderAccumulator.h"
#include "RE/N/NiBound.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiPoint2.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTransform.h"

namespace RE
{
	class ShadowSceneNode;
	class BSShadowDirectionalLight;
	class NiTexture;
	class NiSourceTexture;

	class BSShaderManager
	{
	public:
		static void UpdateShadowDistanceAndInteriorFlag(bool a_interior)
		{
			using func_t = void (*)(bool);
			static REL::Relocation<func_t> func{ RELOCATION_ID(98978, 105631) };
			func(a_interior);
		}

		static void UpdateFogState()
		{
			using func_t = void (*)();
			static REL::Relocation<func_t> func{ RELOCATION_ID(100000, 106707) };
			func();
		}

		enum BSShaderTimerMode
		{
			kDefault = 0,
			kDelta,
			kSystem,
			kRealDelta,

			kTotal = 5,
		};

		using etRenderMode = BSShaderAccumulator::RENDER_MODE;

		[[nodiscard]] static NiPoint3& GetWaterDisplacementMeshPosition() noexcept
		{
			static REL::Relocation<NiPoint3*> position{ RELOCATION_ID(516235, 402400) };
			return *position;
		}

		[[nodiscard]] static NiPoint2& GetWaterDisplacementMeshFlowCellOffset() noexcept
		{
			static REL::Relocation<NiPoint2*> offset{ RELOCATION_ID(528164, 415109) };
			return *offset;
		}

		[[nodiscard]] static std::array<float, 4>& GetWaterDisplacementCellTexCoordOffset() noexcept
		{
			static REL::Relocation<std::array<float, 4>*> offset{ RELOCATION_ID(528184, 415129) };
			return *offset;
		}

		[[nodiscard]] static NiPointer<NiSourceTexture>& GetWaterFlowMapSourceTexture() noexcept
		{
			static REL::Relocation<NiPointer<NiSourceTexture>*> texture{ RELOCATION_ID(527694, 414616) };
			return *texture;
		}

		[[nodiscard]] static bool IsSunShadowCasterCalculationDisabled() noexcept
		{
			static REL::Relocation<bool*> disabled{ RELOCATION_ID(528095, 415040) };
			return *disabled;
		}

		[[nodiscard]] static std::int32_t GetFocusShadowActorCount() noexcept
		{
			static REL::Relocation<std::int32_t*> count{ RELOCATION_ID(527703, 414625) };
			return *count;
		}

		[[nodiscard]] static std::uint32_t& GetLastFrameEnabledShadowCasterLightCount() noexcept
		{
			static REL::Relocation<std::uint32_t*> count{ RELOCATION_ID(528090, 415035) };
			return *count;
		}

		[[nodiscard]] static std::uint32_t& GetGlobalShadowLightCount() noexcept
		{
			static REL::Relocation<std::uint32_t*> count{ RELOCATION_ID(528091, 415036) };
			return *count;
		}

		[[nodiscard]] static std::uint32_t& GetShadowCasterMaskIndex() noexcept
		{
			static REL::Relocation<std::uint32_t*> index{ RELOCATION_ID(528091, 415036), sizeof(std::uint32_t) };
			return *index;
		}

		[[nodiscard]] static std::uint32_t& GetActiveShadowCasterLightMask() noexcept
		{
			static REL::Relocation<std::uint32_t*> mask{ RELOCATION_ID(528093, 415038) };
			return *mask;
		}

		[[nodiscard]] static bool& GetFocusShadowSelected() noexcept
		{
			static REL::Relocation<bool*> selected{ RELOCATION_ID(528096, 415041) };
			return *selected;
		}

		[[nodiscard]] static BSShadowDirectionalLight*& GetSelectedShadowDirectionalLight() noexcept
		{
			static REL::Relocation<BSShadowDirectionalLight**> selected{ RELOCATION_ID(528315, 415267) };
			return *selected;
		}

		[[nodiscard]] static bool IsSunShadowUpdateDue() noexcept
		{
			if (!REL::Module::IsVR()) {
				return false;
			}
			static REL::Relocation<bool*> updateDue{ REL::Offset(0x1ed62f8) };
			return *updateDue;
		}

		[[nodiscard]] static float& GetShadowDistanceCurrent() noexcept
		{
			static REL::Relocation<float*> distance{ RELOCATION_ID(528314, 415263) };
			return *distance;
		}

		[[nodiscard]] static float& GetShadowDistanceSquaredCurrent() noexcept
		{
			static REL::Relocation<float*> distance{ RELOCATION_ID(528316, 415264) };
			return *distance;
		}

		class State
		{
		public:
			static BSShaderManager::State& GetSingleton()
			{
				static REL::Relocation<BSShaderManager::State*> singleton{ RELOCATION_ID(513211, 390951) };
				return *singleton;
			}

			// members
			ShadowSceneNode*     shadowSceneNode[4];                      // 000
			float                timerValues[BSShaderTimerMode::kTotal];  // 020
			NiColorA             loadedRange;                             // 034
			bool                 interior;                                // 044
			bool                 liteBrite;                               // 045
			bool                 characterLightEnabled;                   // 046
			std::uint8_t         pad47;                                   // 047
			void*                unk48;                                   // 048
			void*                unk50;                                   // 050
			void*                unk58;                                   // 058
			void*                unk60;                                   // 060
			void*                unk68;                                   // 068
			NiPointer<NiTexture> worldMapOverlayNormal;                   // 070
			NiPointer<NiTexture> worldMapOverlayNormalSnow;               // 078
			void*                unk80;                                   // 080
			void*                unk88;                                   // 088
			std::uint64_t        unk90;                                   // 090
			float                landLOFadeSeconds;                       // 098
			float                invFrameBufferRange;                     // 09C
			float                leafAnimDampenDistStartSPU;              // 0A0
			float                leafAnimDampenDistEndSPU;                // 0A4
			NiPoint2             oldGridArrayCenter;                      // 0A8
			NiPoint2             gridArrayCenter;                         // 0B0
			float                gridArrayLerpStart;                      // 0B8
			std::uint32_t        currentShaderTechnique;                  // 0BC
			std::uint8_t         sceneGraph;                              // 0C0
			std::uint32_t        debugMode;                               // 0C4
			NiTransform          directionalAmbientTransform;             // 0C8
			NiColorA             ambientSpecular;                         // 0FC
			float                characterLightParams[4];                 // 10C - { Primary, Secondary, Luminance, Max Luminance }
			bool                 ambientSpecularEnabled;                  // 11C
			std::uint32_t        textureTransformCurrentBuffer;           // 120
			std::uint32_t        textureTransformFlipMode;                // 124
			std::uint32_t        cameraInWaterState;                      // 128
			NiBound              cachedPlayerBound;                       // 12C
			std::uint32_t        pad13C;                                  // 13C
			std::uint32_t        pad140;                                  // 140
			float                waterIntersect;                          // 144
		};
		static_assert(sizeof(State) == 0x148);

		static void GetTexture(const char* a_path, bool a_demand, NiPointer<NiTexture>& a_textureOut, bool a_isHeightMap)
		{
			using func_t = decltype(&BSShaderManager::GetTexture);
			static REL::Relocation<func_t> func{ RELOCATION_ID(98986, 105640) };
			return func(a_path, a_demand, a_textureOut, a_isHeightMap);
		}

		static void SetRenderMode(etRenderMode a_renderMode)
		{
			using func_t = decltype(&BSShaderManager::SetRenderMode);
			static REL::Relocation<func_t> func{ RELOCATION_ID(98987, 105641) };
			return func(a_renderMode);
		}
	};
}
