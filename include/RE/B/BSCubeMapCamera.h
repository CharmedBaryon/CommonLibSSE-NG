#pragma once

#include <cstdint>

#include "RE/B/BSTArray.h"
#include "RE/N/NiCamera.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiRTTI.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSShaderAccumulator;

	class BSCubeMapCamera : public NiCamera
	{
	public:
		enum class FaceEnableFlags : std::uint32_t
		{
			kEnablePosX = 1 << 0,
			kEnableNegX = 1 << 1,
			kEnablePosY = 1 << 2,
			kEnableNegY = 1 << 3,
			kEnablePosZ = 1 << 4,
			kEnableNegZ = 1 << 5,
			kEnableAll = 0x3F
		};

		enum class Face : std::uint32_t
		{
			kPosX = 0,
			kNegX = 1,
			kPosY = 2,
			kNegY = 3,
			kPosZ = 4,
			kNegZ = 5
		};

		inline static constexpr auto RTTI = RTTI_BSCubeMapCamera;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSCubeMapCamera;
		inline static constexpr auto VTABLE = VTABLE_BSCubeMapCamera;

		static BSCubeMapCamera* Create();

		~BSCubeMapCamera() override;  // 00

		// override (NiCamera)
		const NiRTTI* GetRTTI() const override;  // 02

		// add
		void         SetFace(Face a_face);
		virtual void RenderCubemap(FaceEnableFlags a_faceMask, bool a_arg2, bool a_clearScenes, bool a_arg4);  // 35

		// members
		BSTArray<NiPointer<NiAVObject>> scenes;             // 188
		NiPointer<BSShaderAccumulator>  accumulator;        // 1A0
		NiPointer<BSShaderAccumulator>  secondAccumulator;  // 1A8
		NiPointer<NiCamera>             unk1B0;             // 1B0
		NiColorA                        silhouetteColor;    // 1B8

	protected:
		BSCubeMapCamera* Ctor();

	private:
		void Dtor();
	};
	STATIC_ASSERT_SIZE(BSCubeMapCamera, 0x1C8, 0x1C8, 0x248, 0x150, 0x1C8);
}
