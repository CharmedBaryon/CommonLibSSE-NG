#include "RE/F/FindMaxMagnitudeVisitor.h"

namespace RE
{
	BSContainer::ForEachResult FindMaxMagnitudeVisitor::Accept(ActiveEffect* a_effect)
	{
		using func_t = decltype(&FindMaxMagnitudeVisitor::Accept);
		static REL::Relocation<func_t> func{ reinterpret_cast<std::uintptr_t*>(RELOCATION_ID(257550, 205805).address())[0x1] };  // AE address/ID untested
		return func(this, a_effect);
	}
}  // namespace RE
