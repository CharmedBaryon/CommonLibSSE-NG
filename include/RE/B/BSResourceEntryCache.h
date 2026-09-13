#pragma once

#include "RE/B/BSAtomic.h"

namespace RE
{
	namespace BSResource
	{
		template <class T_Type, class T_EntryDBTraitsCArgs>
		class Entry;

		struct DAP
		{
		public:
		};
		static_assert(std::is_empty_v<DAP>);

		template <class T_Type, class T_EntryDBTraitsCArgs, class T_DAP, std::uint32_t T_SIZE>
		class EntryCacheTraits
		{
		public:
			using U_Entry = Entry<T_Type, T_EntryDBTraitsCArgs>;
		};
		static_assert(std::is_empty_v<EntryCacheTraits<void, void, void, 0>>);

		template <class T_EntryCacheTraits>
		class REntryCache
		{
		public:
			using U_EntryCacheTraits = T_EntryCacheTraits;

			// members
			T_EntryCacheTraits::U_Entry** table;           // 00
			std::uint32_t                 tableSize;       // 08
			std::uint32_t                 tombstoneCount;  // 10
			std::uint32_t                 active;          // 14
			std::uint32_t                 maxActive;       // 18
			std::uint32_t                 misses;          // 1C
			BSTAtomicValue<std::uint32_t> ctrl;            // 20
		};
	}
}
