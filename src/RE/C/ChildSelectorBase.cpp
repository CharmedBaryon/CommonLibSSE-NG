#include "RE/C/ChildSelectorBase.h"

namespace RE
{
	bool ChildSelectorBase::Validate(CombatBehaviorTreeNode*)
	{
		return true;
	}

	bool ChildSelectorBase::ValidateChildren(CombatBehaviorTreeNode* node, BSFixedString const& type)
	{
		using func_t = decltype(&ChildSelectorBase::ValidateChildren);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46151, 0) };
		return func(node, type);
	}

	uint32_t ChildSelectorBase::SelectChild(CombatBehaviorTreeNode*, uint32_t) const
	{
		return 0xFFFFFFFF;
	}
}
