#pragma once

#include "RE/B/BSString.h"

namespace RE
{
	class BGSSoundDescriptorForm;
	class MagicItem;

	namespace MagicSystem
	{
		enum class CannotCastReason
		{
			kOK = 0,
			kMagicka = 1,
			kPowerUsed = 2,
			kRangedUnderWater = 3,
			kMultipleCast = 4,
			kItemCharge = 5,
			kCastWhileShouting = 6,
			kShoutWhileCasting = 7,
			kShoutWhileRecovering = 8,
			kCustomReasonNoStart = 100,
		};

		enum class CastingSource
		{
			kLeftHand = 0,
			kRightHand = 1,
			kOther = 2,
			kInstant = 3
		};

		enum class CastingType
		{
			kConstantEffect = 0,
			kFireAndForget = 1,
			kConcentration = 2,
			kScroll = 3
		};

		enum class Delivery
		{
			kSelf = 0,
			kTouch = 1,
			kAimed = 2,
			kTargetActor = 3,
			kTargetLocation = 4,

			kTotal
		};

		enum class SoundID
		{
			kDrawSheatheLPM = 0,
			kCharge = 1,
			kReadyLoop = 2,
			kRelease = 3,
			kCastLoop = 4,
			kHit = 5
		};

		enum class SpellType
		{
			kSpell = 0,
			kDisease = 1,
			kPower = 2,
			kLesserPower = 3,
			kAbility = 4,
			kPoison = 5,
			kEnchantment = 6,

			kPotion = 7,
			kAlchemy = static_cast<std::underlying_type_t<SpellType>>(kPotion),

			kWortCraft = 8,
			kIngredient = static_cast<std::underlying_type_t<SpellType>>(kWortCraft),

			kLeveledSpell = 9,
			kAddiction = 10,
			kVoicePower = 11,
			kStaffEnchantment = 12,
			kScroll = 13
		};

		enum class WardState
		{
			kNone = 0,
			kAbsorb = 1,
			kBreak = 2,

			kTotal
		};

		const char*             GetCannotCastString(CannotCastReason a_reason);
		float                   GetMagicCasterTargetUpdateInterval();
		BGSSoundDescriptorForm* GetMagicFailureSound(SpellType a_type);
		void                    GetMagicItemDescription(BSString& a_out, MagicItem* a_magicItem, const char* a_beginTagFormat, const char* a_endTagFormat);
	}
}
