#pragma once

#include "RE/V/ValueModifierEffect.h"

namespace RE
{
	class ParalysisEffect : public ValueModifierEffect
	{
	public:
		inline static constexpr auto RTTI = RTTI_ParalysisEffect;
		inline static constexpr auto VTABLE = VTABLE_ParalysisEffect;

		// override (ValueModifierEffect)
		void Update(float a_delta) override;  // 04

		~ParalysisEffect() override;  // 13

		void Start() override;   // 14
		void Finish() override;  // 15
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ParalysisEffect) == 0x98);
}
