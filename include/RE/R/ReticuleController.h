#pragma once

#include "RE/B/BSTArray.h"
#include "RE/M/MagicSystem.h"

namespace RE
{
	struct ReticuleController
	{
	public:
		static ReticuleController& GetSingleton()
		{
			REL::Relocation<ReticuleController*> singleton{ RELOCATION_ID(508607, 380335) };
			return *singleton;
		}

		// members
		BSTSmallArray<MagicSystem::CastingSource> data;        // 00
		std::uint64_t                             nextUpdate;  // 18
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ReticuleController) == 0x20);
}
