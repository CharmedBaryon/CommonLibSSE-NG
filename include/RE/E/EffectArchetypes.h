#pragma once

#include "RE/A/ActorValues.h"
#include "RE/F/FormTypes.h"

namespace RE
{
	struct EffectArchetypes
	{
		enum class ArchetypeID
		{
			kNone = static_cast<std::underlying_type_t<ArchetypeID>>(-1),
			kValueModifier = 0,
			kScript = 1,
			kDispel = 2,
			kCureDisease = 3,
			kAbsorb = 4,
			kDualValueModifier = 5,
			kCalm = 6,
			kDemoralize = 7,
			kFrenzy = 8,
			kDisarm = 9,
			kCommandSummoned = 10,
			kInvisibility = 11,
			kLight = 12,
			kDarkness = 13,
			kNightEye = 14,
			kLock = 15,
			kOpen = 16,
			kBoundWeapon = 17,
			kSummonCreature = 18,
			kDetectLife = 19,
			kTelekinesis = 20,
			kParalysis = 21,
			kReanimate = 22,
			kSoulTrap = 23,
			kTurnUndead = 24,
			kGuide = 25,
			kWerewolfFeed = 26,
			kCureParalysis = 27,
			kCureAddiction = 28,
			kCurePoison = 29,
			kConcussion = 30,
			kValueAndParts = 31,
			kAccumulateMagnitude = 32,
			kStagger = 33,
			kPeakValueModifier = 34,
			kCloak = 35,
			kWerewolf = 36,
			kSlowTime = 37,
			kRally = 38,
			kEnhanceWeapon = 39,
			kSpawnHazard = 40,
			kEtherealize = 41,
			kBanish = 42,
			kSpawnScriptedRef = 43,
			kDisguise = 44,
			kGrabActor = 45,
			kVampireLord = 46
		};

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kHiddenInEditor = 1 << 0,
			kIsActorValueUsed = 1 << 1,
			kIsFormUsed = 1 << 2,
			kUnk3 = 1 << 3,
			kAllowStacking = 1 << 4,
			kCannotMultiCast = 1 << 5,
			kCreatesRef = 1 << 6,
			kCustomSkillUse = 1 << 7,
			kRewardsSkillUseWithoutTarget = 1 << 8,
			kAddsEffectToCaster = 1 << 9
		};

		struct ArchetypeDef
		{
			const char*                        name;                // 00
			REX::EnumSet<Flags, std::uint32_t> flags;               // 08
			ActorValue                         fixedActorValue;     // 0C
			FormType                           associatedFormType;  // 10
			std::uint32_t                      pad14;               // 14
		};
		static_assert(sizeof(ArchetypeDef) == 0x18);

		static ArchetypeDef& GetArchetypeDef(ArchetypeID a_id)
		{
			static REL::Relocation<ArchetypeDef*> archetypes{ RELOCATION_ID(500623, 358289) };
			return archetypes.get()[std::to_underlying(a_id)];
		}

		static const char* GetArchetypeName(ArchetypeID a_id)
		{
			return GetArchetypeDef(a_id).name;
		}

		static FormType GetAssociatedFormType(ArchetypeID a_id)
		{
			return GetArchetypeDef(a_id).associatedFormType;
		}

		static ActorValue GetFixedActorValue(ArchetypeID a_id)
		{
			return GetArchetypeDef(a_id).fixedActorValue;
		}

		static bool IsFlagSet(ArchetypeID a_id, Flags a_flag)
		{
			return GetArchetypeDef(a_id).flags.all(a_flag);
		}
	};
	using EffectArchetype = EffectArchetypes::ArchetypeID;
}

namespace std
{
	[[nodiscard]] inline std::string to_string(RE::EffectArchetype a_archetype)
	{
		return RE::EffectArchetypes::GetArchetypeName(a_archetype);
	}
}

#ifdef FMT_VERSION
namespace fmt
{
	template <>
	struct formatter<RE::EffectArchetype> : formatter<std::string_view>
	{
		template <class FormatContext>
		auto format(const RE::EffectArchetype& a_archetype, FormatContext& a_ctx) const
		{
			return fmt::format_to(a_ctx.out(), "{}", RE::EffectArchetypes::GetArchetypeName(a_archetype));
		}
	};
}
#endif

#ifdef __cpp_lib_format
namespace std
{
	template <class CharT>
	struct formatter<RE::EffectArchetype, CharT> : std::formatter<std::string_view, CharT>
	{
		template <class FormatContext>
		auto format(RE::EffectArchetype a_archetype, FormatContext& a_ctx) const
		{
			return formatter<std::string_view, CharT>::format(RE::EffectArchetypes::GetArchetypeName(a_archetype), a_ctx);
		}
	};
}
#endif
