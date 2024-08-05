#pragma once

#include "RE/A/ActiveEffect.h"
#include "RE/E/EffectArchetypes.h"
#include "RE/M/MagicSystem.h"

namespace RE
{
	class CureEffect :
		public ActiveEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_CureEffect;
		inline static constexpr auto VTABLE = VTABLE_CureEffect;

		// override (ActiveEffect)
		virtual ~CureEffect();          // 13
		virtual void Start() override;  // 14

		// members
		MagicSystem::SpellType spellType;    // 90
		EffectArchetype        archetypeID;  // 94
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CureEffect) == 0x98);
}
