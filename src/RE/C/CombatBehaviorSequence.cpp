#include "RE/C/CombatBehaviorSequence.h"

#include "RE/C/CombatBehaviorThread.h"
#include "RE/C/CombatBehaviorTreeNode.h"
#include "RE/T/TLSData.h"

namespace RE
{
	void CombatBehaviorSequence::Enter()
	{
		using func_t = decltype(&CombatBehaviorSequence::Enter);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46148, 0) };
		return func(this);
	}

	void CombatBehaviorSequence::Update()
	{
		auto thread = GetStaticTLSData()->combatAIThread;
		++ind;
		if (thread->failState == RE::CombatBehaviorThread::FailState::kFailed || ind >= thread->currentNode->children.size())
			thread->Ascend();
		else
			thread->Descend(ind);
	}
}
