#pragma once

#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"

#include "REX/W32/D3D.h"

namespace RE
{
	class BSCullingProcess;
	class BSGeometry;
	class BSParticleShaderRainEmitter;
	class BSShaderAccumulator;
	class NiCamera;

	class Precipitation
	{
	public:
		inline static constexpr auto RTTI = RTTI_Precipitation;
		inline static constexpr auto VTABLE = VTABLE_Precipitation;

		class OcclusionMapData
		{
		public:
			// members
			alignas(0x10) REX::W32::XMFLOAT4X4 projection;  // 00
			NiPointer<NiCamera>            camera;          // 40
			NiPointer<BSShaderAccumulator> accumulator;     // 48
			BSCullingProcess*              cullingProcess;  // 50
			std::uint64_t                  pad58;           // 58
		};
		static_assert(sizeof(OcclusionMapData) == 0x60);

		virtual ~Precipitation();  // 00

		static NiPoint3 GetDirection()
		{
			REL::Relocation<NiPoint3*> precipDirection{ RELOCATION_ID(515509, 401648) };
			return *precipDirection;
		}

		void SetupMask()
		{
			using func_t = decltype(&Precipitation::SetupMask);
			static REL::Relocation<func_t> func{ RELOCATION_ID(25641, 26183) };
			func(this);
		}

		void RenderMask(BSParticleShaderRainEmitter* a_emitter)
		{
			using func_t = decltype(&Precipitation::RenderMask);
			static REL::Relocation<func_t> func{ RELOCATION_ID(25642, 26184) };
			func(this, a_emitter);
		}

		// members
		OcclusionMapData      occlusionData;           // 10
		NiPointer<BSGeometry> currentPrecip;           // 70
		NiPointer<BSGeometry> lastPrecip;              // 78
		float                 lastCubeSize;            // 80
		float                 currentParticleDensity;  // 84
		float                 lastParticleDensity;     // 88
		std::uint32_t         pad8C;                   // 8C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(Precipitation) == 0x90);
}
