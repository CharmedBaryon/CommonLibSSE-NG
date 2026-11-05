#pragma once

#include "RE/N/NiSingleInterpController.h"

namespace RE
{
	class NiFloatInterpController : public NiSingleInterpController
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiFloatInterpController;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiFloatInterpController;
		inline static constexpr auto VTABLE = VTABLE_NiFloatInterpController;

		~NiFloatInterpController() override;  // 00

		// override (NiSingleInterpController)
		const NiRTTI*                      GetRTTI() const override;                                                                                                                                                                               // 02
		void                               LoadBinary(NiStream& a_stream) override;                                                                                                                                                                // 18
		void                               LinkObject(NiStream& a_stream) override;                                                                                                                                                                // 19
		bool                               RegisterStreamables(NiStream& a_stream) override;                                                                                                                                                       // 1A
		void                               SaveBinary(NiStream& a_stream) override;                                                                                                                                                                // 1B
		bool                               IsEqual(NiObject* a_object) override;                                                                                                                                                                   // 1C
		NiInterpolator*                    CreatePoseInterpolator(std::uint16_t a_index) override;                                                                                                                                                 // 37
		void                               SynchronizePoseInterpolator(NiInterpolator* a_interp, std::uint16_t a_index = 0) override;                                                                                                              // 38
		[[nodiscard]] NiBlendInterpolator* CreateBlendInterpolator(std::uint16_t a_index = 0, bool a_managerControlled = false, bool a_accumulateAnimations = false, float a_weightThreshold = 0.0, std::uint8_t a_arraySize = 2) const override;  // 39
		bool                               InterpolatorIsCorrectType(NiInterpolator* a_interpolator, std::uint16_t a_index) const override;                                                                                                        // 3B

		// add
		virtual void GetTargetFloatValue(float& a_value) = 0;  // 3D
	};
	static_assert(sizeof(NiFloatInterpController) == 0x50);
}
