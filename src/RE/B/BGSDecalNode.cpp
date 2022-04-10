#include "RE/B/BGSDecalNode.h"

using namespace REL;

namespace RE
{
	std::uint8_t BGSDecalNode::Unk_3E()
	{
		return RelocateVirtual<decltype(&BGSDecalNode::Unk_3E)>(0x3E, 0x3F, this);
	}

	void BGSDecalNode::AttachDecal(BSTempEffect* a_decal, bool a_firstAvail)
	{
		RelocateVirtual<decltype(&BGSDecalNode::AttachDecal)>(0x3F, 0x40, this, a_decal, a_firstAvail);
	}
}
