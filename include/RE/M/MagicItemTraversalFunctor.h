#pragma once

#include "RE/B/BSContainer.h"

namespace RE
{
	struct Effect;

	class MagicItemTraversalFunctor
	{
	public:
		inline static constexpr auto RTTI = RTTI_MagicItemTraversalFunctor;
		inline static constexpr auto VTABLE = VTABLE_MagicItemTraversalFunctor;

		MagicItemTraversalFunctor() = default;
		virtual ~MagicItemTraversalFunctor() = default;  // 00

		// add
		virtual BSContainer::ForEachResult operator()(Effect* a_effect) = 0;

		TES_HEAP_REDEFINE_NEW();

		// members
		std::uint32_t index{ 0 };  // 08
		std::uint32_t pad0C{ 0 };  // 0C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(MagicItemTraversalFunctor) == 0x10);
}
