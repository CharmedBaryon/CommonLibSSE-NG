#pragma once

#include "RE/H/hkAabb.h"
#include "RE/H/hkpShape.h"

namespace RE
{
	class hkpBvTreeShape;
	class hkpCdBody;
	class hkpShapeContainer;

	struct hkpCollisionInput;

	class hkpShapeCollectionFilter
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpShapeCollectionFilter;
		inline static constexpr auto VTABLE = VTABLE_hkpShapeCollectionFilter;

		// add
		virtual bool         IsCollisionEnabled1(const hkpCollisionInput& a_input, const hkpCdBody& a_bodyA, const hkpCdBody& a_bodyB, const hkpShapeContainer& a_shapeB, hkpShapeKey a_key) const = 0;                                                                      // 00
		virtual bool         IsCollisionEnabled2(const hkpCollisionInput& a_input, const hkpCdBody& a_bodyA, const hkpCdBody& a_bodyB, const hkpShapeContainer& a_shapeA, const hkpShapeContainer& a_shapeB, hkpShapeKey a_keyA, hkpShapeKey a_keyB) const = 0;              // 01
		virtual std::int32_t NumShapeKeyHitsLimitBreached(const hkpCollisionInput& a_input, const hkpCdBody& a_bodyA, const hkpCdBody& a_bodyB, const hkpBvTreeShape* a_shapeB, hkAabb& a_AABB, hkpShapeKey* a_shapeKeysInOut, std::int32_t a_shapeKeysCapacity) const = 0;  // 02

		virtual ~hkpShapeCollectionFilter();  // 03
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpShapeCollectionFilter) == 0x08);
}
