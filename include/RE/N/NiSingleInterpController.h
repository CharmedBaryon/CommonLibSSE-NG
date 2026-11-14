#pragma once

#include "RE/N/NiInterpController.h"
#include "RE/N/NiInterpolator.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiSingleInterpController : public NiInterpController
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiSingleInterpController;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiSingleInterpController;
		inline static constexpr auto VTABLE = VTABLE_NiSingleInterpController;

		~NiSingleInterpController() override;  // 00

		// override (NiInterpController)
		const NiRTTI*                 GetRTTI() const override;                                                             // 02
		void                          LoadBinary(NiStream& a_stream) override;                                              // 18
		void                          LinkObject(NiStream& a_stream) override;                                              // 19
		bool                          RegisterStreamables(NiStream& a_stream) override;                                     // 1A
		void                          SaveBinary(NiStream& a_stream) override;                                              // 1B
		bool                          IsEqual(NiObject* a_object) override;                                                 // 1C
		void                          ProcessClone(NiCloningProcess& a_cloning) override;                                   // 1D
		[[nodiscard]] bool            TargetIsRequiredType() const override;                                                // 2E
		[[nodiscard]] std::uint16_t   GetInterpolatorCount() const override;                                                // 2F - { return 1; }
		const char*                   GetInterpolatorID(std::uint16_t a_index = 0) override;                                // 30
		std::uint16_t                 GetInterpolatorIndex(const char* a_id) const override;                                // 31
		[[nodiscard]] std::uint16_t   GetInterpolatorIndexFx(const BSFixedString& a_id) const override;                     // 32
		[[nodiscard]] NiInterpolator* GetInterpolator(std::uint16_t a_index = 0) const override;                            // 33 - { return interpolator.get(); }
		void                          SetInterpolator(NiInterpolator* a_interpolator, std::uint16_t a_index = 0) override;  // 34
		void                          ResetTimeExtrema() override;                                                          // 35
		void                          GuaranteeTimeRange(float a_startTime, float a_endTime) override;                      // 3A

		// add
		[[nodiscard]] virtual bool InterpTargetIsCorrectType(NiObjectNET* a_target) const = 0;  // 3C

		// members
		NiPointer<NiInterpolator> interpolator;  // 48
	};
	static_assert(sizeof(NiSingleInterpController) == 0x50);
}
