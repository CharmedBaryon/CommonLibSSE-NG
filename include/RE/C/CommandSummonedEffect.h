#pragma once

#include "RE/A/ActiveEffect.h"

namespace RE
{
	class CommandSummonedEffect :
		public ActiveEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_CommandSummonedEffect;
		inline static constexpr auto VTABLE = VTABLE_CommandSummonedEffect;

		// override (ActiveEffect)
		virtual ~CommandSummonedEffect();  // 13
		virtual void Start() override;     // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CommandSummonedEffect) == 0x90);
}
