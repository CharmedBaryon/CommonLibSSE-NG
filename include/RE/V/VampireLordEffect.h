#pragma once

#include "RE/A/ActiveEffect.h"

namespace RE
{
	class VampireLordEffect :
		public ActiveEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_VampireLordEffect;
		inline static constexpr auto VTABLE = VTABLE_VampireLordEffect;

		// override (ActiveEffect)
		virtual ~VampireLordEffect();    // 13
		virtual void Start() override;   // 14
		virtual void Finish() override;  // 15
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(VampireLordEffect) == 0x90);
}
