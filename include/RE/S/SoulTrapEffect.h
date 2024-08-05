#pragma once

#include "RE/A/ActiveEffect.h"

namespace RE
{
	class SoulTrapEffect :
		public ActiveEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_SoulTrapEffect;
		inline static constexpr auto VTABLE = VTABLE_SoulTrapEffect;

		// override (ActiveEffect)
		virtual void Update(float a_delta) override;  // 04
		virtual ~SoulTrapEffect();                    // 13
		virtual void Finish() override;               // 15
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(SoulTrapEffect) == 0x90);
}
