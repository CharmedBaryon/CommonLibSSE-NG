#pragma once

#include "RE/B/BGSTerrainNode.h"
#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"
#include "RE/N/NiNode.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BGSTerrainNode;
	class TESWorldSpace;

	class BGSTerrainManager
	{
	public:
		struct CullState
		{
		public:
			// members
			bool cullRoot;     // 00
			bool cullLand;     // 01
			bool cullTrees;    // 02
			bool cullObjects;  // 03
		};
		static_assert(sizeof(CullState) == 0x4);

		static bool&              CameraAboveMaxHeight();
		static bool&              Enabled();  // always true?
		static BGSTerrainManager* GetActiveManager();
		static BSSpinLock&        GetCameraTerrainLock();
		static NiPointer<NiNode>& GetLODLandRoot();
		static NiNode*            GetLODLandRootForLevel(std::uint32_t a_level);
		static NiPointer<NiNode>& GetLODObjectRoot();
		static NiPointer<NiNode>& GetLODRoot();
		static NiPointer<NiNode>& GetTreeNode();
		static NiPointer<NiNode>& GetWaterNode();
		static bool&              LoadScreenUp();

		void SetCullState(const CullState& a_state);
		void UnloadAll(bool a_unloadStaticData, bool a_shutdown);
		void Update(const NiPoint3& a_viewPos, const std::int32_t& a_updateType);

		// members
		bool                      mapMode;               // 00
		std::uint8_t              pad01[7];              // 01
		TESWorldSpace*            worldSpace;            // 08
		BGSTerrainNode*           rootNode;              // 10
		std::int16_t              minCellX;              // 18 - read from .lod file
		std::int16_t              minCellY;              // 1A - read from .lod file
		std::uint32_t             maxLevel;              // 1C - read from .lod file
		std::uint32_t             minLevel;              // 20 - read from .lod file
		std::uint32_t             rootLevel;             // 24 - read from .lod file
		std::uint32_t             segmentedBlockLevel;   // 28 - default 4
		std::uint32_t             treeLevel;             // 2C - default 4
		CullState                 cachedCullState;       // 30 - cached in SetCullState
		bool                      needsImmediateUpdate;  // 34
		std::uint8_t              unk35;                 // 35
		bool                      hasLOD;                // 36
		std::uint8_t              unk37;                 // 37
		std::uint64_t             unk38;                 // 38
		std::uint64_t             unk40;                 // 40
		std::uint64_t             unk48;                 // 48
		std::uint64_t             unk50;                 // 50
		bool                      staticDataLoaded;      // 58
		std::uint8_t              unk59;                 // 59
		std::uint16_t             unk5A;                 // 5A
		std::uint32_t             unk5C;                 // 5C
		BSTArray<BGSTerrainNode*> updateNodes;           // 60
		std::uint32_t             nextUpdateNode;        // 78
		std::uint32_t             unk7C;                 // 7C
		BSTArray<BGSTerrainNode*> immediateUpdates;      // 80
		BSSpinLock                immediateUpdateLock;   // 98
		std::uint64_t             unkA0;                 // A0
		std::uint64_t             unkA8;                 // A8
		std::uint64_t             unkB0;                 // B0
		std::uint64_t             unkB8;                 // B8
		std::uint64_t             unkC0;                 // C0
		std::uint64_t             unkC8;                 // C8
	};
	static_assert(sizeof(BGSTerrainManager) == 0xD0);
}
