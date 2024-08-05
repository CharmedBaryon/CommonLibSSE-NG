#pragma once

#include "RE/T/TargetValueModifierEffect.h"

namespace RE
{
	class DemoralizeEffect : public TargetValueModifierEffect
	{
	public:
		inline static constexpr auto RTTI = RTTI_DemoralizeEffect;
		inline static constexpr auto VTABLE = VTABLE_DemoralizeEffect;

		// override (TargetValueModifierEffect)
		~DemoralizeEffect() override;  // 13

		float GetTargetValue() const override;  // 21 - { return 0.0f; }
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(DemoralizeEffect) == 0x98);
}
