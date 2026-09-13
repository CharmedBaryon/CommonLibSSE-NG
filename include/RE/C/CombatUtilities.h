#pragma once

#include "RE/A/ActorLOSLocation.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class TESObjectREFR;

	struct CombatUtilities
	{
		static RE::NiPoint3 GetAngleToProjectedTarget(RE::NiPoint3 a_origin, RE::TESObjectREFR* a_target, float a_speed, float a_gravity, RE::ACTOR_LOS_LOCATION a_location)
		{
			using func_t = decltype(&GetAngleToProjectedTarget);
			static REL::Relocation<func_t> func{ RELOCATION_ID(46022, 47286) };
			return func(a_origin, a_target, a_speed, a_gravity, a_location);
		}
	};
}
