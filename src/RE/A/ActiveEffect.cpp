#include "RE/A/ActiveEffect.h"

#include "RE/A/Actor.h"
#include "RE/E/Effect.h"
#include "RE/F/FormTraits.h"

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

	// target points at the MagicTarget base, whose offset in Actor depends on the
	// runtime version, so no cast recovers the actor; the object's own override does.
	Actor* ActiveEffect::GetTargetActor()
	{
		const auto ref = target ? target->GetTargetStatsObject() : nullptr;
		return ref ? ref->As<Actor>() : nullptr;
	}

	const Actor* ActiveEffect::GetTargetActor() const
	{
		const auto ref = target ? target->GetTargetStatsObject() : nullptr;
		return ref ? ref->As<Actor>() : nullptr;
	}

	float ActiveEffect::GetMagnitude() const
	{
		using func_t = decltype(&ActiveEffect::GetMagnitude);
		static REL::Relocation<func_t> func{ RELOCATION_ID(33282, 34057) };
		return func(this);
	}
}
