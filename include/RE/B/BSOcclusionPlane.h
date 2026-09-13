#pragma once

#include "RE/B/BSCompoundFrustum.h"
#include "RE/B/BSOcclusionShape.h"
#include "RE/N/NiPoint2.h"

namespace RE
{
	class BSOcclusionPlane : public BSOcclusionShape
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSOcclusionPlane;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSOcclusionPlane;
		inline static constexpr auto VTABLE = VTABLE_BSOcclusionPlane;

		~BSOcclusionPlane() override;  // 00

		// override (BSOcclusionShape)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		bool          IsOcclusionPlane() const override;                  // 25
		bool          IsOcclusionBox() const override;                    // 25

		bool WithinFrustumDistFirst(const NiFrustumPlanes* a_planes, const NiPoint3* a_point);

		// members
		NiPoint2          size;     // 48
		BSCompoundFrustum frustum;  // 50
	};
	static_assert(sizeof(BSOcclusionPlane) == 0x118);
}
