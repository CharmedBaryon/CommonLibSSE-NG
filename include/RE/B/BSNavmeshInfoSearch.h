#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSPathingDoor;
	struct BSNavmeshInfo;

	// Node type for AStarSearch<const BSNavmeshInfo*, BSTSmartPointer<BSPathingDoor>, 22>.
	// Verified offsets (from BSPrecomputedNavmeshInfoSearch::sub_1410B7F00 search step):
	//   +00 g_cost, +04 h_cost, +08 BSPathingDoor* door (= U), +10 const BSNavmeshInfo* info (= T),
	//   +20 parent ptr, +28 prev ptr, +30 next ptr.
	// IsAtGoal compares node->+08 against this->goalDoor — confirms the +08 door field.
	struct BSNavmeshInfoSearchNode
	{
		float                    g_cost;       // 00
		float                    h_cost;       // 04
		BSPathingDoor*           door;         // 08
		const BSNavmeshInfo*     info;         // 10
		std::uint8_t             pad18[0x08];  // 18
		BSNavmeshInfoSearchNode* parent;       // 20
		BSNavmeshInfoSearchNode* prev;         // 28 - linked list
		BSNavmeshInfoSearchNode* next;         // 30 - linked list
	};

	// Inherits AStarSearch<const BSNavmeshInfo*, BSTSmartPointer<BSPathingDoor>, 22> (see RTTI),
	// which contributes nearly all the 0x238 bytes. The template family also has instantiations
	// for ParentSpaceNode/TeleportLink, BSFastNavmeshTriLocation/Edge, and BSPathSmootherPOVNode.
	// Each instantiation uses a different node type, so AStarSearch is not headered as a single
	// template; the search state below is described in terms of the navmesh-info specialization.
	class BSNavmeshInfoSearch
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSNavmeshInfoSearch;
		inline static constexpr auto VTABLE = VTABLE_BSNavmeshInfoSearch;

		virtual ~BSNavmeshInfoSearch();  // 00

		virtual void GetNeighbors(BSNavmeshInfoSearchNode* a_node, void* a_outNeighbors);  // 01
		virtual bool IsAtGoal(BSNavmeshInfoSearchNode* a_node);                            // 02

		// members  (most state belongs to AStarSearch<...> base — padding regions are AStar
		//           internals: priority-queue buckets, allocator pools, etc., not yet typed)
		std::uint8_t             pad008[0x110];  // 008
		BSNavmeshInfoSearchNode* savedGoalNode;  // 118 - output: node where IsAtGoal returned true
		BSNavmeshInfoSearchNode* currentNode;    // 120 - input: candidate node passed to GetNeighbors / IsAtGoal
		std::uint8_t             pad128[0x08];   // 128
		// successor open-set. capacity (bit31 = inline-storage flag) @130, inline buffer of 22 node
		// pointers @138 (22 = AStarSearch template param), _size (neighborCount) @1E8. Verified in
		// BSPrecomputedNavmeshInfoSearch::sub_1410B7F00.
		BSTSmallArray<BSNavmeshInfoSearchNode*, 22> neighbors;      // 130
		bool                                        shouldYield;    // 1F0 - if set, search yields via Sleep(1) every 0x32 misses
		std::uint8_t                                pad1F1[0x07];   // 1F1
		NiPoint3                                    start;          // 1F8 - search start world position
		std::uint32_t                               pad204;         // 204
		void*                                       startContext;   // 208 - has NiPoint3 at +0x04 and a vtable-bearing sub-object at +0x38; NOT a BSPathingDoor (decompile of setup ruled it out)
		NiPoint3                                    goal;           // 210 - search goal world position
		std::uint32_t                               pad21C;         // 21C
		BSPathingDoor*                              goalDoor;       // 220 - CONFIRMED by IsAtGoal: node->door == this->goalDoor
		void*                                       unk228;         // 228 - stored from first ptr arg of setup; semantics TBD
		std::uint32_t                               flag230;        // 230 - uint flag from setup param
		bool                                        boolResult234;  // 234 - result of door-to-door virtual call during setup
		std::int8_t                                 char235;        // 235 - char from setup param
		std::uint16_t                               pad236;         // 236
	};
	STATIC_ASSERT_SIZE(BSNavmeshInfoSearch, 0x238);
}
