#pragma once

#include "RE/V/ValueModifierEffect.h"

namespace RE
{
	class AbsorbEffect : public ValueModifierEffect
	{
	public:
		inline static constexpr auto RTTI = RTTI_AbsorbEffect;
		inline static constexpr auto VTABLE = VTABLE_AbsorbEffect;

		// override (ValueModifierEffect)
		~AbsorbEffect() override;  // 13

		void ModifyOnStart() override;                                                  // 1B
		void ModifyOnUpdate(float a_delta) override;                                    // 1D
		void ModifyOnFinish(Actor* a_caster, Actor* a_target, float a_value) override;  // 1F
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(AbsorbEffect) == 0x98);
}
