#pragma once

#include "RE/A/ActiveEffect.h"

namespace RE
{
	class ConcussionEffect :
		public ActiveEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_ConcussionEffect;
		inline static constexpr auto VTABLE = VTABLE_ConcussionEffect;

		// override (ActiveEffect)
		virtual ~ConcussionEffect();  // 13
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ConcussionEffect) == 0x90);
}
