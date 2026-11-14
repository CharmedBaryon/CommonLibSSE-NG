#pragma once

#include "RE/N/NiMatrix3.h"
#include "RE/N/NiObject.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSOcclusionShape : public NiObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSOcclusionShape;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSOcclusionShape;
		inline static constexpr auto VTABLE = VTABLE_BSOcclusionShape;

		~BSOcclusionShape() override;  // 00

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17

		// add
		virtual bool IsOcclusionPlane() const = 0;  // 25
		virtual bool IsOcclusionBox() const = 0;    // 26

		// members
		NiPoint3      translation;            // 10
		NiMatrix3     rotation;               // 1C
		std::uint32_t visibilityState;        // 40 - 0 untested, 1 visible, 2 hidden, 3 hidden by bound test
		bool          updateFacesOrVertices;  // 44
	};
	static_assert(sizeof(BSOcclusionShape) == 0x48);
}
