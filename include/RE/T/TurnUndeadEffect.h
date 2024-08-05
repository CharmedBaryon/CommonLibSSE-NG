#pragma once

#include "RE/D/DemoralizeEffect.h"

namespace RE
{
	class TurnUndeadEffect :
		public DemoralizeEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_TurnUndeadEffect;
		inline static constexpr auto VTABLE = VTABLE_TurnUndeadEffect;

		// override (ActiveEffect)
		virtual ~TurnUndeadEffect();  // 13
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TurnUndeadEffect) == 0x98);
}
