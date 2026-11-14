#include "RE/H/hkpAddModifierUtil.h"
#include "RE/H/hkpContactPointEvent.h"
#include "RE/H/hkpResponseModifier.h"
#include "RE/H/hkpSimpleConstraintContactMgr.h"
#include "RE/H/hkpSimulationIsland.h"

namespace RE
{
	void hkpAddModifierUtil::SetInvMassScalingForContact(const hkpContactPointEvent& a_event, hkpRigidBody* a_body, const hkVector4& a_factor)
	{
		auto island = a_event.bodies[0]->simulationIsland;
		if (island->storageIndex == 0xFFFF) {
			island = a_event.bodies[1]->simulationIsland;
		}

		if (a_event.type == RE::hkpContactPointEvent::Type::kManifold) {
			const auto old_threadID = island->multiThreadCheck.threadId;
			const auto old_markCount = island->multiThreadCheck.markCount;
			const auto old_stackTrace = island->multiThreadCheck.stackTraceId;

			island->multiThreadCheck.markCount |= 0x8000;
			hkpResponseModifier::SetInvMassScalingForContact(a_event.contactMgr, a_body, *island, a_factor);

			island->multiThreadCheck.threadId = old_threadID;
			island->multiThreadCheck.stackTraceId = old_stackTrace;
			island->multiThreadCheck.markCount = old_markCount;
		} else {
			hkpResponseModifier::SetInvMassScalingForContact(a_event.contactMgr, a_body, *island, a_factor);
		}
	}
}
