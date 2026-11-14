#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiFrustumPlanes.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class NiAVObject;
	class NiCamera;

	class BSCompoundFrustum
	{
	public:
		enum class OperatorType : std::int32_t
		{
			kNone = 0,
			kStart = 1,
			kAccept = 2,
			kReject = 3,
			kGroupIntersection = 4,
			kGroupUnion = 5,
			kGroupEnd = 6,
			kTestIntersects = 7,  // followed by an operand record whose first field indexes planes
			kTestInside = 8       // followed by an operand record whose first field indexes planes
		};

		struct Operator
		{
			REX::Enum<OperatorType, std::int32_t> type;    // 00
			std::uint32_t                         onPass;  // 04
			std::uint32_t                         onFail;  // 08
		};
		static_assert(sizeof(Operator) == 0xC);

		void GetActivePlaneState(std::uint32_t* a_outPlaneState);
		void SetActivePlaneState(std::uint32_t* a_planeState);
		bool Process(NiAVObject* a_object);

		// members
		BSTArray<NiFrustumPlanes> planes;             // 00
		BSTArray<Operator>        functionOperators;  // 18
		NiFrustumPlanes           viewFrustum;        // 30
		NiPoint3                  viewPosition;       // A0
		NiCamera*                 camera;             // B0
		uint32_t                  freePlane;          // B8
		uint32_t                  freeOp;             // BC
		uint32_t                  firstOp;            // C0
		bool                      skipViewFrustum;    // C4
		bool                      prethreaded;        // C5
	};
	static_assert(sizeof(BSCompoundFrustum) == 0xC8);
}
