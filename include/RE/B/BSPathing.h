#pragma once

#include "RE/B/BSPathingLocation.h"
#include "RE/F/FindTriangleForLocationFilterCheckDeltaZ.h"

namespace RE
{
	class BSPathingLockData;
	class BSPathingStreamRead;
	class BSPathingStreamWrite;
	class IDebugText;
	class IMovementParameters;
	class MovementMessage;
	class PathingCell;

	struct BSVirtualPathingNode
	{
		BSPathingLocation                location;      // 00
		BSTSmartPointer<MovementMessage> actionAtNode;  // 30
	};
	static_assert(sizeof(BSVirtualPathingNode) == 0x38);

	struct BSPathingNode
	{
		BSPathingLocation                location;      // 00
		BSTSmartPointer<MovementMessage> actionAtNode;  // 30;
		NiPoint3                         tangent;       // 38
	};
	static_assert(sizeof(BSPathingNode) == 0x48);

	struct BSPathingSolution : BSIntrusiveRefCounted
	{
		BSTSmallArray<BSVirtualPathingNode, 2> virtualPathingNodes;          // 08
		std::int32_t                           firstLoadedVirtualNodeIndex;  // 88
		std::int32_t                           lastLoadedVirtualNodeIndex;   // 8C
		BSTArray<BSPathingNode>                currentPathingNodes;          // 90
		bool                                   bIncompletePath;              // A8
		bool                                   bRequestGoalUnused;           // A9
	};
	static_assert(sizeof(BSPathingSolution) == 0xB0);

	struct BSPathingStart
	{
		BSPathingLocation location;  // 00
		float             tangent;   // 30
	};
	static_assert(sizeof(BSPathingStart) == 0x38);

	struct BSPathingGoal
	{
		NiPoint3          targetPoint;           // 00
		float             targetAngleTolerance;  // 0C
		BSPathingLocation location;              // 10
		float             zDelta;                // 40
		float             goalRadius;            // 44
		float             normalizeSpeedAtGoal;  // 48
	};
	static_assert(sizeof(BSPathingGoal) == 0x50);

	class BSPathingAvoidNode;

	struct BSPathingRestrictions
	{
		struct BSPathingSearchAreaRestrictions
		{
			NiPoint3 center;  // 00
			float    radius;  // 08
		};

		NiPointer<BSTArray<BSPathingAvoidNode>> avoidNodeArray;    // 00
		BSPathingSearchAreaRestrictions         areaRestrictions;  // 08
	};
	static_assert(sizeof(BSPathingRestrictions) == 0x18);

	class BSPathingSearchParameters;
	class BSPathingActorAttributes;
	class MovementActorAvoidanceParameters;
	class BSPathingRequest;

	class BSPathing : public BSTSingletonExplicit<BSPathing>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathing;
		inline static constexpr auto VTABLE = VTABLE_BSPathing;

		virtual ~BSPathing();  // 00

		// add
		virtual BSTArray<BSNavmeshInfo*> GetPotentialNavMeshInfoForLocation(PathingCell* a_cell) = 0;                                             // 01
		virtual bool                     GetAllLoadedNavmeshes1(BSTScrapHashMap<std::uint32_t, BSTSmartPointer<BSNavmesh>>& a_retNavMeshes) = 0;  // 02
		virtual bool                     GetAllLoadedNavmeshes2(BSScrapArray<BSNavmeshInfo*>& a_retNavMeshes) = 0;                                // 03
		virtual bool                     GetAllLoadedNavmeshes3(BSTArray<BSNavmeshInfo*>& a_retNavMeshes) = 0;                                    // 04
		virtual bool                     GetAllLoadedNavmeshes4(BSScrapArray<BSTSmartPointer<BSNavmesh>>& a_retNavMeshes) = 0;                    // 05
		virtual bool                     GetAllLoadedNavmeshes5(BSTArray<BSTSmartPointer<BSNavmesh>>& a_retNavMeshes) = 0;                        // 06
		virtual FormID                   GetSelectedDebugRef() = 0;                                                                               // 07
		virtual bool                     GetPathingDoorFromCollision(NiAVObject* a_object, BSTSmartPointer<BSPathingDoor>& a_retDoor) = 0;        // 08

		// members
		FindTriangleForLocationFilterCheckDeltaZ defaultTriangleFilter;  // 08
	};
	static_assert(sizeof(BSPathing) == 0x18);
}
