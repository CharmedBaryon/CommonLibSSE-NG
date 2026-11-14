#pragma once

#include "RE/B/BSNavmeshInfoSearch.h"

namespace RE
{
	class BSPrecomputedNavmeshInfoSearch : public BSNavmeshInfoSearch
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPrecomputedNavmeshInfoSearch;
		inline static constexpr auto VTABLE = VTABLE_BSPrecomputedNavmeshInfoSearch;

		~BSPrecomputedNavmeshInfoSearch() override;  // 00

		bool IsAtGoal(BSNavmeshInfoSearchNode* a_node) override;  // 02
	};
	STATIC_ASSERT_SIZE(BSPrecomputedNavmeshInfoSearch, 0x238);
}
