#pragma once

#include "RE/A/ActiveEffect.h"

namespace RE
{
	class CloakEffect :
		public ActiveEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_CloakEffect;
		inline static constexpr auto VTABLE = VTABLE_CloakEffect;

		// override (ActiveEffect)
		virtual void Update(float a_delta) override;  // 04
		virtual ~CloakEffect();                       // 13

		// members
		std::uint64_t nextTargetCheck;  // 90
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CloakEffect) == 0x98);
}
