#pragma once

#include "RE/D/DemoralizeEffect.h"

namespace RE
{
	class BanishEffect :
		public DemoralizeEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_BanishEffect;
		inline static constexpr auto VTABLE = VTABLE_BanishEffect;

		// override (ActiveEffect)
		virtual ~BanishEffect();        // 13
		virtual void Start() override;  // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BanishEffect) == 0x98);
}
