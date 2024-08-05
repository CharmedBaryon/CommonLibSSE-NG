#pragma once

#include "RE/A/ActiveEffect.h"

namespace RE
{
	class EtherealizationEffect :
		public ActiveEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_EtherealizationEffect;
		inline static constexpr auto VTABLE = VTABLE_EtherealizationEffect;

		// override (ActiveEffect)
		virtual ~EtherealizationEffect();  // 13
		virtual void Start() override;     // 14
		virtual void Finish() override;    // 15
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(EtherealizationEffect) == 0x90);
}
