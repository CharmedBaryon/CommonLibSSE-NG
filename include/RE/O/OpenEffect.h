#pragma once

#include "RE/A/ActiveEffect.h"

namespace RE
{
	class OpenEffect :
		public ActiveEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_OpenEffect;
		inline static constexpr auto VTABLE = VTABLE_OpenEffect;

		// override (ActiveEffect)
		virtual ~OpenEffect();          // 13
		virtual void Start() override;  // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(OpenEffect) == 0x90);
}
