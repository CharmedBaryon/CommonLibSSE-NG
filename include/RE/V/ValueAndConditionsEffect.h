#pragma once

#include "RE/A/ActorValues.h"
#include "RE/V/ValueModifierEffect.h"

namespace RE
{
	class ValueAndConditionsEffect :
		public ValueModifierEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_ValueAndConditionsEffect;
		inline static constexpr auto VTABLE = VTABLE_ValueAndConditionsEffect;

		// override (ActiveEffect)
		virtual void SaveGame(BGSSaveFormBuffer* a_buf) override;  // 08
		virtual void LoadGame(BGSLoadFormBuffer* a_buf) override;  // 09
		virtual ~ValueAndConditionsEffect();                       // 13

		// override (ValueModifierEffect)
		virtual void ModifyActorValue(Actor* a_actor, float a_value, ActorValue a_actorValue) override;  // 20

		// members
		ActorValue actorValue;  // 98
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ValueAndConditionsEffect) == 0xA0);
}
