#pragma once

#include "RE/V/ValueModifierEffect.h"

namespace RE
{
	class DarknessEffect :
		public ValueModifierEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_DarknessEffect;
		inline static constexpr auto VTABLE = VTABLE_DarknessEffect;

		// override (ActiveEffect)
		virtual ~DarknessEffect();       // 13
		virtual void Start() override;   // 14
		virtual void Finish() override;  // 15
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(DarknessEffect) == 0x98);
}
