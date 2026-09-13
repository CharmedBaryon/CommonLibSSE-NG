#include "RE/C/CombatBehaviorRepeat.h"

#include "RE/C/CombatBehaviorThread.h"
#include "RE/C/CombatBehaviorTreeNode.h"
#include "RE/T/TLSData.h"

namespace RE
{
	CombatBehaviorRepeat::CombatBehaviorRepeat() :
		retry_time(0), timer({ 0.001f, 0 })
	{
		flags.set(Flags::kSingle, Flags::kRetryOnFailed);
	}

	CombatBehaviorRepeat::CombatBehaviorRepeat(float interval) :
		retry_time(interval), timer({ 0, 0 })
	{
		flags.set(Flags::kSingle, Flags::kRetryOnFailed);
	}

	CombatBehaviorRepeat::CombatBehaviorRepeat(FLAGS flags) :
		flags(flags), retry_time(0), timer({ 0.001f, 0 })
	{}

	CombatBehaviorRepeat::CombatBehaviorRepeat(float interval, FLAGS flags) :
		flags(flags), retry_time(interval), timer({ 0, 0 })
	{}

	void RE::CombatBehaviorRepeat::Enter()
	{
		GetStaticTLSData()->combatAIThread->Descend();
	}

	void CombatBehaviorRepeat::Update()
	{
		using func_t = decltype(&CombatBehaviorRepeat::Update);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46184, 0) };
		return func(this);
	}
}
