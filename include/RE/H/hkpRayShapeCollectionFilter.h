#pragma once

#include "RE/H/hkpShape.h"

namespace RE
{
	class hkpShapeContainer;

	struct hkpShapeRayCastInput;

	class hkpRayShapeCollectionFilter
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpRayShapeCollectionFilter;
		inline static constexpr auto VTABLE = VTABLE_hkpRayShapeCollectionFilter;

		// add
		virtual bool IsCollisionEnabled(const hkpShapeRayCastInput& a_input, const hkpShapeContainer& a_container, hkpShapeKey a_key) const = 0;  // 00

		virtual ~hkpRayShapeCollectionFilter();  // 01
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpRayShapeCollectionFilter) == 0x08);
}
