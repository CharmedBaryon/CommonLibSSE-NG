#pragma once

#include "RE/V/ValueModifierEffect.h"

namespace RE
{
	class AccumulatingValueModifierEffect :
		public ValueModifierEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_AccumulatingValueModifierEffect;
		inline static constexpr auto VTABLE = VTABLE_AccumulatingValueModifierEffect;

		// override (ActiveEffect)
		virtual void SaveGame(BGSSaveFormBuffer* a_buf) override;  // 08
		virtual void LoadGame(BGSLoadFormBuffer* a_buf) override;  // 09
		virtual ~AccumulatingValueModifierEffect();                // 13
		virtual void Start() override;                             // 14
		virtual void Finish() override;                            // 15

		// override (ValueModifierEffect)
		virtual bool ShouldModifyOnStart() override;                                            // 1A
		virtual bool ShouldModifyOnUpdate() const override;                                     // 1C
		virtual void ModifyOnUpdate(float a_delta) override;                                    // 1D
		virtual void ModifyOnFinish(Actor* a_caster, Actor* a_target, float a_value) override;  // 1F

		// members
		float accumulatedMagnitude;  // 98
		float maximumMagnitude;      // 9C
		float holdTimer;             // A0
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(AccumulatingValueModifierEffect) == 0xA8);
}
