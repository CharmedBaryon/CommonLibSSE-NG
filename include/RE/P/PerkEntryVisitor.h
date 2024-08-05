#pragma once

#include "RE/B/BSContainer.h"

namespace RE
{
	class BGSPerkEntry;

	class PerkEntryVisitor
	{
	public:
		inline static constexpr auto RTTI = RTTI_PerkEntryVisitor;
		inline static constexpr auto VTABLE = VTABLE_PerkEntryVisitor;

		virtual BSContainer::ForEachResult Visit(BGSPerkEntry* a_perkEntry) = 0;  // 00
	private:
		KEEP_FOR_RE()
	};
}
