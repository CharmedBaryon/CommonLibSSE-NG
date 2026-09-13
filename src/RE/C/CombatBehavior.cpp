#include "RE/C/CombatBehavior.h"

#include "RE/C/CombatBehaviorThread.h"
#include "RE/C/CombatBehaviorTreeNode.h"
#include "RE/T/TLSData.h"

#include "RE/C/CombatBehaviorAccessors.h"

namespace RE
{
	void CombatBehavior::Abort()
	{
		CombatBehaviorAccessors::Finish();
	}

	bool CombatBehavior::CheckTargetChanged()
	{
		using func_t = decltype(&CombatBehavior::CheckTargetChanged);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46089, 0) };
		return func(this);
	}

	CombatBehaviorThread* CombatBehavior::CreateChildThread(uint32_t child_ind, bool isControlChild)
	{
		using func_t = decltype(&CombatBehavior::CreateChildThread);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46090, 0) };
		return func(this, child_ind, isControlChild);
	}

	void CombatBehavior::StartChildThread(CombatBehaviorThread* thread, uint32_t child_ind, bool isControlChild)
	{
		using func_t = decltype(&CombatBehavior::StartChildThread);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46091, 0) };
		return func(this, thread, child_ind, isControlChild);
	}

	void CombatBehavior::Update()
	{
		CombatBehaviorAccessors::Finish();
	}

	bool CombatBehaviorBranch::Validate(CombatBehaviorTreeNode* node)
	{
		using func_t = decltype(&CombatBehaviorBranch::Validate);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46093, 0) };
		return func(node);
	}

	bool CombatBehaviorNode::Validate(CombatBehaviorTreeNode* node)
	{
		using func_t = decltype(&CombatBehaviorNode::Validate);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46092, 0) };
		return func(node);
	}

	bool CombatBehaviorAction::Validate(CombatBehaviorTreeNode* node)
	{
		using func_t = decltype(&CombatBehaviorAction::Validate);
		static REL::Relocation<func_t> func{ RELOCATION_ID(529913, 0) };
		return func(node);
	}
}
