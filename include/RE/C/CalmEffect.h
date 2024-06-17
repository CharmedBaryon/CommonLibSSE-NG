#pragma once

#include "RE/T/TargetValueModifierEffect.h"

namespace RE
{
	class CalmEffect : public TargetValueModifierEffect
	{
	public:
		inline static constexpr auto RTTI = RTTI_CalmEffect;
		inline static constexpr auto VTABLE = VTABLE_CalmEffect;

		// override (TargetValueModifierEffect)
		~CalmEffect() override;  // 13

		void  Start() override;                 // 14
		float GetTargetValue() const override;  // 21 - { return -1.0f; }
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CalmEffect) == 0x98);
}
