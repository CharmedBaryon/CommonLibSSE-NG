#pragma once

#include "RE/A/Actor.h"
#include "RE/B/BSContainer.h"

namespace RE
{
	class SpellItem;

	struct MagicItemList;

	class MagicMenuAddSpellVisitor : public Actor::ForEachSpellVisitor
	{
	public:
		inline static constexpr auto RTTI = RTTI___MagicMenuAddSpellVisitor;
		inline static constexpr auto VTABLE = VTABLE___MagicMenuAddSpellVisitor;

		virtual ~MagicMenuAddSpellVisitor(){};  // 00

		// override (Actor::ForEachSpellVisitor)
		virtual BSContainer::ForEachResult Visit(SpellItem* a_spell) override;  // 01

		// members
		MagicItemList* itemList;  // 08
		std::uint64_t  unk10;     // 10
	};
	static_assert(sizeof(MagicMenuAddSpellVisitor) == 0x18);
}
