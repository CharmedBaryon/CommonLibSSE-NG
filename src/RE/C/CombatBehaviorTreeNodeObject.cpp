#include "RE/C/CombatBehaviorTreeNodeObject.h"

#include "RE/C/CombatBehaviorChildSelector.h"
#include "RE/C/CombatBehaviorContextAcquireWeapon.h"
#include "RE/C/CombatBehaviorContextCloseMovement.h"
#include "RE/C/CombatBehaviorContextMagic.h"
#include "RE/C/CombatBehaviorContextMelee.h"
#include "RE/C/CombatBehaviorEquipContext.h"
#include "RE/C/CombatBehaviorFallbackSelector.h"
#include "RE/C/CombatBehaviorParallel.h"
#include "RE/C/CombatBehaviorRepeat.h"
#include "RE/C/CombatBehaviorTreeCreateContextNode.h"

namespace RE
{
	template class CombatBehaviorTreeCreateContextNode<CombatBehaviorContextMelee>;
	template class CombatBehaviorTreeCreateContextNode<CombatBehaviorEquipContext>;

	template class CombatBehaviorChildSelector<ValueChildSelector>;
	static_assert(sizeof(CombatBehaviorChildSelector<ValueChildSelector>) == 0x4);
	static_assert(sizeof(CombatBehaviorTreeNodeObject<CombatBehaviorChildSelector<ValueChildSelector>>) == 0x28);

	template class CombatBehaviorChildSelector<RandomValueChildSelector>;
	static_assert(sizeof(CombatBehaviorChildSelector<RandomValueChildSelector>) == 0x8);
	static_assert(sizeof(CombatBehaviorTreeNodeObject<CombatBehaviorChildSelector<RandomValueChildSelector>>) == 0x28);

	template class CombatBehaviorChildSelector<ConditionalChildSelector>;
	static_assert(sizeof(CombatBehaviorChildSelector<ConditionalChildSelector>) == 0x4);
	static_assert(sizeof(CombatBehaviorTreeNodeObject<CombatBehaviorChildSelector<ConditionalChildSelector>>) == 0x28);

	template class CombatBehaviorFallbackSelector<NextChildSelector>;
	static_assert(sizeof(CombatBehaviorFallbackSelector<NextChildSelector>) == 0x8);
	static_assert(sizeof(CombatBehaviorTreeNodeObject<CombatBehaviorFallbackSelector<NextChildSelector>>) == 0x28);

	template class CombatBehaviorFallbackSelector<WeightedRandomChildSelector>;
	static_assert(sizeof(CombatBehaviorFallbackSelector<WeightedRandomChildSelector>) == 0xC);
	static_assert(sizeof(CombatBehaviorTreeNodeObject<CombatBehaviorFallbackSelector<WeightedRandomChildSelector>>) == 0x28);
}
