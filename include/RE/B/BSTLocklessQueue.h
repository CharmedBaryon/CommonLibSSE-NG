#pragma once

namespace RE
{
	struct BSTLocklessQueue
	{
		template <class T, std::uint32_t SIZE, std::uint32_t UNKNOWN>
		class PtrMultiProdCons
		{
		public:
			T* Next()
			{
				auto frontOfQueue = start;
				if (frontOfQueue == end)
					return nullptr;

				// atomic acquire of front of queue
				while (frontOfQueue != REX::W32::InterlockedCompareExchange(&start, frontOfQueue + 1, frontOfQueue)) {
					frontOfQueue = start;
					if (frontOfQueue == end)
						return nullptr;
				}

				// loop around, such that given SIZE = 8, index 8 = 0, index 9 = 1, etc
				std::uint32_t slotIndex = frontOfQueue % SIZE;

				// return the slot
				T* next = data[slotIndex];
				data[slotIndex] = nullptr;

				for (std::uint32_t currentFetched = fetched; !data[currentFetched % SIZE]; currentFetched = fetched) {
					if (fetched == start)
						break;
					if (currentFetched != REX::W32::InterlockedCompareExchange(&fetched, currentFetched + 1, currentFetched))
						break;
				}

				return next;
			}

			void Add(T* a_element)
			{
				std::uint32_t i;
				for (i = allocated;; i = allocated) {
					while ((((i + 1) ^ fetched) % SIZE) == 0) {
						REX::W32::Sleep(0);
						i = allocated;
					}
					if (i == REX::W32::InterlockedCompareExchange(&allocated, i + 1, i))
						break;
				}
				data[i % SIZE] = a_element;
				for (std::uint32_t j = end; data[j % SIZE]; j = end) {
					if (end == allocated)
						break;
					if (j != REX::W32::InterlockedCompareExchange(&end, j + 1, j))
						break;
				}
			}

			// members
			T*                     data[SIZE];  // 00
			volatile std::uint32_t start;       // 08
			volatile std::uint32_t fetched;     // 0C
			volatile std::uint32_t end;         // 10
			volatile std::uint32_t allocated;   // 14
		};
		static_assert(sizeof(PtrMultiProdCons<void*, 1, 1>) == 0x18);

		template <class QueueContainer, class T, std::uint32_t SIZE, std::uint32_t UNKNOWN>
		struct ObjQueueBase
		{
			// functions
			// AllocAndProduce - Next(free), Add(queued)
			// AllocObject - Next(free)
			// Consume - Next(queued)
			// FreeObject - Add(free)
			// Produce - Add(queued)

			T              data[SIZE];  // 00
			QueueContainer queued;      // ??
			QueueContainer free;        // ??
		};

		template <class T, std::uint32_t SIZE, std::uint32_t UNKNOWN>
		class ObjMultiProdCons : public ObjQueueBase<PtrMultiProdCons<T, SIZE * 2, UNKNOWN>, T, SIZE, UNKNOWN>
		{};
	};
}
