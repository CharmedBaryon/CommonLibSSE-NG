#pragma once

#include "RE/M/MagicItemFindFunctor.h"

namespace RE
{
	class BGSKeyword;

	class MagicItemFindKeywordFunctor : public MagicItemFindFunctor
	{
	public:
		inline static constexpr auto RTTI = RTTI_MagicItemFindKeywordFunctor;
		inline static constexpr auto VTABLE = VTABLE_MagicItemFindKeywordFunctor;

		~MagicItemFindKeywordFunctor() override;  // 00

		// override (MagicItemFindFunctor)
		bool MatchCondition(Effect* a_effect) override;  // 02

		// members
		BGSKeyword* keyword;  // 18
	};
	static_assert(sizeof(MagicItemFindKeywordFunctor) == 0x20);
}
