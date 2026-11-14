#pragma once

#include "RE/M/MagicItemTraversalFunctor.h"

namespace RE
{
	class MagicItemFindFunctor : public MagicItemTraversalFunctor
	{
	public:
		inline static constexpr auto RTTI = RTTI_MagicItemFindFunctor;
		inline static constexpr auto VTABLE = VTABLE_MagicItemFindFunctor;

		~MagicItemFindFunctor() override;  // 00

		// override (MagicItemTraversalFunctor)
		BSContainer::ForEachResult operator()(Effect* a_effect) override;  // 01

		// add
		virtual bool MatchCondition(Effect* a_effect) = 0;  // 02

		// members
		std::int32_t  indexCount;  // 10
		std::uint32_t pad14;       // 14
	};
	static_assert(sizeof(MagicItemFindFunctor) == 0x18);
}
