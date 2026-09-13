#pragma once

#include "RE/B/BSTaskletGroupData.h"

namespace RE
{
	// Non-virtual handle populated by BSTaskletManager::CreateTaskGroup(BSTaskletGroup&);
	// never constructed/owned directly.
	class BSTaskletGroup
	{
	public:
		// members
		BSTaskletGroupData* data;  // 00
	};
	static_assert(sizeof(BSTaskletGroup) == 0x8);
}
