#pragma once

#include "RE/V/ValueModifierEffect.h"

namespace RE
{
	class NightEyeEffect :
		public ValueModifierEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_NightEyeEffect;
		inline static constexpr auto VTABLE = VTABLE_NightEyeEffect;

		// override (ActiveEffect)
		virtual void Update(float a_delta) override;  // 04
		virtual ~NightEyeEffect();                    // 13
		virtual void Start() override;                // 14
		virtual void Finish() override;               // 15
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(NightEyeEffect) == 0x98);
}
