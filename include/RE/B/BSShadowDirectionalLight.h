#pragma once

#include "RE/B/BSShadowLight.h"

namespace RE
{
	class BSShadowDirectionalLight : public BSShadowLight
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSShadowDirectionalLight;

		~BSShadowDirectionalLight() override;  // 00

		// override (BSShadowLight)
		bool AreFocusShadowsSupported() override;                                                                              // 04
		bool IsDirectionalLight() override;                                                                                    // 06
		void Cull(uint32_t& globalShadowLightCount, uint32_t shadowMaskChannel, NiPointer<NiAVObject> cullingScene) override;  // 09
		void RenderShadowmaps() override;                                                                                      // 0A
		void Reset() override;                                                                                                 // 0C
		void Unk_0D() override;                                                                                                // 0D
		bool Unk_0E() override;                                                                                                // 0E
		void Unk_0F() override;                                                                                                // 0F
		bool SetFrameCamera(const NiCamera& frameCamera) override;                                                             // 10

		// members
		NiPoint3                              lightDirection;             // 560
		NiPoint3                              previousLightDirection;     // 56C
		NiPointer<NiCamera>                   cullingCamera;              // 578
		BSTArray<NiPointer<BSCullingProcess>> cullingProcesses;           // 580
		float                                 startSplitDistances[3];     // 598
		float                                 endSplitDistances[3];       // 5A4
		float                                 lightDirectionUpdateTimer;  // 5B0
		bool                                  cameraShifted;              // 5B4
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSShadowDirectionalLight) == 0x5B8);
}
