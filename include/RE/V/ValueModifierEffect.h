#pragma once

#include "RE/A/ActiveEffect.h"
#include "RE/A/ActorValues.h"

namespace RE
{
	class ValueModifierEffect : public ActiveEffect
	{
	public:
		inline static constexpr auto RTTI = RTTI_ValueModifierEffect;
		inline static constexpr auto VTABLE = VTABLE_ValueModifierEffect;

		// override (ActiveEffect)
		void OnAdd(MagicTarget* a_target) override;             // 01
		void Update(float a_delta) override;                    // 04
		bool IsCausingHealthDamage() override;                  // 06
		bool GetAllowMultipleCastingSourceStacking() override;  // 11 - { return  1; };
		void ClearTargetImpl() override;                        // 12

		~ValueModifierEffect() override;  // 13

		void  Start() override;                                                   // 14
		void  Finish() override;                                                  // 15
		bool  CheckCustomSkillUseConditions() const override;                     // 17
		float GetCustomSkillUseMagnitudeMultiplier(float a_mult) const override;  // 18

		// add
		virtual void SetActorValue(ActorValue a_actorValue);                                    // 19 - { actorValue = a_actorValue; }
		virtual bool ShouldModifyOnStart();                                                     // 1A
		virtual void ModifyOnStart();                                                           // 1B
		virtual bool ShouldModifyOnUpdate() const;                                              // 1C
		virtual void ModifyOnUpdate(float a_delta);                                             // 1D
		virtual bool ShouldModifyOnFinish() const;                                              // 1E
		virtual void ModifyOnFinish(Actor* a_caster, Actor* a_target, float a_value);           // 1F
		virtual void ModifyActorValue(Actor* a_actor, float a_value, ActorValue a_actorValue);  // 20

		// members
		ActorValue actorValue;  // 90
		float      value;       // 94
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ValueModifierEffect) == 0x98);
}
