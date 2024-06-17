#pragma once

#include "RE/A/ActiveEffect.h"

namespace RE
{
	class LockEffect :
		public ActiveEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_LockEffect;
		inline static constexpr auto VTABLE = VTABLE_LockEffect;

		// override (ActiveEffect)
		virtual ~LockEffect();          // 13
		virtual void Start() override;  // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(LockEffect) == 0x90);
}
