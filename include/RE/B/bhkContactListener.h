#pragma once

#include "RE/H/hkpContactListener.h"

namespace RE
{
	class bhkContactListener : public hkpContactListener
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkContactListener;
		inline static constexpr auto VTABLE = VTABLE_bhkContactListener;

		~bhkContactListener() override;  // 04
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(bhkContactListener) == 0x8);
}
