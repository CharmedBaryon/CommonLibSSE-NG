#pragma once

#include "RE/B/BSTArray.h"
#include "RE/C/CombatAcquireItem.h"
#include "RE/C/CombatBehavior.h"
#include "RE/C/CombatPath.h"

namespace RE
{
	class CombatBehaviorFindWeapon : public CombatBehaviorAction
	{
	public:
		struct ObjectData
		{
			CombatAcquireItem weapon;  // 00
			CombatAcquireItem ammo;    // 18
			float             score;   // 30
			uint32_t          pad34;   // 34
		};
		static_assert(sizeof(ObjectData) == 0x38);

		void Enter();
		void Update();

		// members
		BSTArray<ObjectData>  objects;  // 00
		NiPointer<CombatPath> path;     // 18
	};
	static_assert(sizeof(CombatBehaviorFindWeapon) == 0x20);
}
