#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/I/ID.h"

namespace RE
{
	namespace BSResource
	{
		class Stream;

		template <class T_Type, class T_EntryDBTraitsCArgs>
		class Entry
		{
		public:
			using U_Type = T_Type;
			using U_EntryDBTraitsCArgs = T_EntryDBTraitsCArgs;

			union UserData
			{
				std::uint32_t         flags;
				T_EntryDBTraitsCArgs* traits;
			};
			static_assert(sizeof(UserData) == 0x8);

			// members
			ID                                   name;      // 00
			BSTAtomicValue<std::uint32_t>        ctrl;      // 0C
			UserData                             userData;  // 10
			Entry<T_Type, T_EntryDBTraitsCArgs>* next;      // 18
			BSTSmartPointer<Stream>              stream;    // 20
			T_Type                               data;      // 28
		};
	}
}
