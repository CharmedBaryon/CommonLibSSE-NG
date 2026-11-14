#pragma once

#include "RE/B/BSGeometry.h"
#include "RE/B/BSMultiBoundNode.h"
#include "RE/B/BSStream.h"

namespace RE
{
	class BGSTerrainNode;

	class BGSTerrainChunk
	{
	public:
		BGSTerrainChunk(BGSTerrainNode* a_node, BSStream& a_stream, std::int32_t a_cellX, std::int32_t a_cellY);
		~BGSTerrainChunk();

		static void           AttachWater(bool a_attach);
		static std::uint32_t& GetChunkCount();  // increased in ctor, decreased in dtor

		void Attach();
		void Detach();
		void Prepare();

		// members
		BGSTerrainNode*             terrainNode;    // 00
		NiPointer<BSGeometry>       landMesh;       // 08
		NiPointer<BSMultiBoundNode> waterNode;      // 10
		NiPointer<BSMultiBoundNode> chunk;          // 18
		bool                        doneLoading;    // 20
		bool                        attached;       // 21
		bool                        waterAttached;  // 22
		bool                        prepared;       // 23
		std::uint32_t               pad24;          // 24

	private:
		BGSTerrainChunk* Ctor(BGSTerrainNode* a_node, BSStream& a_stream, std::int32_t a_cellX, std::int32_t a_cellY);
		void             Dtor();
	};
	static_assert(sizeof(BGSTerrainChunk) == 0x28);
}
