#include "RE/M/MagicItemDataCollector.h"
#include "RE/M/MagicItem.h"

namespace RE
{
	MagicItemDataCollector::MagicItemDataCollector(const MagicItem* a_magicItem) :
		MagicItemTraversalFunctor(),
		projectileEffectList(),
		costliestEffect(nullptr),
		maxCost(-1),
		pad34(0),
		largestAreaEffect(nullptr),
		highestArea(0.0f),
		flags(a_magicItem->Is(FormType::Ingredient) ? Flags::kOnlyFirstEffect : Flags::kNone),
		summonsExtraLargeCreature(false),
		pad49(0),
		pad4A(0),
		pad4C(0)
	{
		stl::emplace_vtable(this);
	}

	BSContainer::ForEachResult MagicItemDataCollector::operator()(Effect* a_effect)
	{
		using func_t = decltype(&MagicItemDataCollector::operator());
		static REL::Relocation<func_t> func{ RELOCATION_ID(33834, 34626) };
		return func(this, a_effect);
	}
}
