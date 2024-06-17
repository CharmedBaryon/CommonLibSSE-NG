#pragma once

#include "RE/T/TargetValueModifierEffect.h"

namespace RE
{
	class RallyEffect :
		public TargetValueModifierEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_RallyEffect;
		inline static constexpr auto VTABLE = VTABLE_RallyEffect;

		// override (ActiveEffect)
		virtual ~RallyEffect();  // 13

		// override (TargetValueModifierEffect)
		virtual float GetTargetValue() const override;  // 21
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(RallyEffect) == 0x98);
}
