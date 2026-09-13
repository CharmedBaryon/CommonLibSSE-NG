#pragma once

#include "RE/H/hkpWorldCinfo.h"

namespace RE
{
	class bhkWorldCinfo : public hkpWorldCinfo
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkWorldCinfo;
		inline static constexpr auto VTABLE = VTABLE_bhkWorldCinfo;

		~bhkWorldCinfo() override;  // 00
	};
	static_assert(sizeof(bhkWorldCinfo) == 0x100);
}
