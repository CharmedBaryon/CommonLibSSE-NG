#pragma once

#include "RE/A/ActiveEffect.h"

namespace RE
{
	class DispelEffect :
		public ActiveEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_DispelEffect;
		inline static constexpr auto VTABLE = VTABLE_DispelEffect;

		// override (ActiveEffect)
		virtual ~DispelEffect();        // 13
		virtual void Start() override;  // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(DispelEffect) == 0x90);
}
