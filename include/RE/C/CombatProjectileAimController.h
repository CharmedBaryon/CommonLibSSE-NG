#pragma once

#include "RE/A/AITimeStamp.h"
#include "RE/B/BSFixedString.h"
#include "RE/C/CombatAimController.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BGSProjectile;
	class NiAVObject;

	class CombatProjectileAimController : public CombatAimController
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatProjectileAimController;
		inline static constexpr auto VTABLE = VTABLE_CombatProjectileAimController;

		~CombatProjectileAimController() override;  // 00

		// override (CombatObject)
		std::uint32_t GetObjectType() override;  // 02

		// override (CombatAimController)
		bool                                         CanFireAtTarget(const NiPoint3* a_arg2, const NiPoint3* a_arg3) override;  // 05
		bool                                         CanFireNow() override;                                                     // 06
		bool                                         IsFacingTarget(float a_tolerance) override;                                // 07
		void                                         Update() override;                                                         // 08
		[[nodiscard]] CombatProjectileAimController* Clone() override;                                                          // 09
		void                                         OnWeaponTypeChanged() override;                                            // 0A

		// members
		BGSProjectile*        projectile;          // 48 - RTTI-checked cast from a form-ID lookup in LoadGame
		float                 projectileSpeed;     // 50 - launch speed, fed into the ballistic arc time-of-flight solver
		float                 blastRadius;         // 54 - friendly-fire safety radius, checked in IsClearToFire
		float                 heading;             // 58 - cached heading, from GetClampedTurnHeadingTowardLookAtTarget
		NiPoint3              unk5C;               // 5C - output buffer for GetClampedTurnHeadingTowardLookAtTarget
		NiPoint3              basePosition;        // 68 - read and subtracted from target position in UpdateAimSolution
		NiPoint3              idealAimPosition;    // 74 - barrel-offset-compensated aim-solution result position
		NiPoint3              aimOffset;           // 80 - (target actual pos - basePosition), set by UpdateAimSolution
		NiPoint3              unk8C;               // 8C - trajectory accumulator, reset and integrated in a loop
		float                 unk98;               // 98
		float                 unk9C;               // 9C
		float                 radiusMode;          // A0 - compared/multiplied against a fixed constant
		std::uint32_t         pad_A4;              // A4
		NiPointer<NiAVObject> weaponNode;          // A8 - cached muzzle/draw node, manually refcount-swapped in OnWeaponTypeChanged
		AITimeStamp           unkB0;               // B0
		NiPoint3              trackedAimPosition;  // B4 - cached result of GetClampedAimTrackingPosition
		AITimeStamp           lastTrackingUpdate;  // C0 - throttles GetClampedAimTrackingPosition to once per qtimer tick
		std::uint32_t         pad_C4;              // C4
		BSFixedString         weaponKeyword;       // C8 - cached weapon-type keyword, compared against a global singleton in OnWeaponTypeChanged
	};
	static_assert(sizeof(CombatProjectileAimController) == 0xD0);
}
