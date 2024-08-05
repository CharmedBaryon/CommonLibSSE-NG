#include "RE/C/CriticalHit.h"

namespace RE
{
	BSTEventSource<CriticalHit::Event>* CriticalHit::GetEventSource()
	{
		using func_t = decltype(&CriticalHit::GetEventSource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(37726, 38671) };
		return func();
	}
}
