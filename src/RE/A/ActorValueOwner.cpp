#include "RE/A/ActorValueOwner.h"
#include "RE/A/ActorValueList.h"

namespace RE
{
	float ActorValueOwner::GetArmorRatingSkillMultiplier(float a_skillLevel) const
	{
		using func_t = decltype(&ActorValueOwner::GetArmorRatingSkillMultiplier);
		static REL::Relocation<func_t> func(RELOCATION_ID(25858, 26424));
		return func(this, a_skillLevel);
	}

	float ActorValueOwner::GetClampedActorValue(ActorValue a_akValue) const
	{
		using func_t = decltype(&ActorValueOwner::GetClampedActorValue);
		static REL::Relocation<func_t> func{ RELOCATION_ID(26616, 27284) };
		return func(this, a_akValue);
	}

	void ActorValueOwner::DamageActorValue(ActorValue a_akValue, float a_value)
	{
		auto avi = ActorValueList::GetActorValueInfo(a_akValue);

		float damage = avi && avi->IsInverted() ? std::abs(a_value) : -std::abs(a_value);
		ModActorValue(ACTOR_VALUE_MODIFIER::kDamage, a_akValue, damage);
	}

	void ActorValueOwner::RestoreActorValue(ActorValue a_akValue, float a_value)
	{
		auto avi = ActorValueList::GetActorValueInfo(a_akValue);

		float damage = avi && avi->IsInverted() ? -std::abs(a_value) : std::abs(a_value);
		ModActorValue(ACTOR_VALUE_MODIFIER::kDamage, a_akValue, damage);
	}
}
