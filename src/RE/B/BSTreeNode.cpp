#include "RE/B/BSTreeNode.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void BSTreeNode::OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex)
	{
		REL::RelocateVirtual<decltype(&BSTreeNode::OnVisible)>(0x34, 0x35, this, a_process, a_alphaGroupIndex);
	}
#endif

	void BSTreeNode::ComputeTreeLODBlend(std::uintptr_t a_arg1, std::uintptr_t a_arg2, std::uintptr_t a_arg3)
	{
		using func_t = decltype(&BSTreeNode::ComputeTreeLODBlend);
		static REL::Relocation<func_t> func{ RELOCATION_ID(26509, 27110) };
		return func(this, a_arg1, a_arg2, a_arg3);
	}
}
