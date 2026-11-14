#pragma once

#include <cstdint>

#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSNavmesh;

	// Node type for AStarSearch<BSFastNavmeshTriLocation, BSFastNavmeshEdgeHandle, 3>
	// (used by BSNavmeshSearch / CombatNavmeshSearch). Not a generic A* node — the
	// 4 other AStarSearch template instantiations in the binary use different node
	// layouts. Verified from BSNavmeshSearch::Func1_1410EBA00 (VR 0x141148740):
	// successor allocation writes h_cost, navMesh+triIndex, NiPoint3 center, parent
	// backlink, and edge index at the offsets below.
	struct AStarNode
	{
		float         g_cost;                // 00 - cost from start
		float         h_cost;                // 04 - heuristic to goal
		BSNavmesh*    navMesh;               // 08
		std::uint16_t triIndex;              // 10
		std::uint16_t pad12;                 // 12
		std::uint32_t pad14;                 // 14
		NiPoint3      center;                // 18 - triangle centroid
		std::uint32_t pad24;                 // 24
		BSNavmesh*    parentNavMesh;         // 28 - navMesh of predecessor node
		std::uint16_t parentTriIndex;        // 30
		std::uint16_t pad32;                 // 32
		std::uint32_t pad34;                 // 34
		std::int32_t  edgeIndex;             // 38 - which edge (0..2) we crossed from parent
		std::uint32_t pad3C;                 // 3C
		std::uint8_t  pad40[(0x58 - 0x40)];  // 40 - open/closed bookkeeping (unverified)
		AStarNode*    next;                  // 58 - linked list pointer (unverified)
	};
	static_assert(sizeof(AStarNode) == 0x60, "size");
}
