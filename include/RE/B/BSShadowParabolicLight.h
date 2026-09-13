#pragma once

#include "RE/B/BSShadowLight.h"

namespace RE
{
	class BSShadowParabolicLight : public BSShadowLight
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSShadowParabolicLight;
		inline static constexpr auto VTABLE = VTABLE_BSShadowParabolicLight;

		~BSShadowParabolicLight() override;  // 00

		// override (BSShadowLight)
		bool          GetIsParabolicLight() override;                                                                                                                                // 07
		bool          GetIsOmniLight() override;                                                                                                                                     // 08
		void          Accumulate(std::uint32_t& a_globalShadowLightCount, std::uint32_t a_shadowMaskChannel, NiAVObject* a_cullingScene, std::uint8_t a_vrUpdateFlag = 0) override;  // 09
		void          Render(std::uint32_t& a_index) override;                                                                                                                       // 0A
		void          SetShadowMapCount(std::uint32_t a_count) override;                                                                                                             // 0B
		void          ReturnShadowmaps() override;                                                                                                                                   // 0C
		std::uint32_t GetPassExtraParam(std::uint32_t a_accumFlag) override;                                                                                                         // 0D
		bool          GetNeedsClipPlanes() override;                                                                                                                                 // 0E
		bool          UpdateCamera(const NiCamera* a_viewCamera) override;                                                                                                           // 10
	};
	STATIC_ASSERT_SIZE(BSShadowParabolicLight, 0x560, 0x560, 0x5C0, 0x148);
}
