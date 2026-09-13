#include "RE/A/ActiveEffect.h"

#include "RE/A/Actor.h"
#include "RE/E/Effect.h"

namespace RE
{
	void ActiveEffect::Dispel(bool a_force)
	{
		using func_t = decltype(&ActiveEffect::Dispel);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33286, 34061) };
		return func(this, a_force);
	}

	EffectSetting* ActiveEffect::GetBaseObject() noexcept
	{
		return effect ? effect->baseEffect : nullptr;
	}

	const EffectSetting* ActiveEffect::GetBaseObject() const noexcept
	{
		return effect ? effect->baseEffect : nullptr;
	}

	NiPointer<Actor> ActiveEffect::GetCasterActor() const
	{
		return caster.get();
	}

	Actor* ActiveEffect::GetTargetActor()
	{
		if (target && target->MagicTargetIsActor()) {
			return reinterpret_cast<Actor*>(target);
		} else {
			return nullptr;
		}
	}

	const Actor* ActiveEffect::GetTargetActor() const
	{
		if (target && target->MagicTargetIsActor()) {
			return reinterpret_cast<const Actor*>(target);
		} else {
			return nullptr;
		}
	}

	float ActiveEffect::GetMagnitude() const
	{
		using func_t = decltype(&ActiveEffect::GetMagnitude);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33282, 34057) };
		return func(this);
	}
}
