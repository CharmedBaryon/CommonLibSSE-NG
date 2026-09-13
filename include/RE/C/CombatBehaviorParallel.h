#pragma once

#include "RE/B/BSTArray.h"
#include "RE/C/CombatBehavior.h"

namespace RE
{
	class CombatBehaviorParallel : public CombatBehaviorNode
	{
	public:
		enum class Flag : uint32_t
		{
			kNoAbortOnUpdate = 1 << 0,
			kCalledAbort = (uint32_t)1 << 31
		};
		using FLAGS = stl::enumeration<Flag, uint32_t>;

		CombatBehaviorParallel() = default;

		void Abort();
		void Enter();
		void Update();

		// members
		BSTArray<CombatBehaviorThread*> child_threads;  // 00 -- TODO: unique_ptr?
		FLAGS                           flags;          // 18
		uint32_t                        pad1C;          // 1C
	};
	static_assert(sizeof(CombatBehaviorParallel) == 0x20);
}
