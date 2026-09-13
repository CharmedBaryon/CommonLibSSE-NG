#include "RE/B/BGSDistantTreeBlock.h"

namespace RE
{
	BGSDistantTreeBlock::BGSDistantTreeBlock(BGSTerrainNode* a_node, std::uint32_t a_LODLevel)
	{
		Ctor(a_node, a_LODLevel);
	}

	NiPointer<NiTexture>& BGSDistantTreeBlock::GetAtlasTexture()
	{
		static REL::Relocation<NiPointer<NiTexture>*> tex{ RELOCATION_ID(516086, 402199) };
		return *tex;
	}

	NiPointer<NiAlphaProperty>& BGSDistantTreeBlock::GetSharedAlpha()
	{
		static REL::Relocation<NiPointer<NiAlphaProperty>*> alpha{ RELOCATION_ID(516087, 402200) };
		return *alpha;
	}

	BSTArray<BGSDistantTreeBlock::TreeType>& BGSDistantTreeBlock::GetTreeTypes()
	{
		static REL::Relocation<BSTArray<TreeType>*> types{ RELOCATION_ID(516088, 402201) };
		return *types;
	}

	void BGSDistantTreeBlock::Attach()
	{
		using func_t = decltype(&BGSDistantTreeBlock::Attach);
		static REL::Relocation<func_t> func{ RELOCATION_ID(30832, 31653) };
		func(this);
	}

	void BGSDistantTreeBlock::Detach()
	{
		using func_t = decltype(&BGSDistantTreeBlock::Detach);
		static REL::Relocation<func_t> func{ RELOCATION_ID(30830, 31651) };
		func(this);
	}

	BGSDistantTreeBlock* BGSDistantTreeBlock::Ctor(BGSTerrainNode* a_node, std::uint32_t a_LODLevel)
	{
		using func_t = decltype(&BGSDistantTreeBlock::Ctor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(30826, 31647) };  // AE: not used by the game, inlined somewhere else
		return func(this, a_node, a_LODLevel);
	}
}
