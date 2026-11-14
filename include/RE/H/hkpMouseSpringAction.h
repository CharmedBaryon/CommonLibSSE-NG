#pragma once

#include "RE/H/hkpUnaryAction.h"

namespace RE
{
	class hkpMouseSpringAction : public hkpUnaryAction
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpMouseSpringAction;
		inline static constexpr auto VTABLE = VTABLE_hkpMouseSpringAction;

		using MouseSpringAppliedCallback = void(hkpMouseSpringAction* a_mouseSpring, const hkStepInfo& a_stepInfo, const hkVector4& a_impulseApplied);

		virtual ~hkpMouseSpringAction() override;  // 00

		// override (hkpUnaryAction)
		void       ApplyAction(const hkStepInfo& a_stepInfo) override;                                                         // 03
		void       EntityRemovedCallback(hkpEntity* a_entity) override;                                                        // 06
		hkpAction* Clone(const hkArray<hkpEntity*>& a_newEntities, const hkArray<hkpPhantom*>& a_newPhantoms) const override;  // 07

		// members
		hkVector4                            positionInRbLocal;     // 40
		hkVector4                            mousePositionInWorld;  // 50
		float                                springDamping;         // 60
		float                                springElasticity;      // 64
		float                                maxRelativeForce;      // 68
		float                                objectDamping;         // 6C
		hkpShapeKey                          shapeKey;              // 70
		std::uint32_t                        pad74;                 // 74
		hkArray<MouseSpringAppliedCallback*> applyCallbacks;        // 78
	};
	static_assert(sizeof(hkpMouseSpringAction) == 0x90);
}
