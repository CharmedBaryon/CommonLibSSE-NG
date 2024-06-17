#pragma once

#include "RE/A/ActorValues.h"
#include "RE/V/ValueModifierEffect.h"

namespace RE
{
	class DualValueModifierEffect :
		public ValueModifierEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_DualValueModifierEffect;
		inline static constexpr auto VTABLE = VTABLE_DualValueModifierEffect;

		// override (ActiveEffect)
		virtual bool IsCausingHealthDamage() override;             // 06
		virtual void SaveGame(BGSSaveFormBuffer* a_buf) override;  // 08
		virtual void LoadGame(BGSLoadFormBuffer* a_buf) override;  // 09
		virtual ~DualValueModifierEffect();                        // 13

		// override (ValueModifierEffect)
		virtual void ModifyActorValue(Actor* a_actor, float a_value, ActorValue a_actorValue) override;  // 20

		// add
		virtual ActorValue GetAdditionalActorValue() const;  // 21
		virtual float      GetSecondaryAVWeight() const;     // 22

		// members
		ActorValue secondaryActorValue;  // 98
		float      secondaryAVWeight;    // 9C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(DualValueModifierEffect) == 0xA0);
}
