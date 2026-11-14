#pragma once

#include "RE/B/BSShadowLight.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSShadowFrustumLight : public BSShadowLight
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSShadowFrustumLight;
		inline static constexpr auto VTABLE = VTABLE_BSShadowFrustumLight;

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                   \
	float semiWidth;    /* 560, VR 5C0 xFOV */ \
	float semiHeight;   /* 564, VR 5C4 yFOV */ \
	float falloff;      /* 568, VR 5C8 */      \
	float nearDistance; /* 56C, VR 5CC */      \
	float farDistance;  /* 570, VR 5D0 */
			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x14);

		~BSShadowFrustumLight() override;  // 00

		// override (BSShadowLight)
		bool GetIsFrustumOrDirectionalLight() override;                                                                                                                     // 04
		bool GetIsFrustumLight() override;                                                                                                                                  // 05
		void Accumulate(std::uint32_t& a_globalShadowLightCount, std::uint32_t a_shadowMaskChannel, NiAVObject* a_cullingScene, std::uint8_t a_vrUpdateFlag = 0) override;  // 09
		void Render(std::uint32_t& a_index) override;                                                                                                                       // 0A
		bool UpdateCamera(const NiCamera* a_viewCamera) override;                                                                                                           // 10

		RUNTIME_DATA_ACCESSOR_EX(RUNTIME_DATA, GetShadowFrustumLightRuntimeData, 0x560, 0x5C0);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 560, VR 5C0
#endif
	};
	STATIC_ASSERT_SIZE(BSShadowFrustumLight, 0x578, 0x578, 0x5D8, 0x148);
}
#undef RUNTIME_DATA_CONTENT
