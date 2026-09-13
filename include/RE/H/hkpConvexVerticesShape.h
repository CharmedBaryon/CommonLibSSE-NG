#pragma once

#include "RE/H/hkpConvexShape.h"

#include "RE/H/hkArray.h"

namespace RE
{
	class hkpConvexVerticesConnectivity;

	class hkFourTransposedPoints
	{
	public:
		hkVector4 x;
		hkVector4 y;
		hkVector4 z;
	};
	static_assert(sizeof(hkFourTransposedPoints) == 0x30);

	class hkpConvexVerticesShape : public hkpConvexShape
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpConvexVerticesShape;
		inline static constexpr auto VTABLE = VTABLE_hkpConvexVerticesShape;

		~hkpConvexVerticesShape() override;  // 00

		// override (hkpConvexShape)
		void             CalcContentStatistics(hkStatisticsCollector* a_collector, const hkClass* a_class) const override;     // 02
		std::int32_t     CalcSizeForSpu(const CalcSizeForSpuInput& a_input, std::int32_t a_spuBufferSizeLeft) const override;  // 06
		void             GetAabbImpl(const hkTransform& a_localToWorld, float a_tolerance, hkAabb& a_out) const override;      // 07
		bool             CastRayImpl(const hkpShapeRayCastInput& a_input, hkpShapeRayCastOutput& a_output) const override;     // 08
		std::int32_t     GetNumCollisionSpheresImpl() override;                                                                // 0B
		const hkpSphere* GetCollisionSpheresImpl(hkSphere* a_sphereBuffer) override;                                           // 0C

		// members
		hkVector4                              aabbHalfExtents;  // 30
		hkVector4                              aabbCenter;       // 40
		hkArray<hkFourTransposedPoints>        rotatedVertices;  // 50
		std::int32_t                           numVertices;      // 60
		void*                                  externalObject;   // 68
		void*                                  getFaceNormals;   // 70
		mutable hkArray<hkVector4>             planeEquations;   // 78
		mutable hkpConvexVerticesConnectivity* connectivity;     // 88
	};
	static_assert(sizeof(hkpConvexVerticesShape) == 0x90);
}
