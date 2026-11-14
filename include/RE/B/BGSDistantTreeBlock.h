#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BGSTerrainNode;
	class BSMultiStreamInstanceTriShape;
	class BSTriShape;
	class NiAlphaProperty;
	class NiTexture;

	class BGSDistantTreeBlock
	{
	public:
		BGSDistantTreeBlock(BGSTerrainNode* a_node, std::uint32_t a_LODLevel);
		~BGSDistantTreeBlock() = default;

		struct InstanceData
		{
		public:
			// members
			FormID        id;      // 00 - Only the lower 24 bits used
			std::uint16_t x;       // 04
			std::uint16_t y;       // 06
			std::uint16_t z;       // 08
			std::uint16_t rotZ;    // 0A
			std::uint16_t scale;   // 0C
			std::uint16_t alpha;   // 0E - This is Float2Word(fAlpha)
			bool          hidden;  // 10 - alpha <= 0.0f or set by object flags
			std::uint8_t  pad11;   // 11
			std::uint16_t pad12;   // 12
		};
		static_assert(sizeof(InstanceData) == 0x14);

		struct TreeGroup
		{
		public:
			// members
			NiPointer<BSMultiStreamInstanceTriShape> geometry;                // 00
			BSTArray<InstanceData>                   instances;               // 08
			std::uint32_t                            num;                     // 20
			bool                                     shaderPropertyUpToDate;  // 24
			std::uint8_t                             treeType;                // 25
			std::uint16_t                            pad26;                   // 26
		};
		static_assert(sizeof(TreeGroup) == 0x28);

		struct TreeType
		{
		public:
			// members
			std::uint32_t         index;      // 00 - .lst file
			float                 width;      // 04 - .lst file
			float                 height;     // 08 - .lst file
			float                 uvMinX;     // 0C - .lst file
			float                 uvMinY;     // 10 - .lst file
			float                 uvMaxX;     // 14 - .lst file
			float                 uvMaxY;     // 18 - .lst file
			std::uint32_t         unk1C;      // 1C - .lst file, unused
			NiPointer<BSTriShape> treeModel;  // 20 - created with data above
		};
		static_assert(sizeof(TreeType) == 0x28);

		static NiPointer<NiTexture>&       GetAtlasTexture();
		static NiPointer<NiAlphaProperty>& GetSharedAlpha();
		static BSTArray<TreeType>&         GetTreeTypes();

		void Attach();
		void Detach();

		// members
		BSTArray<TreeGroup*>                     treeGroups;   // 00
		BSTHashMap<std::uint32_t, InstanceData*> instanceMap;  // 18
		BSTHashMap<std::uint32_t, TreeGroup*>    nextGroup;    // 48
		BGSTerrainNode*                          node;         // 78
		bool                                     doneLoading;  // 80
		bool                                     attached;     // 81
		bool                                     allVisible;   // 82
		std::uint8_t                             pad83;        // 83
		std::uint32_t                            pad84;        // 84

	private:
		BGSDistantTreeBlock* Ctor(BGSTerrainNode* a_node, std::uint32_t a_LODLevel);
	};
	static_assert(sizeof(BGSDistantTreeBlock) == 0x88);
}
