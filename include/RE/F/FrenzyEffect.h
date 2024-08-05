#pragma once

#include "RE/T/TargetValueModifierEffect.h"

namespace RE
{
	class FrenzyEffect : public TargetValueModifierEffect
	{
	public:
		inline static constexpr auto RTTI = RTTI_FrenzyEffect;
		inline static constexpr auto VTABLE = VTABLE_FrenzyEffect;

		// override (TargetValueModifierEffect)
		~FrenzyEffect() override;  // 13

		void  Start() override;                 // 14
		void  Finish() override;                // 15
		float GetTargetValue() const override;  // 21 - { return 3.0f; }
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(FrenzyEffect) == 0x98);
}
