#pragma once

#include "RE/A/AITimer.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/C/CombatObject.h"

namespace RE
{
	class CombatPath : public CombatObject
	{
	public:
		enum class STATE : uint32_t
		{
			kNone,
			kStarted,
			kMoving,
			kWaitingRepath,
			kStopped,
			kUnreachable,
			kUnk6
		};

		void SetAccelerationDecelerationMult(float accelerationMult, float DecelerationMult);
		void Start();
		void Update();

		// members
		ActorHandle actorhandle;
		STATE       state;
		STATE       last_state;
		uint32_t    speed;
		AITimer     PathRetryTimer;
		AITimer     timer;
		void*       speedcontroller;  // TODO: add
	};
	static_assert(sizeof(CombatPath) == 0x38);
}
