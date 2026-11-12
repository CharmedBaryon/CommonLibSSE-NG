#pragma once

#include "RE/B/BSTFreeList.h"

namespace RE
{
	class ScrapHeap;

	template <class T>
	class BSTMessageQueue
	{
	public:
		virtual ~BSTMessageQueue() = default;  // 00

		// add
		virtual bool Push(T* a_obj) = 0;     // 01 - Wait for lock, then push
		virtual bool TryPush(T* a_obj) = 0;  // 02 - Try for lock, return false if taken, else push
		virtual bool Pop(T* a_obj) = 0;      // 03 - Wait for lock, then remove
		virtual bool TryPop(T* a_obj) = 0;   // 04 - Try for lock, return false if taken, else remove
	};

	static_assert(sizeof(BSTMessageQueue<void*>) == 0x8);

	template <class T>
	class BSTCommonMessageQueue : public BSTMessageQueue<T>
	{
	public:
		~BSTCommonMessageQueue() override = default;  // 00

		class LockGuard
		{
		public:
			explicit LockGuard(const BSTCommonMessageQueue& a_queue) :
				lock(a_queue.lock)
			{
				for (std::uint32_t expected = 0; !lock.compare_exchange_weak(expected, 1); expected = 0) {
					_mm_pause();
				}
			}
			~LockGuard() { lock.store(0); }

			LockGuard(const LockGuard&) = delete;
			LockGuard& operator=(const LockGuard&) = delete;

		private:
			std::atomic<std::uint32_t>& lock;
		};

		template <class Queue>
		class LockedView
		{
			using range_type = decltype(std::declval<Queue&>().Range(std::declval<const LockGuard&>()));

		public:
			explicit LockedView(Queue& a_queue) :
				guard(a_queue), range(a_queue.Range(guard)) {}

			[[nodiscard]] auto begin(this LockedView& a_self) { return a_self.range.begin(); }
			[[nodiscard]] auto end(this LockedView& a_self) { return a_self.range.end(); }

		private:
			LockGuard  guard;
			range_type range;
		};

		template <class Self>
		[[nodiscard]] auto Locked(this Self& a_self)
		{
			return LockedView<Self>(a_self);
		}

		// override (BSTMessageQueue<T>)
		bool Push(T* a_obj) override
		{
			const LockGuard guard(*this);
			return PushInternal(a_obj);
		}

		bool TryPush(T* a_obj) override
		{
			std::uint32_t expected = 0;
			if (!lock.compare_exchange_strong(expected, 1)) {
				return false;
			}
			const stl::scope_exit unlock{ [&]() noexcept { lock.store(0); } };
			return PushInternal(a_obj);
		}

		bool Pop(T* a_obj) override
		{
			const LockGuard guard(*this);
			return PopInternal(a_obj);
		}

		bool TryPop(T* a_obj) override
		{
			std::uint32_t expected = 0;
			if (!lock.compare_exchange_strong(expected, 1)) {
				return false;
			}
			const stl::scope_exit unlock{ [&]() noexcept { lock.store(0); } };
			return PopInternal(a_obj);
		}

	protected:
		// add
		virtual bool PushInternal([[maybe_unused]] T* a_obj) { return false; };  // 05
		virtual bool PopInternal([[maybe_unused]] T* a_obj) { return false; };   // 06

	public:
		mutable std::atomic<std::uint32_t> lock{ 0 };  // 08
		std::uint32_t                      pad0C{};    // 0C
	};

	static_assert(sizeof(BSTCommonMessageQueue<void*>) == 0x10);

	template <class T>
	class BSTCommonScrapHeapMessageQueue : public BSTCommonMessageQueue<T>
	{
	public:
		// members
		ScrapHeap*    unk10;  // 10
		std::uint64_t unk18;  // 18
		std::uint64_t unk20;  // 20
	};

	static_assert(sizeof(BSTCommonScrapHeapMessageQueue<void*>) == 0x28);

	template <class T>
	class BSTCommonLLMessageQueue : public BSTCommonMessageQueue<T>
	{
	public:
		explicit BSTCommonLLMessageQueue(BSTFreeList<T>* a_backingList) :
			freeList(a_backingList) {}

		~BSTCommonLLMessageQueue() override
		{
			T scratch{};
			while (this->Pop(&scratch)) {}
		}

		using LockGuard = BSTCommonMessageQueue<T>::LockGuard;

		template <bool Const>
		class basic_iterator
		{
			using node_type = std::conditional_t<Const, const BSTFreeListElem<T>, BSTFreeListElem<T>>;

		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = std::conditional_t<Const, const T*, T*>;
			using reference = std::conditional_t<Const, const T&, T&>;

			basic_iterator() = default;
			explicit basic_iterator(node_type* a_node) :
				node(a_node) {}

			reference       operator*() const { return *reinterpret_cast<pointer>(node->elem); }
			pointer         operator->() const { return reinterpret_cast<pointer>(node->elem); }
			basic_iterator& operator++()
			{
				node = node->next;
				return *this;
			}
			basic_iterator operator++(int)
			{
				auto previous = *this;
				node = node->next;
				return previous;
			}
			friend bool operator==(const basic_iterator&, const basic_iterator&) = default;

		private:
			node_type* node{ nullptr };
		};

		// The guard is the proof that the queue is locked; reach this through Locked()
		template <class Self>
		[[nodiscard]] auto Range(this Self& a_self, const LockGuard&)
		{
			using iterator = basic_iterator<std::is_const_v<Self>>;
			return std::ranges::subrange(iterator{ a_self.head }, iterator{ nullptr });
		}

	protected:
		// override (BSTCommonMessageQueue<T>)
		bool PushInternal(T* a_obj) override
		{
			BSTFreeListElem<T>* node = nullptr;
			if (!freeList || !freeList->Allocate(node, *a_obj)) {
				return false;
			}
			if (!head) {
				tail = &head;
			}
			*tail = node;
			node->next = nullptr;
			tail = &node->next;
			return true;
		}

		bool PopInternal(T* a_out) override
		{
			BSTFreeListElem<T>* node = head;
			if (!node) {
				return false;
			}
			*a_out = *reinterpret_cast<T*>(node->elem);
			head = node->next;
			freeList->Free(node);
			return true;
		}

	private:
		BSTFreeList<T>*      freeList;         // 10
		BSTFreeListElem<T>*  head{ nullptr };  // 18
		BSTFreeListElem<T>** tail{ &head };    // 20
	};

	static_assert(sizeof(BSTCommonLLMessageQueue<void*>) == 0x28);

	template <class T, std::size_t SIZE>
	class BSTCommonStaticMessageQueue : public BSTCommonMessageQueue<T>
	{
		static_assert(SIZE > 0 && SIZE <= (std::numeric_limits<std::uint32_t>::max)());

	public:
		BSTCommonStaticMessageQueue() = default;
		// Note: The real destructor does not drain: entries still queued are never destroyed, their references leak.
		~BSTCommonStaticMessageQueue() override
		{
			T scratch{};
			while (this->Pop(&scratch)) {}
		}

		using LockGuard = BSTCommonMessageQueue<T>::LockGuard;

		template <class Self>
		[[nodiscard]] auto Range(this Self& a_self, const LockGuard&)
		{
			return std::views::iota(std::uint32_t{ 0 }, std::uint32_t{ a_self.numEntries }) |
			       std::views::transform([&a_self](std::uint32_t a_offset) -> auto& {
					   return a_self.Entries()[(a_self.popIdx + a_offset) % SIZE];
				   });
		}

		[[nodiscard]] std::uint32_t size() const
		{
			return numEntries;
		}

	protected:
		bool PushInternal(T* a_obj) override
		{
			if (numEntries >= SIZE) {
				return false;
			}
			std::construct_at(Entries() + pushIdx, *a_obj);
			pushIdx = (pushIdx + 1) % SIZE;
			++numEntries;
			return true;
		}

		bool PopInternal(T* a_out) override
		{
			if (numEntries == 0) {
				return false;
			}
			T* slot = Entries() + popIdx;
			*a_out = *slot;  // a_out must be a live T
			std::destroy_at(slot);
			popIdx = (popIdx + 1) % SIZE;
			--numEntries;
			return true;
		}

	private:
		template <class Self>
		auto* Entries(this Self& a_self) noexcept
		{
			return reinterpret_cast<std::conditional_t<std::is_const_v<Self>, const T, T>*>(a_self.queueBuffer);
		}

		T* Entries() noexcept { return reinterpret_cast<T*>(queueBuffer); }

		char          queueBuffer[sizeof(T) * SIZE]{};  // 10
		std::uint32_t numEntries{};                     // ??
		std::uint32_t pushIdx{};                        // ??
		std::uint32_t popIdx{};                         // ??
	};
}