#pragma once

namespace RE
{
	template <class T>
	struct BSTFreeListElem
	{
		char                elem[sizeof(T)];  // 00
		BSTFreeListElem<T>* next;             // ??
	};

	// size == sizeof(T) + 0x8

	template <class T>
	class BSTFreeList
	{
	public:
		virtual ~BSTFreeList() = default;  // 00

		bool Allocate(BSTFreeListElem<T>*& a_out, const T& a_value)
		{
			for (std::uint32_t expected = 0; !lock.compare_exchange_weak(expected, 1); expected = 0) {
				_mm_pause();
			}
			a_out = free;
			if (a_out) {
				free = a_out->next;
				a_out->next = nullptr;
			}
			lock.store(0);

			if (!a_out) {
				return false;
			}
			std::construct_at(reinterpret_cast<T*>(a_out->elem), a_value);
			return true;
		}

		void Free(BSTFreeListElem<T>*& a_node)
		{
			std::destroy_at(reinterpret_cast<T*>(a_node->elem));

			for (std::uint32_t expected = 0; !lock.compare_exchange_weak(expected, 1); expected = 0) {
				_mm_pause();
			}
			a_node->next = free;
			free = a_node;
			lock.store(0);
			a_node = nullptr;
		}

		// members
		std::atomic<std::uint32_t> lock{ 0 };        // 08
		std::uint32_t              pad0C;            // 0C
		BSTFreeListElem<T>*        free{ nullptr };  // 10
	};

	static_assert(sizeof(BSTFreeList<void*>) == 0x18);

	template <class T, std::size_t SIZE>
	class BSTStaticFreeList : public BSTFreeList<T>
	{
	public:
		~BSTStaticFreeList() override
		{
			for (size_t i = SIZE; i > 0; --i) {
				std::destroy_at(std::addressof(elems[i - 1]));
			}
		}  // 00

		explicit BSTStaticFreeList()
		{
			this->free = &elems[0];
			for (std::size_t i = 0; i < SIZE - 1; ++i) {
				elems[i].next = &elems[i + 1];
			}
			elems[SIZE - 1].next = nullptr;
		}

		// members
		BSTFreeListElem<T> elems[SIZE];  // 18
	};

	// size == 0x18 + sizeof(BSTFreeListElem<T>) * SIZE
}