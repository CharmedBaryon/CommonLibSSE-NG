#include "RE/B/BSFadeNode.h"

using namespace REL;

namespace RE
{
	BSTreeNode* BSFadeNode::AsTreeNode()
	{
		return REL::RelocateVirtual<decltype(&BSFadeNode::AsTreeNode)>(0x3E, 0x3F, this);
	}

	BSLeafAnimNode* BSFadeNode::AsLeafAnimNode()
	{
		return REL::RelocateVirtual<decltype(&BSFadeNode::AsLeafAnimNode)>(0x3F, 0x40, this);
	}
}
