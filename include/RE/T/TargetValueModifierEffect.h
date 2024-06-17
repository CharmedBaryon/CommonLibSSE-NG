#pragma once

#include "RE/V/ValueModifierEffect.h"

namespace RE
{
	class TargetValueModifierEffect : public ValueModifierEffect
	{
	public:
		inline static constexpr auto RTTI = RTTI_TargetValueModifierEffect;
		inline static constexpr auto VTABLE = VTABLE_TargetValueModifierEffect;

		// override (ValueModifierEffect)
		bool GetAllowMultipleCastingSourceStacking() override;  // 11 - return { 0; }

		~TargetValueModifierEffect() override;  // 13

		void Start() override;  // 14

		// add
		virtual float GetTargetValue() const = 0;  // 21
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TargetValueModifierEffect) == 0x98);
}
