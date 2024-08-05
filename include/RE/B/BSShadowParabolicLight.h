#pragma once

#include "RE/B/BSShadowLight.h"

namespace RE
{
	class BSShadowParabolicLight : public BSShadowLight
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSShadowParabolicLight;

		~BSShadowParabolicLight() override;  // 00

		// override (BSShadowLight)
		bool IsParabolicLight() override;                                                                                      // 07
		bool IsOmnidirectionalLight() override;                                                                                // 08
		void Cull(uint32_t& globalShadowLightCount, uint32_t shadowMaskChannel, NiPointer<NiAVObject> cullingScene) override;  // 09
		void RenderShadowmaps() override;                                                                                      // 0A
		void Reset() override;                                                                                                 // 0C
		void Unk_0D() override;                                                                                                // 0D
		bool Unk_0E() override;                                                                                                // 0E
		bool SetFrameCamera(const NiCamera& frameCamera) override;                                                             // 10

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSShadowParabolicLight) == 0x560);
}
