#pragma once

#include "RE/S/StaggerEffect.h"

namespace RE
{
	class DisarmEffect :
		public StaggerEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_DisarmEffect;
		inline static constexpr auto VTABLE = VTABLE_DisarmEffect;

		// override (ActiveEffect)
		virtual void Update(float a_delta) override;  // 04
		virtual ~DisarmEffect();                      // 13
		virtual void Start() override;                // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(DisarmEffect) == 0x90);
}
