#include "RE/C/CombatBehaviorAcquireResource.h"

#include "RE/C/CombatBehaviorController.h"
#include "RE/C/CombatBehaviorThread.h"
#include "RE/C/CombatBehaviorTreeNode.h"
#include "RE/T/TLSData.h"

namespace RE
{
	CombatBehaviorAcquireResource::CombatBehaviorAcquireResource()
	{
		using func_t = CombatBehaviorAcquireResource*(CombatBehaviorAcquireResource*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46206, 0) };
		func(this);
	}

	CombatBehaviorAcquireResource::CombatBehaviorAcquireResource(const BSFixedString& name, uint32_t priority, FLAG flags)
	{
		using func_t = CombatBehaviorAcquireResource*(CombatBehaviorAcquireResource*, const BSFixedString& name, uint32_t priority, FLAG flags);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46207, 0) };
		func(this, name, priority, flags);
	}

	void CombatBehaviorAcquireResource::Abort()
	{
		using func_t = decltype(&CombatBehaviorAcquireResource::Abort);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46212, 0) };
		return func(this);
	}

	void CombatBehaviorAcquireResource::Enter()
	{
		using func_t = decltype(&CombatBehaviorAcquireResource::Abort);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46209, 0) };
		return func(this);
	}

	void CombatBehaviorAcquireResource::Exit()
	{
		using func_t = decltype(&CombatBehaviorAcquireResource::Abort);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46211, 0) };
		return func(this);
	}

	void CombatBehaviorAcquireResource::Update()
	{
		using func_t = decltype(&CombatBehaviorAcquireResource::Abort);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46210, 0) };
		return func(this);
	}
}
