#pragma once

#include "RE/B/BSCubeMapCamera.h"
#include "RE/B/BSShaderAccumulator.h"
#include "RE/N/NiPlane.h"
#include "RE/N/NiRefObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSCullingProcess;
	class BSWaterShaderMaterial;

	class TESWaterReflections : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESWaterReflections;
		inline static constexpr auto VTABLE = VTABLE_TESWaterReflections;

		struct CubeMapSide
		{
			std::uint32_t idx;         // 00
			float         renderTime;  // 04
		};
		static_assert(sizeof(CubeMapSide) == 0x8);

		// https://github.com/libxse/commonlibf4/blob/main/include/RE/T/TESWaterReflections.h
		enum class Flags : std::uint16_t
		{
			kDirty = 1 << 0,
			kStaticCubemap = 1 << 1,
			kDynamicCubemap = 1 << 2,
			kInterior = 1 << 3,
			kSilhouette = 1 << 4,
			kLODScene = 1 << 5,
			kFullScene = 1 << 6,
			kLand = 1 << 7,
			kSky = 1 << 8,
			kExplosions = 1 << 9,
			kSelective = 1 << 10,
			kDontUpdate = 1 << 11,
			kWorldOrigin = 1 << 12
		};

		virtual ~TESWaterReflections() override { Dtor(); };  // 00

		// Returns whether this instance was actively processed this frame (== activeThisFrame),
		// gated by a per-frame budget of cubeMapSides.size() (6).
		bool UpdateActor();

		// members
		REX::EnumSet<Flags, std::uint16_t> flags;                  // 10
		std::uint16_t                      pad12;                  // 12
		NiPlane                            reflectPlane;           // 14
		std::uint32_t                      pad24;                  // 24
		NiPointer<BSCubeMapCamera>         cubeMapCamera;          // 28
		NiPointer<BSShaderAccumulator>     sorter;                 // 30
		BSCullingProcess*                  cullingProcess;         // 38
		BSWaterShaderMaterial*             waterMaterial;          // 40
		float                              reflectionUpdateTimer;  // 48
		std::uint32_t                      currentCubeMapFace;     // 4C
		CubeMapSide                        cubeMapSides[6];        // 50
		bool                               activeThisFrame;        // 80
		std::uint8_t                       pad81;                  // 81
		std::uint16_t                      pad82;                  // 82
		std::uint32_t                      pad84;                  // 84
	private:
		void Dtor();
	};
	static_assert(sizeof(TESWaterReflections) == 0x88);
}
