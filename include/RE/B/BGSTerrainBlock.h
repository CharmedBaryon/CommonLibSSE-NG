#pragma once

#include "RE/B/BSTriShape.h"

namespace RE
{
	class BGSTerrainNode;

	class BGSTerrainBlock
	{
	public:
		// members
		BGSTerrainNode*   node;           // 00
		BSTriShape*       land;           // 08
		BSMultiBoundNode* water;          // 10
		BSMultiBoundNode* chunk;          // 18
		bool              loaded;         // 20
		bool              attached;       // 21
		bool              waterAttached;  // 22
		bool              unk23;          // 23
		uint32_t          unk24;          // 24
		uint32_t          unk28;          // 28
		uint32_t          unk2C;          // 2C
		uint64_t          unk30;          // 30
		uint64_t          unk38;          // 38
		uint64_t          unk40;          // 40
		uint64_t          unk48;          // 48
		uint64_t          unk50;          // 50
		uint64_t          unk58;          // 58
		uint64_t          unk60;          // 60
		uint64_t          unk68;          // 68
		uint64_t          unk70;          // 70
		uint64_t          unk78;          // 78
		bool              unk80;          // 80
		bool              unk81;          // 81
		bool              unk82;          // 82
		bool              unk83;          // 83
	};
}
