#include "RE/B/BGSDistantObjectBlock.h"

namespace RE
{
	BGSDistantObjectBlock::BGSDistantObjectBlock(BGSTerrainNode* a_node, BSStream& a_stream)
	{
		Ctor(a_node, a_stream);
	}

	BGSMaterialObject* BGSDistantObjectBlock::GetAshLODMaterial()
	{
		static REL::Relocation<BGSMaterialObject**> mat{ RELOCATION_ID(516052, 402146) };
		return *mat;
	}

	BGSMaterialObject* BGSDistantObjectBlock::GetAshLODMaterialHD()
	{
		static REL::Relocation<BGSMaterialObject**> mat{ RELOCATION_ID(516053, 402147) };
		return *mat;
	}

	BGSMaterialObject* BGSDistantObjectBlock::GetSnowLODMaterial()
	{
		static REL::Relocation<BGSMaterialObject**> mat{ RELOCATION_ID(516050, 402144) };
		return *mat;
	}

	BGSMaterialObject* BGSDistantObjectBlock::GetSnowLODMaterialHD()
	{
		static REL::Relocation<BGSMaterialObject**> mat{ RELOCATION_ID(516051, 402145) };
		return *mat;
	}

	void BGSDistantObjectBlock::Attach()
	{
		using func_t = decltype(&BGSDistantObjectBlock::Attach);
		static REL::Relocation<func_t> func{ RELOCATION_ID(30741, 31581) };
		func(this);
	}

	void BGSDistantObjectBlock::Detach()
	{
		using func_t = decltype(&BGSDistantObjectBlock::Detach);
		static REL::Relocation<func_t> func{ RELOCATION_ID(30739, 31577) };
		func(this);
	}

	void BGSDistantObjectBlock::Prepare()
	{
		using func_t = decltype(&BGSDistantObjectBlock::Prepare);
		static REL::Relocation<func_t> func{ RELOCATION_ID(30746, 31587) };
		func(this);
	}

	BGSDistantObjectBlock* BGSDistantObjectBlock::Ctor(BGSTerrainNode* a_node, BSStream& a_stream)
	{
		using func_t = decltype(&BGSDistantObjectBlock::Ctor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(30737, 31575) };
		return func(this, a_node, a_stream);
	}
}
