#pragma once

#include "RE/G/GString.h"

namespace RE
{
	class GASStringManager;

	class GASStringBuiltinManager
	{
	public:
		// members
		std::uint64_t     unk000[157];    // 000
		GASStringManager* stringManager;  // 4E8
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GASStringBuiltinManager) == 0x4F0);
}
