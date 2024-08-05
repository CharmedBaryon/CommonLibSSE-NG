#pragma once

#include "RE/B/BGSPerkRankArray.h"

namespace RE
{
	struct PerkRankData;

	class PerkRankVisitor
	{
	public:
		inline static constexpr auto RTTI = RTTI_PerkRankVisitor;
		inline static constexpr auto VTABLE = VTABLE_PerkRankVisitor;

		virtual bool operator()(const PerkRankData* a_entry) = 0;  // 00
	private:
		KEEP_FOR_RE()
	};
}
