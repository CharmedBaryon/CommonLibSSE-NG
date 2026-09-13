#include "RE/C/CombatPath.h"

namespace RE
{
	void CombatPath::SetAccelerationDecelerationMult(float accelerationMult, float DecelerationMult)
	{
		using func_t = decltype(&CombatPath::SetAccelerationDecelerationMult);
		static REL::Relocation<func_t> func{ RELOCATION_ID(49022, 0) };
		return func(this, accelerationMult, DecelerationMult);
	}

	void CombatPath::Start()
	{
		using func_t = decltype(&CombatPath::Start);
		static REL::Relocation<func_t> func{ RELOCATION_ID(49013, 0) };
		return func(this);
	}

	void CombatPath::Update()
	{
		using func_t = decltype(&CombatPath::Start);
		static REL::Relocation<func_t> func{ RELOCATION_ID(49011, 0) };
		return func(this);
	}
}
