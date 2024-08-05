#pragma once

#include "RE/A/ActiveEffect.h"

namespace RE
{
	class StaggerEffect :
		public ActiveEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_StaggerEffect;
		inline static constexpr auto VTABLE = VTABLE_StaggerEffect;

		// override (ActiveEffect)
		virtual ~StaggerEffect();       // 13
		virtual void Start() override;  // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(StaggerEffect) == 0x90);
}
