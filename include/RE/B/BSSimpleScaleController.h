#pragma once

#include "RE/N/NiTimeController.h"

namespace RE
{
	class BSSimpleScaleController : public NiTimeController
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSSimpleScaleController;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSSimpleScaleController;
		inline static constexpr auto VTABLE = VTABLE_BSSimpleScaleController;

		~BSSimpleScaleController() override;  // 00

		// override (NiTimeController)
		const NiRTTI*      GetRTTI() const override;                           // 02
		NiObject*          CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void               Update(float a_time) override;                      // 27
		[[nodiscard]] bool TargetIsRequiredType() const override;              // 2E

		// members
		float scale3D;            // 48
		float refScale;           // 4C
		float scaleAnimDuration;  // 50
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSSimpleScaleController) == 0x58);
}
