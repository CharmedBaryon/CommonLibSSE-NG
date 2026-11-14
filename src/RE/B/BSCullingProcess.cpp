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

#ifdef SKYRIM_CROSS_VR
	void BSCullingProcess::ClearCollectedGeometry()
	{
		if (REL::Module::IsVR()) {
			REL::RelocateVirtual<decltype(&BSCullingProcess::ClearCollectedGeometry)>(0x1A, 0x1A, this);
		}
		// SE/AE: no such function
	}

	bool BSCullingProcess::TestBaseVisibility1(BSMultiBound& a_bound)
	{
		return REL::RelocateVirtual<decltype(&BSCullingProcess::TestBaseVisibility1)>(0x1A, 0x1B, this, a_bound);
	}

	bool BSCullingProcess::TestBaseVisibility2(BSOcclusionPlane& a_bound)
	{
		return REL::RelocateVirtual<decltype(&BSCullingProcess::TestBaseVisibility2)>(0x1B, 0x1C, this, a_bound);
	}

	bool BSCullingProcess::TestBaseVisibility3(const NiBound& a_bound)
	{
		return REL::RelocateVirtual<decltype(&BSCullingProcess::TestBaseVisibility3)>(0x1C, 0x1D, this, a_bound);
	}
#endif
}
