#pragma once

#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkpCollidableCollidableFilter.h"
#include "RE/H/hkpRayCollidableFilter.h"
#include "RE/H/hkpRayShapeCollectionFilter.h"
#include "RE/H/hkpShapeCollectionFilter.h"

namespace RE
{
	class hkpBvTreeShape;
	class hkpWorld;

	class hkpCollisionFilter :
		public hkReferencedObject,             // 00
		public hkpCollidableCollidableFilter,  // 08
		public hkpShapeCollectionFilter,       // 10
		public hkpRayShapeCollectionFilter,    // 18
		public hkpRayCollidableFilter          // 20
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpCollisionFilter;
		inline static constexpr auto VTABLE = VTABLE_hkpCollisionFilter;

		enum class hkpFilterType
		{
			kUnknown = 0,
			kNull = 1,
			kGroup = 2,
			kList = 3,
			kFilterCustom = 4,
			kFilterPair = 5,
			kFilterConstraint = 6,
		};

		~hkpCollisionFilter() override;  // 00

		// add
		virtual void Init(hkpWorld* world);

		// override (hkpShapeCollectionFilter)
		std::int32_t NumShapeKeyHitsLimitBreached(const hkpCollisionInput& a_input, const hkpCdBody& a_bodyA, const hkpCdBody& a_bodyB, const hkpBvTreeShape* a_shapeB, hkAabb& a_AABB, hkpShapeKey* a_shapeKeysInOut, std::int32_t a_shapeKeysCapacity) const override;  // 02

		// members
		std::uint32_t                                  pad30;  // 30
		std::uint32_t                                  pad34;  // 34
		stl::enumeration<hkpFilterType, std::uint32_t> type;   // 38
		std::uint32_t                                  pad3C;  // 3C
		std::uint32_t                                  pad40;  // 40
		std::uint32_t                                  pad44;  // 44
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpCollisionFilter) == 0x48);
}
