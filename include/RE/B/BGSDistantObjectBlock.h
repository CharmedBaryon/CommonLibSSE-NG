#pragma once

#include "RE/B/BSNiNode.h"
#include "RE/B/BSStream.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BGSMaterialObject;
	class BGSTerrainNode;

	class BGSDistantObjectBlock
	{
	public:
		BGSDistantObjectBlock(BGSTerrainNode* a_node, BSStream& a_stream);
		~BGSDistantObjectBlock() = default;

		static BGSMaterialObject* GetAshLODMaterial();
		static BGSMaterialObject* GetAshLODMaterialHD();
		static BGSMaterialObject* GetSnowLODMaterial();
		static BGSMaterialObject* GetSnowLODMaterialHD();

		void Attach();
		void Detach();
		void Prepare();

		// members
		BGSTerrainNode*   terrainNode;  // 00
		NiPointer<NiNode> node;         // 08
		bool              doneLoading;  // 10
		bool              attached;     // 11
		bool              prepared;     // 12
		std::uint8_t      pad13[5];     // 13

	private:
		BGSDistantObjectBlock* Ctor(BGSTerrainNode* a_node, BSStream& a_stream);
	};
	static_assert(sizeof(BGSDistantObjectBlock) == 0x18);
}
