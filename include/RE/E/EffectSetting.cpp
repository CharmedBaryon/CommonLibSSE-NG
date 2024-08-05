#pragma once

#include "RE/E/EffectSetting.h"
#include "RE/B/BSFixedString.h"

namespace RE
{
	BSFixedString EffectSetting::GetArchetypeAsString()
	{
		auto archetype = BSFixedString();

		switch (data.archetype) {
		case Archetype::kValueModifier:
			archetype = "ValueMod";
			break;
		case Archetype::kScript:
			archetype = "Script";
			break;
		case Archetype::kDispel:
			archetype = "Dispel";
			break;
		case Archetype::kCureDisease:
			archetype = "CureDisease";
			break;
		case Archetype::kAbsorb:
			archetype = "Absorb";
			break;
		case Archetype::kDualValueModifier:
			archetype = "DualValueMod";
			break;
		case Archetype::kCalm:
			archetype = "Calm";
			break;
		case Archetype::kDemoralize:
			archetype = "Demoralize";
			break;
		case Archetype::kFrenzy:
			archetype = "Frenzy";
			break;
		case Archetype::kDisarm:
			archetype = "Disarm";
			break;
		case Archetype::kCommandSummoned:
			archetype = "CommandSummoned";
			break;
		case Archetype::kInvisibility:
			archetype = "Invisibility";
			break;
		case Archetype::kLight:
			archetype = "Light";
			break;
		case Archetype::kLock:
			archetype = "Lock";
			break;
		case Archetype::kOpen:
			archetype = "Open";
			break;
		case Archetype::kBoundWeapon:
			archetype = "BoundWeapon";
			break;
		case Archetype::kSummonCreature:
			archetype = "SummonCreature";
			break;
		case Archetype::kDetectLife:
			archetype = "DetectLife";
			break;
		case Archetype::kTelekinesis:
			archetype = "Telekinesis";
			break;
		case Archetype::kParalysis:
			archetype = "Paralysis";
			break;
		case Archetype::kReanimate:
			archetype = "Reanimate";
			break;
		case Archetype::kSoulTrap:
			archetype = "SoulTrap";
			break;
		case Archetype::kTurnUndead:
			archetype = "TurnUndead";
			break;
		case Archetype::kGuide:
			archetype = "Guide";
			break;
		case Archetype::kWerewolfFeed:
			archetype = "WerewolfFeed";
			break;
		case Archetype::kCureParalysis:
			archetype = "CureParalysis";
			break;
		case Archetype::kCureAddiction:
			archetype = "CureAddiction";
			break;
		case Archetype::kCurePoison:
			archetype = "CurePoison";
			break;
		case Archetype::kConcussion:
			archetype = "Concussion";
			break;
		case Archetype::kValueAndParts:
			archetype = "ValueAndParts";
			break;
		case Archetype::kAccumulateMagnitude:
			archetype = "AccumulateMagnitude";
			break;
		case Archetype::kStagger:
			archetype = "Stagger";
			break;
		case Archetype::kPeakValueModifier:
			archetype = "PeakValueMod";
			break;
		case Archetype::kCloak:
			archetype = "Cloak";
			break;
		case Archetype::kWerewolf:
			archetype = "Werewolf";
			break;
		case Archetype::kSlowTime:
			archetype = "SlowTime";
			break;
		case Archetype::kRally:
			archetype = "Rally";
			break;
		case Archetype::kEnhanceWeapon:
			archetype = "EnhanceWeapon";
			break;
		case Archetype::kSpawnHazard:
			archetype = "SpawnHazard";
			break;
		case Archetype::kEtherealize:
			archetype = "Etherealize";
			break;
		case Archetype::kBanish:
			archetype = "Banish";
			break;
		case Archetype::kDisguise:
			archetype = "Disguise";
			break;
		case Archetype::kGrabActor:
			archetype = "GrabActor";
			break;
		case Archetype::kVampireLord:
			archetype = "VampireLord";
			break;
		default:
			break;
		}

		return archetype;
	}
}
