#pragma once

#include "RE/B/bhkContactListener.h"

namespace RE
{
	class bhkBackfaceContactListener : public bhkContactListener
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkBackfaceContactListener;
		inline static constexpr auto VTABLE = VTABLE_bhkBackfaceContactListener;

		~bhkBackfaceContactListener() override;  // 04
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(bhkBackfaceContactListener) == 0x8);
}
