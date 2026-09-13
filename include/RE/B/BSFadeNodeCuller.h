#pragma once

#include "RE/N/NiCullingProcess.h"

namespace RE
{
	class BSFadeNodeCuller : public NiCullingProcess
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSFadeNodeCuller;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSFadeNodeCuller;
		inline static constexpr auto VTABLE = VTABLE_BSFadeNodeCuller;

		// override (NiCullingProcess)
		const NiRTTI* GetRTTI() const override;  // 00

		~BSFadeNodeCuller() override;  // 15

		void Process1(NiAVObject* a_object, std::int32_t a_arg2) override;                                    // 16
		void Process2(const NiCamera* a_camera, NiAVObject* a_scene, NiVisibleArray* a_visibleSet) override;  // 17
		void AppendVirtual(BSGeometry& a_visible, std::int32_t a_arg2) override;                              // 18
	};
	static_assert(sizeof(BSFadeNodeCuller) == 0x128);
}
