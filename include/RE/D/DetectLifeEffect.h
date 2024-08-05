#pragma once

#include "RE/A/ActiveEffect.h"

namespace RE
{
	class DetectLifeEffect :
		public ActiveEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_DetectLifeEffect;
		inline static constexpr auto VTABLE = VTABLE_DetectLifeEffect;

		// override (ActiveEffect)
		virtual void Update(float a_delta) override;                    // 04
		virtual bool ShouldDispelOnDeath() const override;              // 10
		virtual bool GetAllowMultipleCastingSourceStacking() override;  // 11
		virtual ~DetectLifeEffect();                                    // 13
		virtual bool CheckCustomSkillUseConditions() const override;    // 17
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(DetectLifeEffect) == 0x90);
}
