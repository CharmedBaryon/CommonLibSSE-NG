#pragma once

#include "RE/B/BSLight.h"
#include "RE/N/NiPlane.h"
#include "RE/N/NiRect.h"

namespace RE
{
	class BSShaderAccumulator;
	class NiCamera;

	class BSShadowLight : public BSLight
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSShadowLight;
		inline static constexpr auto VTABLE = VTABLE_BSShadowLight;

		struct ShadowmapDescriptor
		{
			REX::W32::XMFLOAT4X4           lightTransform;     // 00
			NiPointer<NiCamera>            camera;             // 40
			NiPointer<BSShaderAccumulator> shaderAccumulator;  // 48
			uint32_t                       unk50;              // 50
			RENDER_TARGET_DEPTHSTENCIL     renderTarget;       // 54
			uint32_t                       shadowmapIndex;     // 58
			NiPlane                        planes[6];          // 5C
			uint32_t                       unkBC;              // BC
			uint32_t                       unkC0;              // C0
			float                          unkC4;              // C4
			float                          unkC8;              // C8
			float                          unkCC;              // CC
			NiRect<int32_t>                port;               // D0
			BSCullingProcess*              cullingProcess;     // E0
			uint16_t                       flags;              // E8
		};
		static_assert(sizeof(ShadowmapDescriptor) == 0xF0);

		~BSShadowLight() override;  // 00

		// add
		virtual bool AreFocusShadowsSupported();                                                                                  // 04
		virtual bool IsSpotLight();                                                                                               // 05
		virtual bool IsDirectionalLight();                                                                                        // 06
		virtual bool IsParabolicLight();                                                                                          // 07
		virtual bool IsOmnidirectionalLight();                                                                                    // 08
		virtual void Cull(uint32_t& globalShadowLightCount, uint32_t shadowMaskChannel, NiPointer<NiAVObject> cullingScene) = 0;  // 09
		virtual void RenderShadowmaps() = 0;                                                                                      // 0A
		virtual void SetShadowmapCount(uint32_t shadowmapCount);                                                                  // 0B
		virtual void Reset();                                                                                                     // 0C
		virtual void Unk_0D();                                                                                                    // 0D
		virtual bool Unk_0E();                                                                                                    // 0E
		virtual void Unk_0F();                                                                                                    // 0F
		virtual bool SetFrameCamera(const NiCamera& frameCamera) = 0;                                                             // 10

		// members
		uint32_t                        shadowMapCount;                // 140
		uint32_t                        unk144;                        // 144
		BSTArray<ShadowmapDescriptor>   shadowmapDescriptors;          // 148
		ShadowmapDescriptor             focusShadowmapDescriptors[4];  // 160
		uint32_t                        shadowLightIndex;              // 520
		uint32_t                        unk524;                        // 524
		BSTArray<NiPointer<NiAVObject>> cullingObjects;                // 528
		float                           shadowBiasScale;               // 540
		NiRect<int32_t>                 port;                          // 544
		uint32_t                        shadowSceneNodeIndex;          // 554
		bool                            drawFocusShadows;              // 558
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSShadowLight) == 0x560);
}
