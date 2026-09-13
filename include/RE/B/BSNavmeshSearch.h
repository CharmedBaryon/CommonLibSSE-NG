#pragma once

#include <cstdint>

namespace RE
{
	class BSNavmeshSearch
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSNavmeshSearch;
		inline static constexpr auto VTABLE = VTABLE_BSNavmeshSearch;

		virtual ~BSNavmeshSearch();
	};
}
