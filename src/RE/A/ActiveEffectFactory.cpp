#include "RE/A/ActiveEffectFactory.h"

namespace RE
{
	namespace ActiveEffectFactory
	{
		bool CheckCast(MagicCaster* a_caster, MagicItem* a_spell, Effect* a_effect, MagicSystem::CannotCastReason& a_reason)
		{
			using func_t = decltype(&ActiveEffectFactory::CheckCast);
			static REL::Relocation<func_t> func{ RELOCATION_ID(33716, 34500) };
			return func(a_caster, a_spell, a_effect, a_reason);
		}
	}
}
