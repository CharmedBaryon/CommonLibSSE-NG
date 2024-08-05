#pragma once

#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkpCdBody;

	struct hkpCollisionInput;

	class hkpConvexListFilter : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpConvexListFilter;
		inline static constexpr auto VTABLE = VTABLE_hkpConvexListFilter;

		enum class ConvexListCollisionType
		{
			kNormal = 0,
			kList,
			kConvex
		};

		~hkpConvexListFilter() override;  // 00

		// add
		virtual ConvexListCollisionType GetConvexListCollisionType(const hkpCdBody& a_convexListBody, const hkpCdBody& a_otherBody, const hkpCollisionInput& a_input) const = 0;  // 03
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpConvexListFilter) == 0x10);
}
