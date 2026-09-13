#pragma once

#include "RE/B/BSCullingProcess.h"

namespace RE
{
	class BSShaderAccumulator;

	class BSParabolicCullingProcess : public BSCullingProcess
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSParabolicCullingProcess;
		inline static constexpr auto VTABLE = VTABLE_BSParabolicCullingProcess;

		// override (BSCullingProcess)
		const NiRTTI* GetRTTI() const override;  // 00

		~BSParabolicCullingProcess() override;  // 15

		virtual void               Process1(NiAVObject* a_object, std::int32_t a_arg2) override;                                    // 16
		virtual void               Process2(const NiCamera* a_camera, NiAVObject* a_scene, NiVisibleArray* a_visibleSet) override;  // 17
		virtual void               AppendNonAccum(NiAVObject& a_object, std::int32_t a_arg2) override;                              // 19
		virtual bool               TestBaseVisibility1(BSMultiBound& a_bound) override;                                             // 1A
		virtual bool               TestBaseVisibility2(BSOcclusionPlane& a_bound) override;                                         // 1B
		[[nodiscard]] virtual bool TestBaseVisibility3(const NiBound& a_bound) override;                                            // 1C

		float                          unk301F8;                   // 301F8
		NiPointer<BSShaderAccumulator> backHemisphereAccumulator;  // 30200
		NiPlane                        equatorialPlane;            // 30208
		NiPoint3                       lightPosition;              // 30218
		float                          lightRadius;                // 30224
		NiPointer<NiCamera>            lightCamera;                // 30228
	};
	static_assert(sizeof(BSParabolicCullingProcess) == 0x30230);
}
