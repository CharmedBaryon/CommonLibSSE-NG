#include "RE/B/BSCullingProcess.h"

namespace RE
{
	BSCullingProcess::CullingContext::CullingContext()
	{
		using func_t = CullingContext* (*)(CullingContext*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(100211, 106919) };
		func(this);
	}

	bool BSCullingProcess::AddShared(NiAVObject* a_object)
	{
		using func_t = decltype(&BSCullingProcess::AddShared);
		static REL::Relocation<func_t> func{ RELOCATION_ID(74812, 76562) };
		return func(this, a_object);
	}

	void BSCullingProcess::Process(CullingContext& a_context)
	{
		using func_t = void (*)(CullingContext*, std::int32_t, std::int32_t);
		static REL::Relocation<func_t> func{ RELOCATION_ID(100213, 106921) };
		return func(&a_context, 0, 0);
	}
}
