#pragma once

#include "RE/A/ActiveEffect.h"

namespace RE
{
	class WerewolfFeedEffect :
		public ActiveEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_WerewolfFeedEffect;
		inline static constexpr auto VTABLE = VTABLE_WerewolfFeedEffect;

		// override (ActiveEffect)
		virtual ~WerewolfFeedEffect();  // 13
		virtual void Start() override;  // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(WerewolfFeedEffect) == 0x90);
}
