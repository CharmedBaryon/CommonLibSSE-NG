#pragma once

#include "RE/B/BSContainer.h"

namespace RE
{
	class ActiveEffect;

	struct ItemCard;
	struct MagicItemList;

	class MagicMenuAddActiveEffectVisitor
	{
	public:
		inline static constexpr auto RTTI = RTTI___MagicMenuAddActiveEffectVisitor;
		inline static constexpr auto VTABLE = VTABLE___MagicMenuAddActiveEffectVisitor;

		virtual ~MagicMenuAddActiveEffectVisitor() {};  // 00

		virtual BSContainer::ForEachResult Visit(ActiveEffect* a_effect);  // 01

		// members
		std::uint64_t  unk08;     // 08
		std::uint64_t  unk10;     // 10
		ItemCard*      itemCard;  // 18
		std::uint64_t  unk20;     // 20
		std::uint64_t  unk28;     // 28
		std::uint64_t  unk30;     // 30
		std::uint64_t  unk38;     // 38
		std::uint64_t  unk40;     // 40
		std::uint64_t  unk48;     // 48
		std::uint64_t  unk50;     // 50
		std::uint64_t  unk58;     // 58
		std::uint64_t  unk60;     // 60
		std::uint64_t  unk68;     // 68
		std::uint64_t  unk70;     // 70
		std::uint64_t  unk78;     // 78
		MagicItemList* itemList;  // 80
	};
	static_assert(sizeof(MagicMenuAddActiveEffectVisitor) == 0x88);
}
