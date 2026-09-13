#include "RE/C/CombatBehaviorResource.h"

namespace RE
{
	CombatBehaviorResource::CombatBehaviorResource(CombatBehaviorController* controller, const BSFixedString& name)
	{
		using func_t = CombatBehaviorResource*(CombatBehaviorResource*, CombatBehaviorController * controller, const BSFixedString& name);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46198, 0) };
		func(this, controller, name);
	}

	bool CombatBehaviorResource::AcquireResource(CombatBehaviorThread* thread, uint32_t priority, bool can_suspend)
	{
		using func_t = decltype(&CombatBehaviorResource::AcquireResource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46200, 0) };
		return func(this, thread, priority, can_suspend);
	}

	void CombatBehaviorResource::ClearOwner(CombatBehaviorThread* thread)
	{
		using func_t = decltype(&CombatBehaviorResource::ClearOwner);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46203, 0) };
		return func(this, thread);
	}

	void CombatBehaviorResource::ForceAcquireResource(CombatBehaviorThread* new_owner)
	{
		using func_t = decltype(&CombatBehaviorResource::ForceAcquireResource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46202, 0) };
		return func(this, new_owner);
	}

	void CombatBehaviorResource::ReleaseResource(CombatBehaviorThread* thread)
	{
		using func_t = decltype(&CombatBehaviorResource::ReleaseResource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46201, 0) };
		return func(this, thread);
	}
}
