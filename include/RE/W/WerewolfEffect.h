#pragma once

#include "RE/A/ActiveEffect.h"

namespace RE
{
	class WerewolfEffect :
		public ActiveEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_WerewolfEffect;
		inline static constexpr auto VTABLE = VTABLE_WerewolfEffect;

		// override (ActiveEffect)
		virtual ~WerewolfEffect();       // 13
		virtual void Start() override;   // 14
		virtual void Finish() override;  // 15
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(WerewolfEffect) == 0x90);
}
