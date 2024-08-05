#pragma once

#include "RE/N/NiPlane.h"
#include "RE/N/NiRefObject.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSWaterShaderMaterial;
	class BSCubeMapCamera;

	class TESWaterReflections : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESWaterReflections;
		inline static constexpr auto VTABLE = VTABLE_TESWaterReflections;

		struct CubeMapSide
		{
			std::uint32_t idx;    // 00
			float         unk04;  // 04
		};
		static_assert(sizeof(CubeMapSide) == 0x8);

		virtual ~TESWaterReflections();  // 00

		// members
		std::uint32_t              flags;            // 10
		NiPlane                    reflectPlane;     // 14
		std::uint32_t              unk24;            // 24
		NiPointer<BSCubeMapCamera> cubeMapCamera;    // 28
		std::uint64_t              unk30;            // 30
		std::uint64_t              unk38;            // 38
		BSWaterShaderMaterial*     waterMaterial;    // 40
		float                      unk48;            // 48
		std::uint32_t              unk4C;            // 4C
		CubeMapSide                cubeMapSides[6];  // 50
		std::uint8_t               unk80;            // 80
		std::uint8_t               pad81;            // 81
		std::uint16_t              pad82;            // 82
		std::uint32_t              pad84;            // 84
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESWaterReflections) == 0x88);
}
