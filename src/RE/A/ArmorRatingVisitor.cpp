#include "RE/A/ArmorRatingVisitor.h"

namespace RE
{
	bool ArmorRatingVisitor::HaveNotVisitedArmor(TESObjectARMO* a_armor)
	{
		using func_t = decltype(&ArmorRatingVisitor::HaveNotVisitedArmor);
		static REL::Relocation<func_t> func(RELOCATION_ID(39221, 40297));
		return func(this, a_armor);
	}

	void ArmorRatingVisitor::VisitArmor(TESObjectARMO* a_armor)
	{
		using func_t = decltype(&ArmorRatingVisitor::VisitArmor);
		static REL::Relocation<func_t> func(RELOCATION_ID(39217, 40293));
		return func(this, a_armor);
	}
}
