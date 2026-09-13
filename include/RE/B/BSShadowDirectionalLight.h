#pragma once

#include "RE/B/BSShadowLight.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSShadowDirectionalLight : public BSShadowLight
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSShadowDirectionalLight;
		inline static constexpr auto VTABLE = VTABLE_BSShadowDirectionalLight;

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                \
	NiPoint3                              sunVector;                      /* 560, VR 5C0 */ \
	NiPoint3                              lastSunVector;                  /* 56C, VR 5CC */ \
	NiPointer<NiCamera>                   fullFrustumCamera;              /* 578, VR 5D8 */ \
	BSTArray<NiPointer<BSCullingProcess>> fullFrustumCullingProcessArray; /* 580, VR 5E0 */ \
	float                                 startSplitDistances[3];         /* 598, VR 5F8 */ \
	float                                 endSplitDistances[3];           /* 5A4, VR 604 */ \
	float                                 sunUpdate;                      /* 5B0, VR 610 */ \
	std::uint32_t                         sunUpdateMode;                  /* 5B4, VR 614 */
            RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x58);

		~BSShadowDirectionalLight() override;  // 00

		// override (BSShadowLight)
		bool          GetIsFrustumOrDirectionalLight() override;                                                                                                                     // 04
		bool          GetIsDirectionalLight() override;                                                                                                                              // 06
		void          Accumulate(std::uint32_t& a_globalShadowLightCount, std::uint32_t a_shadowMaskChannel, NiAVObject* a_cullingScene, std::uint8_t a_vrUpdateFlag = 0) override;  // 09
		void          Render(std::uint32_t& a_index) override;                                                                                                                       // 0A
		void          ReturnShadowmaps() override;                                                                                                                                   // 0C
		std::uint32_t GetPassExtraParam(std::uint32_t a_accumFlag) override;                                                                                                         // 0D
		bool          GetNeedsClipPlanes() override;                                                                                                                                 // 0E
		void          TransformClipSpacePlanes(REX::W32::D3DXMatrix* a_matrix1, REX::W32::D3DXMatrix* a_matrix2) override;                                                           // 0F
		bool          UpdateCamera(const NiCamera* a_viewCamera) override;                                                                                                           // 10

		RUNTIME_DATA_ACCESSOR_EX(RUNTIME_DATA, GetShadowDirectionalLightRuntimeData, 0x560, 0x5C0);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 560, VR 5C0
#endif
	};
	STATIC_ASSERT_SIZE(BSShadowDirectionalLight, 0x5B8, 0x5B8, 0x618, 0x148);
}
#undef RUNTIME_DATA_CONTENT
