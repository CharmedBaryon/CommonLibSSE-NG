#pragma once

#include "RE/A/AITimer.h"
#include "RE/C/CombatBehavior.h"

namespace RE
{
	class CombatBehaviorTreeNode;

	class CombatBehaviorRepeat : public CombatBehaviorNode
	{
	public:
		enum class Flags : uint32_t
		{
			kSingle = 1 << 0,
			kRetryOnFailed = 1 << 1
		};
		using FLAGS = stl::enumeration<Flags, uint32_t>;

		CombatBehaviorRepeat();
		CombatBehaviorRepeat(float interval);
		CombatBehaviorRepeat(FLAGS flags);
		CombatBehaviorRepeat(float interval, FLAGS flags);

		void Enter();
		void Update();

		// members
		FLAGS   flags;       // 00
		float   retry_time;  // 04
		AITimer timer;       // 08
	};
	static_assert(sizeof(CombatBehaviorRepeat) == 0x10);
}
