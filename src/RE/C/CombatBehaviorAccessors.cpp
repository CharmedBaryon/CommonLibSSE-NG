#include "RE/C/CombatBehaviorAccessors.h"

#include "RE/C/CombatBehaviorThread.h"
#include "RE/T/TLSData.h"

namespace RE
{
	void CombatBehaviorAccessors::Fail()
	{
		using func_t = decltype(Fail);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46417, 0) };
		return func();
	}

	void CombatBehaviorAccessors::Finish()
	{
		GetStaticTLSData()->combatAIThread->Ascend();
	}

	void CombatBehaviorAccessors::Finish(bool failed)
	{
		auto thread = GetStaticTLSData()->combatAIThread;
		thread->SetFailed(failed);
		thread->Ascend();
	}
}
