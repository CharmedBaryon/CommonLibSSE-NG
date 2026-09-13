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
		void GetActivePlaneState(std::uint32_t* a_outPlaneState);
		void SetActivePlaneState(std::uint32_t* a_planeState);
		bool Process(NiAVObject* a_object);

		// members
		BSTArray<NiFrustumPlanes> planes;             // 00
		BSTArray<void*>           functionOperators;  // 18
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
