#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESDescription.h"
#include "RE/T/TESForm.h"
#include "RE/T/TESFullName.h"
#include "RE/T/TESIcon.h"

namespace RE
{
	class ActorValueOwner;
	class BGSSkillPerkTreeNode;

	class ActorValueInfo :
		public TESForm,         // 000
		public TESFullName,     // 020
		public TESDescription,  // 030
		public TESIcon          // 040
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActorValueInfo;
		inline static constexpr auto VTABLE = VTABLE_ActorValueInfo;
		inline static constexpr auto FORMTYPE = FormType::ActorValueInfo;

		using DynamicBaseValueFunctor = float (*)(ActorValueOwner*, uint32_t avIndex);

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		enum class ActorValueType : std::uint32_t
		{
			kAttribute,         // e.g. Health, HealRate
			kSkill,             // e.g. OneHanded, VampirePerks, WerewolfPerks
			kAITemperament,     // e.g. Aggression, Energy, Morality
			kDamageResistance,  // e.g. PoisonResist
			kLimbCondition,     // e.g. BrainCondition
			kStatus,            // e.g. DetectLifeRange, Invisibility, NightEye, Paralysis
			kMiscellaneous,     // e.g. ArmorPerks, BowSpeedBonus, Fame, [Skill]Mod, [Skill]SkillAdvance, Variable01, WardPower
		};

		enum class ActorValueFlag : std::uint32_t
		{
			// used for combat-related magic skills
			kHostileEffectsScaleWithDifficulty = 1 << 1,

			// affects kClampAsSpecialStat behavior
			kSpecialStatClampsAsNonZero = 1 << 2,

			// clamped value (ActorValueOwner::GetClampedActorValue) is in the range [0, 10]
			// or [1, 10]
			kClampAsSpecialStat = 1 << 3,

			// clamped value is in the range [0, 100]
			kClampAsSkill = 1 << 4,

			// the value can have "permanent," "temporary," and "damage" modifiers
			// (see RE::Modifiers, RE::ActorValueStorage, RE::Actor::healthModifiers, etc.)
			kCanHaveModifiers = 1 << 5,

			// if the base value is computed from the actor or race, then the computed
			// base value is the dynamic computation + the current value
			kBaseValueIsDynamicPlusCurrent = 1 << 6,

			// base value is computed per reference (`computeBaseFunc`), and the GetAVInfo
			// console command lists the "derived" value as "ignored"
			kBaseValueComputedFromActor = 1 << 7,

			// the AV is an enum.
			kEnumeration = 1 << 8,

			// damaging this AV increases the value, and restoring it decreases the value.
			// used for AVs where high = bad, e.g. MovementNoiseMult impairing sneak
			kInverted = 1 << 9,

			// base value is computed per reference (`computeBaseFunc`), and values cached
			// in the AI process (see other flags) are forcibly refreshed on race change or
			// savegame load
			kBaseValueComputedFromRace = 1 << 11,

			// Papyrus APIs refuse to alter this AV's value
			kCannotBeAlteredByScripts = 1 << 14,

			kBaseValueIsAlwaysZero = 1 << 15,

			// probably intended for multipliers, though some (e.g. WeaponSpeedMult) use the
			// kBaseValueIsAlwaysZero flag instead
			kBaseValueIsAlwaysOne = 1 << 16,

			// used for limb condition AVs
			kBaseValueIsAlwaysOneHundred = 1 << 17,

			// see RE::CachedValues::actorValueCache
			kAIProcessCachesCurrentValue = 1 << 18,

			// see RE::CachedValues::maxActorValueCache. non-numeric AVs like Confidence, in
			// particular, only cache their current value and not a maximum
			kAIProcessCachesMaxValue = 1 << 19,

			// the current value for the player cannot be decreased while ToggleGodMode
			// is active
			kProtectedByGodMode = 1 << 20,

			// when an effect's <MAG> token is substituted for the magnitude, the displayed
			// value is scaled by 100
			kDisplayedEffectMagnitudeTimesOneHundred = 1 << 21,
		};

		struct Skill  // AVSK
		{
			TES_HEAP_REDEFINE_NEW();

			// members
			float useMult;        // 00
			float offsetMult;     // 04
			float improveMult;    // 08
			float improveOffset;  // 0C
		};
		static_assert(sizeof(Skill) == 0x10);

		~ActorValueInfo() override;  // 00

		// override (TESForm)
		void ClearData() override;           // 05
		bool Load(TESFile* a_mod) override;  // 06
		void InitItemImpl() override;        // 13

		// override (TESIcon)
		[[nodiscard]] const char* GetDefaultPath() const override;  // 06 - { return "Textures\\"; }

		bool IsInverted() const { return flags.all(ActorValueFlag::kInverted); }

		// members
		const char*                                 enumName;                   // 050
		BSFixedString                               abbreviation;               // 058 - ANAM
		REX::EnumSet<ActorValueFlag, std::uint32_t> flags;                      // 060
		ActorValueType                              type;                       // 064
		DynamicBaseValueFunctor                     computeBaseFunc;            // 068 - used if appropriate flags are set
		std::uint32_t                               unk070;                     // 070
		std::uint32_t                               unk074;                     // 074
		std::uint32_t                               unk078;                     // 078
		std::uint32_t                               unk07C;                     // 07C
		std::uint32_t                               unk080;                     // 080
		std::uint32_t                               unk084;                     // 084
		std::uint32_t                               unk088;                     // 088
		std::uint32_t                               unk08C;                     // 08C
		std::uint32_t                               unk090;                     // 090
		std::uint32_t                               unk094;                     // 094
		std::uint32_t                               unk098;                     // 098
		std::uint32_t                               unk09C;                     // 09C
		std::uint32_t                               unk0A0;                     // 0A0
		std::uint32_t                               unk0A4;                     // 0A4
		std::uint32_t                               unk0A8;                     // 0A8
		std::uint32_t                               unk0AC;                     // 0AC
		std::uint64_t                               enumValueCount;             // 0B0
		const char*                                 enumValues[0xA];            // 0B8
		Skill*                                      skill;                      // 108 - AVSK
		std::uint32_t                               isNthAICachedCurrentValue;  // 110 - if appropriate AV flag is set, RE::CachedValues::actorValueCache[n] is this AV
		std::uint32_t                               isNthAICachedMaxValue;      // 114 - if appropriate AV flag is set, RE::CachedValues::maxActorValueCache[n] is this AV
		BGSSkillPerkTreeNode*                       perkTree;                   // 118
		std::uint32_t                               perkTreeWidth;              // 120
		std::uint32_t                               unk124;                     // 124 - CNAM
	};
	static_assert(sizeof(ActorValueInfo) == 0x128);
}
