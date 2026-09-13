#pragma once

#include "RE/H/hkArray.h"

namespace RE
{
	class hkpShape;

	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0)
	class bhkListShapeCinfo
	{
	public:
		~bhkListShapeCinfo();

		// members
		std::uint32_t            unk00;        // 00
		std::uint32_t            pad04;        // 04
		hkArray<const hkpShape*> shapes;       // 08
		hkArray<std::uint32_t>   filterInfos;  // 18
	};
}
