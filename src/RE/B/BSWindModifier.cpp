#include "RE/B/BSWindModifier.h"

#include "RE/M/MemoryManager.h"

namespace RE
{
	BSWindModifier* BSWindModifier::Ctor()
	{
		using func_t = decltype(&BSWindModifier::Ctor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(74377, 76100) };
		return func(this);
	}

	BSWindModifier* BSWindModifier::Create(const BSFixedString& a_name, float a_strength)
	{
		auto modifier = malloc<BSWindModifier>();
		if (modifier) {
			modifier->Ctor();
			modifier->name = a_name;
			modifier->strength = a_strength;
		}
		return modifier;
	}
}
