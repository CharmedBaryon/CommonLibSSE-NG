#include "RE/C/CombatBehaviorContextAcquireWeapon.h"

namespace RE
{
	void CombatBehaviorContextAcquireWeapon::Enter()
	{
		using func_t = decltype(&CombatBehaviorContextAcquireWeapon::Enter);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46341, 0) };
		return func(this);
	}

	void CombatBehaviorContextAcquireWeapon::Exit()
	{
		using func_t = decltype(&CombatBehaviorContextAcquireWeapon::Exit);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46342, 0) };
		return func(this);
	}

	const CombatAcquireItem& CombatBehaviorContextAcquireWeapon::GetAcquireAmmo() const
	{
		return ammo;
	}

	const CombatAcquireItem& CombatBehaviorContextAcquireWeapon::GetAcquireWeapon() const
	{
		return weapon;
	}

	bool CombatBehaviorContextAcquireWeapon::HasAmmoTarget() const
	{
		using func_t = decltype(&CombatBehaviorContextAcquireWeapon::HasAmmoTarget);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46442, 0) };
		return func(this);
	}
}
