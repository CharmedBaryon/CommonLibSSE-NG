#pragma once

#include "RE/B/BSAtomic.h"

namespace RE
{
	namespace BSResource
	{
		template <class T>
		class EntryQueue
		{
		public:
			// members
			BSNonReentrantSpinLock lock;  // 00
			T*                     head;  // 08
			T**                    tail;  // 10
		};
		static_assert(sizeof(EntryQueue<void>) == 0x18);

		template <class T, std::uint32_t SIZE>
		class EntryBucketQueue
		{
		public:
			// members
			EntryQueue<T>          buckets[SIZE];  // 00
			volatile std::uint32_t step;           // C0 - e.g. the load queue's bucket for a new entry is (step + priority) & 7
		};
		static_assert(sizeof(EntryBucketQueue<void, 8>) == 0xC8);
	}
}
