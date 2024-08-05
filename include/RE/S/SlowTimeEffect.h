#pragma once

#include "RE/B/BSSoundHandle.h"
#include "RE/S/ScriptEffect.h"

namespace RE
{
	class SlowTimeEffect :
		public ScriptEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_SlowTimeEffect;
		inline static constexpr auto VTABLE = VTABLE_SlowTimeEffect;

		// override (ActiveEffect)
		virtual ~SlowTimeEffect();       // 13
		virtual void Start() override;   // 14
		virtual void Finish() override;  // 15

		// members
		BSSoundHandle activeSound;  // A0
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(SlowTimeEffect) == 0xB0);
}
