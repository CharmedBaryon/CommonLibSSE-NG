#include "RE/A/AITimer.h"

namespace RE
{
	float AITimer::QTimer()
	{
		using func_t = decltype(&AITimer::QTimer);
		static REL::Relocation<func_t> func{ RELOCATION_ID(47089, 48253) };
		return func();
	}
}
