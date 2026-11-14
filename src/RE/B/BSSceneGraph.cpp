#include "RE/B/BSSceneGraph.h"

#include "REL/Relocation.h"

namespace RE
{
	BSSceneGraph* BSSceneGraph::GetWorldSceneGraph()
	{
		static REL::Relocation<BSSceneGraph**> worldSceneGraph{ RELOCATION_ID(528087, 415032) };
		return *worldSceneGraph;
	}

#ifdef SKYRIM_CROSS_VR
	float BSSceneGraph::GetFarDistance()
	{
		return REL::RelocateVirtual<decltype(&BSSceneGraph::GetFarDistance)>(0x3E, 0x3F, this);
	}

	float BSSceneGraph::GetNearDistance()
	{
		return REL::RelocateVirtual<decltype(&BSSceneGraph::GetNearDistance)>(0x3F, 0x40, this);
	}

	void BSSceneGraph::SetViewDistanceBasedOnFrameRate(float a_frameRate)
	{
		REL::RelocateVirtual<decltype(&BSSceneGraph::SetViewDistanceBasedOnFrameRate)>(0x40, 0x41, this, a_frameRate);
	}
#endif
}
