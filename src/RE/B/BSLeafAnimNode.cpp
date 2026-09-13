#include "RE/B/BSLeafAnimNode.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void BSLeafAnimNode::OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex)
	{
		REL::RelocateVirtual<decltype(&BSLeafAnimNode::OnVisible)>(0x34, 0x34, this, a_process, a_alphaGroupIndex);
	}

	BSLeafAnimNode* BSLeafAnimNode::AsLeafAnimNode()
	{
		return REL::RelocateVirtual<decltype(&BSLeafAnimNode::AsLeafAnimNode)>(0x3F, 0x3F, this);
	}
#endif
}
