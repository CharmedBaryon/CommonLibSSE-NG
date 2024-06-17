#pragma once

#include "RE/B/BSShadowLight.h"

namespace RE
{
	class BSShadowFrustumLight : public BSShadowLight
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSShadowFrustumLight;

		~BSShadowFrustumLight() override;  // 00

		// override (BSShadowLight)
		bool AreFocusShadowsSupported() override;                                                                              // 04
		bool IsSpotLight() override;                                                                                           // 05
		void Cull(uint32_t& globalShadowLightCount, uint32_t shadowMaskChannel, NiPointer<NiAVObject> cullingScene) override;  // 09
		void RenderShadowmaps() override;                                                                                      // 0A
		bool SetFrameCamera(const NiCamera& frameCamera) override;                                                             // 10

		// members
		float semiWidth;     // 560
		float semiHeight;    // 564
		float falloff;       // 568
		float nearDistance;  // 56C
		float farDistance;   // 570
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSShadowFrustumLight) == 0x578);
}
