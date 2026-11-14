#pragma once

#include "RE/C/CombatAcquireItem.h"
#include "RE/C/CombatBehaviorContext.h"

namespace RE
{
	class CombatBehaviorContextAcquireWeapon : public CombatBehaviorContext
	{
	public:
		void                     Enter();
		void                     Exit();
		const CombatAcquireItem& GetAcquireAmmo() const;
		const CombatAcquireItem& GetAcquireWeapon() const;
		bool                     HasAmmoTarget() const;

		// members
		CombatAcquireItem weapon;    // 00
		CombatAcquireItem ammo;      // 18
		uint64_t          field_30;  // 30
	};
	static_assert(sizeof(CombatBehaviorContextAcquireWeapon) == 0x38);
}
