#pragma once

#include "RE/B/BGSEntryPointFunction.h"

namespace RE
{
	class Actor;

	struct BGSEntryPoint
	{
		struct ENTRY_POINTS
		{
			enum ENTRY_POINT : std::uint32_t
			{
				kCalculateWeaponDamage = 0,
				kCalculateMyCriticalHitChance = 1,
				kCalculateMyCriticalHitDamage = 2,
				kCalculateMineExplodeChance = 3,
				kAdjustLimbDamage = 4,
				kAdjustBookSkillPoints = 5,
				kModRecoveredHealth = 6,
				kGetShouldAttack = 7,
				kModBuyPrices = 8,
				kAddLeveledListOnDeath = 9,
				kGetMaxCarryWeight = 10,
				kModAddictionChance = 11,
				kModAddictionDuration = 12,
				kModPositiveChemDuration = 13,
				kActivate = 14,
				kIgnoreRunningDuringDetection = 15,
				kIgnoreBrokenLock = 16,
				kModEnemyCriticalHitChance = 17,
				kModSneakAttackMult = 18,
				kModMaxPlaceableMines = 19,
				kModBowZoom = 20,
				kModRecoverArrowChance = 21,
				kModSkillUse = 22,
				kModTelekinesisDistance = 23,
				kModTelekinesisDamageMult = 24,
				kModTelekinesisDamage = 25,
				kModBashingDamage = 26,
				kModPowerAttackStamina = 27,
				kModPowerAttackDamage = 28,
				kModSpellMagnitude = 29,
				kModSpellDuration = 30,
				kModSecondaryValueWeight = 31,
				kModArmorWeight = 32,
				kModIncomingStagger = 33,
				kModTargetStagger = 34,
				kModAttackDamage = 35,
				kModIncomingDamage = 36,
				kModTargetDamageResistance = 37,
				kModSpellCost = 38,
				kModPercentBlocked = 39,
				kModShieldDeflectArrowChance = 40,
				kModIncomingSpellMagnitude = 41,
				kModIncomingSpellDuration = 42,
				kModPlayerIntimidation = 43,
				kModPlayerReputation = 44,
				kModFavorPoints = 45,
				kModBribeAmount = 46,
				kModDetectionLight = 47,
				kModDetectionMovement = 48,
				kModSoulGemRecharge = 49,
				kSetSweepAttack = 50,
				kApplyCombatHitSpell = 51,
				kApplyBashingSpell = 52,
				kApplyReanimateSpell = 53,
				kSetBooleanGraphVariable = 54,
				kModSpellCastingSoundEvent = 55,
				kModPickpocketChance = 56,
				kModDetectionSneakSkill = 57,
				kModFallingDamage = 58,
				kModLockpickSweetSpot = 59,
				kModSellPrices = 60,
				kCanPickpocketEquippedItem = 61,
				kModLockpickLevelAllowed = 62,
				kSetLockpickStartingArc = 63,
				kSetProgressionPicking = 64,
				kMakeLockpicksUnbreakable = 65,
				kModAlchemyEffectiveness = 66,
				kApplyWeaponSwingSpell = 67,
				kModCommandedActorLimit = 68,
				kApplySneakingSpell = 69,
				kModPlayerMagicSlowdown = 70,
				kModWardMagickaAbsorptionPct = 71,
				kModInitialIngredientEffectsLearned = 72,
				kPurifyAlchemyIngredients = 73,
				kFilterActivation = 74,
				kCanDualCastSpell = 75,
				kModTemperingHealth = 76,
				kModEnchantmentPower = 77,
				kModSoulPctCapturedToWeapon = 78,
				kModSoulGemEnchanting = 79,
				kModNumberAppliedEnchantmentsAllowed = 80,
				kSetActivateLabel = 81,
				kModShoutOK = 82,
				kModPoisonDoseCount = 83,
				kShouldApplyPlacedItem = 84,
				kModArmorRating = 85,
				kModLockpickingCrimeChance = 86,
				kModIngredientsHarvested = 87,
				kModSpellRange_TargetLoc = 88,
				kModPotionsCreated = 89,
				kModLockpickingKeyRewardChance = 90,
				kAllowMountActor = 91,

				kTotal
			};
		};
		using ENTRY_POINT = ENTRY_POINTS::ENTRY_POINT;

		struct EntryPointParameter
		{
		public:
			const char*   name;      // 00
			bool          nonActor;  // 08
			std::uint8_t  pad09;     // 09
			std::uint16_t pad0A;     // 0A
			std::uint32_t pad0C;     // 0C
		};
		static_assert(sizeof(EntryPointParameter) == 0x10);

		struct EntryPointParameters
		{
		public:
			std::uint32_t        count;  // 00
			std::uint32_t        pad04;  // 04
			EntryPointParameter* data;   // 08
		};
		static_assert(sizeof(EntryPointParameters) == 0x10);

		struct EntryPoint
		{
		public:
			const char*                                      name;          // 00
			EntryPointParameters                             parameters;    // 08
			BGSEntryPointFunction::ENTRY_POINT_FUNCTION_TYPE functionType;  // 18
			std::uint32_t                                    pad1C;         // 1C
		};
		static_assert(sizeof(EntryPoint) == 0x20);

		static EntryPoint* GetEntryPoint(ENTRY_POINT a_entryPoint)
		{
			if (a_entryPoint < ENTRY_POINT::kTotal) {
				REL::Relocation<EntryPoint*> entryPoints{ RELOCATION_ID(675707, 368994) };  //TODO: Verify SSE ID against VR
				return &entryPoints.get()[a_entryPoint];
			}

			return nullptr;
		}

		template <class... Args>
		static void HandleEntryPoint(ENTRY_POINT a_entryPoint, Actor* a_perkOwner, Args... a_args)
		{
			using func_t = decltype(&BGSEntryPoint::HandleEntryPoint<Args...>);
			static REL::Relocation<func_t> func{ RELOCATION_ID(23073, 23526) };
			func(a_entryPoint, a_perkOwner, a_args...);
		}
	};
}
