#include "RE/B/BGSTerrainChunk.h"

namespace RE
{
	BGSTerrainChunk::BGSTerrainChunk(BGSTerrainNode* a_node, BSStream& a_stream, std::int32_t a_cellX, std::int32_t a_cellY)
	{
		Ctor(a_node, a_stream, a_cellX, a_cellY);
	}

	BGSTerrainChunk::~BGSTerrainChunk()
	{
		Dtor();
	}

	void BGSTerrainChunk::AttachWater(bool a_attach)
	{
		using func_t = decltype(&BGSTerrainChunk::AttachWater);
		static REL::Relocation<func_t> func{ RELOCATION_ID(30939, 31742) };
		func(a_attach);
	}

	std::uint32_t& BGSTerrainChunk::GetChunkCount()  // increased in ctor, decreased in dtor
	{
		static REL::Relocation<std::uint32_t*> count{ RELOCATION_ID(516095, 402227) };
		return *count;
	}

	void BGSTerrainChunk::Attach()
	{
		using func_t = decltype(&BGSTerrainChunk::Attach);
		static REL::Relocation<func_t> func{ RELOCATION_ID(30934, 31737) };
		func(this);
	}

	void BGSTerrainChunk::Detach()
	{
		using func_t = decltype(&BGSTerrainChunk::Detach);
		static REL::Relocation<func_t> func{ RELOCATION_ID(30936, 31739) };
		func(this);
	}

	void BGSTerrainChunk::Prepare()
	{
		using func_t = decltype(&BGSTerrainChunk::Prepare);
		static REL::Relocation<func_t> func{ RELOCATION_ID(30947, 31750) };
		func(this);
	}

	BGSTerrainChunk* BGSTerrainChunk::Ctor(BGSTerrainNode* a_node, BSStream& a_stream, std::int32_t a_cellX, std::int32_t a_cellY)
	{
		using func_t = decltype(&BGSTerrainChunk::Ctor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(30932, 31735) };
		return func(this, a_node, a_stream, a_cellX, a_cellY);
	}

	void BGSTerrainChunk::Dtor()
	{
		using func_t = decltype(&BGSTerrainChunk::Dtor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(30933, 31736) };
		func(this);
	}
}
