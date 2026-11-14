#pragma once

#include "RE/A/AITimeStamp.h"
#include "RE/A/AITimer.h"
#include "RE/B/BSTArray.h"
#include "RE/C/CombatBehaviorContext.h"
#include "RE/N/NiPoint3.h"
#include "RE/S/SetEventData.h"

namespace RE
{
	class BGSAttackData;
	class CombatMeleeAimController;

	class CombatBehaviorContextMelee : public CombatBehaviorContext
	{
	public:
		enum class ATTACK_TYPE : uint32_t
		{
			WeaponRight,
			Shield,
			WeaponLeft
		};

		class CombatAttackData
		{
		public:
			BGSAttackData* attackdata;      // 00
			NiPoint3       P1;              // 08
			NiPoint3       P2;              // 14
			float          P1_len;          // 20
			float          hitframe_time;   // 24
			AITimer        cooldown_timer;  // 28
		};
		static_assert(sizeof(CombatAttackData) == 0x30);

		void CalculateAnimationData();
		bool CheckAttack(CombatAttackData* attack);
		bool CheckAttackRange();
		void Enter();
		void FinishedAttack();
		void GatherAttackData();
		bool StartAttack();

		// members
		float                      reach;                 // 00
		ATTACK_TYPE                attack_type;           // 04
		AITimeStamp                finishedAttackTime;    // 08
		uint32_t                   equipment_set;         // 0C
		BSTArray<SetEventData>*    attackAnimationArray;  // 10
		BSTArray<CombatAttackData> combatattackdatas;     // 18
		float                      min_P1_len;            // 30
		float                      attack_time_mult;      // 34
		CombatMeleeAimController*  aim_controller;        // 38
	};
	static_assert(sizeof(CombatBehaviorContextMelee) == 0x40);
}
