#include "RE/H/hkbBehaviorGraph.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void hkbBehaviorGraph::Unk_06(void)
	{
		REL::RelocateVirtual<decltype(&hkbBehaviorGraph::Unk_06)>(0x06, 0x06, this);
	}
#endif
}
