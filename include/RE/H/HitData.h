#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/F/FormTypes.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BGSAttackData;
	class InventoryEntryData;
	class MagicItem;
	class TESObjectWEAP;
	class VATSCommand;

	class HitData
	{
	public:
		enum class Flag
		{
			kBlocked = 1 << 0,
			kBlockWithWeapon = 1 << 1,
			kBlockCandidate = 1 << 2,
			kCritical = 1 << 3,
			kCriticalOnDeath = 1 << 4,
			kFatal = 1 << 5,
			kDismemberLimb = 1 << 6,
			kExplodeLimb = 1 << 7,
			kCrippleLimb = 1 << 8,
			kDisarm = 1 << 9,
			kDisableWeapon = 1 << 10,
			kSneakAttack = 1 << 11,
			kIgnoreCritical = 1 << 12,
			kPredictDamage = 1 << 13,
			//kPredictBaseDamage = 1 << 14,
			kBash = 1 << 14,
			kTimedBash = 1 << 15,
			kPowerAttack = 1 << 16,
			kMeleeAttack = 1 << 18,
			kRicochet = 1 << 19,
			kExplosion = 1 << 20
		};

		void Populate(Actor* a_aggressor, Actor* a_target, InventoryEntryData* a_weapon)
		{
			using func_t = decltype(&HitData::Populate);
			static REL::Relocation<func_t> func(RELOCATION_ID(42832, 44001));
			return func(this, a_aggressor, a_target, a_weapon);
		}

		// members
		NiPoint3                              hitPosition;             // 00
		NiPoint3                              hitDirection;            // 0C
		ActorHandle                           aggressor;               // 18
		ActorHandle                           target;                  // 1C
		ObjectRefHandle                       sourceRef;               // 20
		std::uint32_t                         pad24;                   // 24
		NiPointer<BGSAttackData>              attackData;              // 28
		TESObjectWEAP*                        weapon;                  // 30
		MagicItem*                            criticalEffect;          // 38
		SpellItem*                            attackDataSpell;         // 40
		VATSCommand*                          VATSCommand;             // 48
		float                                 totalDamage;             // 50
		float                                 physicalDamage;          // 54
		float                                 targetedLimbDamage;      // 58
		float                                 percentBlocked;          // 5C
		float                                 resistedPhysicalDamage;  // 60
		float                                 resistedTypedDamage;     // 64
		float                                 stagger;                 // 68
		float                                 sneakAttackBonus;        // 6C
		float                                 bonusHealthDamageMult;   // 70
		float                                 pushBack;                // 74
		float                                 reflectedDamage;         // 78
		float                                 criticalDamageMult;      // 7C
		stl::enumeration<Flag, std::uint32_t> flags;                   // 80
		std::uint32_t                         equipIndex;              // 84
		ActorValue                            skill;                   // 88
		std::uint32_t                         damageLimb;              // 8C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(HitData) == 0x90);
}
