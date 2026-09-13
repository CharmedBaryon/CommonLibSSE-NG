#pragma once

#include "RE/M/MemoryManager.h"

namespace RE
{
	inline constexpr auto DEFAULT_OBJECT_ARENA_PAGE_SIZE = 32;

	class BSTObjectArenaHeapAlloc
	{
	public:
		using size_type = std::uint32_t;

		[[nodiscard]] static void* allocate_bytes(size_type a_count) noexcept { return calloc<std::byte>(a_count); }
		static void                deallocate_bytes(void* a_ptr) { free(a_ptr); }
	};
	static_assert(std::is_empty_v<BSTObjectArenaHeapAlloc>);

	class BSTObjectArenaScrapAllocBase
	{
	public:
		// members
		ScrapHeap* scrapHeap{ MemoryManager::GetSingleton()->GetThreadScrapHeap() };  // 0
	};
	static_assert(sizeof(BSTObjectArenaScrapAllocBase) == 0x8);

	class BSTObjectArenaScrapAlloc :
		private BSTObjectArenaScrapAllocBase  // 0
	{
	public:
		using size_type = std::uint32_t;

		[[nodiscard]] void* allocate_bytes(size_type a_bytes) { return scrapHeap->Allocate(a_bytes, 0x8); }
		void                deallocate_bytes(void* a_ptr) { scrapHeap->Deallocate(a_ptr); }
	};
	static_assert(sizeof(BSTObjectArenaScrapAlloc) == 0x8);

	template <
		class T,
		class Allocator = BSTObjectArenaHeapAlloc,
		std::uint32_t N = DEFAULT_OBJECT_ARENA_PAGE_SIZE>
	class BSTObjectArena :
		private Allocator  // 00
	{
	private:
		using super = Allocator;

	public:
		using value_type = T;
		using allocator_type = Allocator;
		using size_type = std::uint32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;

		class Page
		{
		public:
			TES_HEAP_REDEFINE_NEW();

			[[nodiscard]] std::byte*       begin() noexcept { return std::begin(buffer); }
			[[nodiscard]] const std::byte* begin() const noexcept { return std::begin(buffer); }
			[[nodiscard]] const std::byte* cbegin() const noexcept { return begin(); }

			[[nodiscard]] std::byte*       end() noexcept { return std::end(buffer); }
			[[nodiscard]] const std::byte* end() const noexcept { return std::end(buffer); }
			[[nodiscard]] const std::byte* cend() const noexcept { return end(); }

			// members
			std::byte buffer[sizeof(value_type) * N]{ static_cast<std::byte>(0) };  // 00
			Page*     next{ nullptr };                                              // ??
		};

	private:
		template <class U>
		class iterator_base
		{
		public:
			using difference_type = std::ptrdiff_t;
			using value_type = std::remove_const_t<U>;
			using pointer = value_type*;
			using reference = value_type&;
			using iterator_category = std::forward_iterator_tag;

			iterator_base() noexcept = default;

			template <class V>
			iterator_base(const iterator_base<V>& a_rhs) noexcept  //
				requires(std::convertible_to<typename iterator_base<V>::reference, reference>)
				:
				_proxy(a_rhs._proxy),
				_first(a_rhs._first),
				_last(a_rhs._last)
			{}

			~iterator_base() noexcept = default;

			template <class V>
			iterator_base& operator=(const iterator_base<V>& a_rhs) noexcept  //
				requires(std::convertible_to<typename iterator_base<V>::reference, reference>)
			{
				_proxy = a_rhs._proxy;
				_first = a_rhs._first;
				_last = a_rhs._last;
				return *this;
			}

			[[nodiscard]] reference operator*() const noexcept
			{
				assert(good());
				return *std::launder(reinterpret_cast<pointer>(_first));
			}

			[[nodiscard]] pointer operator->() const noexcept
			{
				return std::pointer_traits<pointer>::pointer_to(operator*());
			}

			template <class V>
			[[nodiscard]] bool operator==(const iterator_base<V>& a_rhs) const noexcept
			{
				assert(_last == a_rhs._last);
				if (_first == a_rhs._first) {
					assert(_proxy == a_rhs._proxy);
					return true;
				} else {
					return false;
				}
			}

			template <class V>
			[[nodiscard]] bool operator!=(const iterator_base<V>& a_rhs) const noexcept
			{
				return !operator==(a_rhs);
			}

			iterator_base& operator++() noexcept
			{
				assert(good());
				_first += sizeof(value_type);
				if (_first == _proxy->cend() && _first != _last) {
					_proxy = _proxy->next;
					_first = _proxy->begin();
				}
				return *this;
			}

			iterator_base operator++(int) noexcept
			{
				iterator_base tmp{ *this };
				operator++();
				return tmp;
			}

		protected:
			template <class, class, std::uint32_t>
			friend class BSTObjectArena;

			explicit iterator_base(Page* a_proxy, std::byte* a_first, std::byte* a_last) noexcept :
				_proxy(a_proxy),
				_first(a_first),
				_last(a_last)
			{}

		private:
			template <class>
			friend class iterator_base;

			[[nodiscard]] bool good() const noexcept
			{
				return _proxy != nullptr &&
				       _first != nullptr &&
				       _last != nullptr &&
				       _first != _last &&
				       _first != _proxy->cend();
			}

			Page*      _proxy{ nullptr };
			std::byte* _first{ nullptr };
			std::byte* _last{ nullptr };
		};

	public:
		using iterator = iterator_base<value_type>;
		using const_iterator = iterator_base<const value_type>;

		~BSTObjectArena()
		{
			const auto del = [](Page*& a_page) -> void {
				while (a_page != nullptr) {
					auto* next = a_page->next;
					allocator_type::deallocate_bytes(a_page);
					a_page = next;
				}
			};

			clear();
			del(_head);
			del(_free);
			_tail = nullptr;
			_end = nullptr;
			_begin = nullptr;
		}

		TES_HEAP_REDEFINE_NEW();

		[[nodiscard]] constexpr reference operator[](size_type a_pos) noexcept
		{
			assert(a_pos < size() && a_pos < N);
			return data()[a_pos];
		}

		[[nodiscard]] constexpr const_reference operator[](size_type a_pos) const noexcept
		{
			assert(a_pos < size() && a_pos < N);
			return data()[a_pos];
		}

		[[nodiscard]] reference       at(size_type a_pos) noexcept { return operator[](a_pos); }
		[[nodiscard]] const_reference at(size_type a_pos) const noexcept { return operator[](a_pos); }

		[[nodiscard]] constexpr reference       front() noexcept { return operator[](0); }
		[[nodiscard]] constexpr const_reference front() const noexcept { return operator[](0); }

		[[nodiscard]] constexpr reference       back() noexcept { return operator[](size() - 1); }
		[[nodiscard]] constexpr const_reference back() const noexcept { return operator[](size() - 1); }

		[[nodiscard]] pointer       data() noexcept { return empty() ? nullptr : std::launder(reinterpret_cast<pointer>(_begin)); }
		[[nodiscard]] const_pointer data() const noexcept { return empty() ? nullptr : std::launder(reinterpret_cast<const_pointer>(_begin)); }

		[[nodiscard]] iterator       begin() noexcept { return iterator{ _head, _begin, _end }; }
		[[nodiscard]] const_iterator begin() const noexcept { return iterator{ _head, _begin, _end }; }
		[[nodiscard]] const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] iterator       end() noexcept { return iterator{ _tail, _end, _end }; }
		[[nodiscard]] const_iterator end() const noexcept { return iterator{ _tail, _end, _end }; }
		[[nodiscard]] const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] bool      empty() const noexcept { return size() == 0; }
		[[nodiscard]] size_type size() const noexcept { return _size; }
		[[nodiscard]] size_type capacity() const noexcept { return N; }

		void clear()
		{
			for (; _size > 0; --_size) {
				std::destroy_at(reinterpret_cast<pointer>(_begin));
				_begin += sizeof(value_type);
				if (_begin == _head->cend()) {
					if (_head == _tail) {  // reached the end
						_next = std::addressof(_head);
						_tail = nullptr;
						_end = nullptr;
						_begin = nullptr;
					} else {  // update pos to next page
						_begin = _head->next->begin();
					}

					// move head into free list, grab next page
					_head =
						std::exchange(_head->next,
							std::exchange(_free, _head));
				}
			}

			assert(empty());
		}

		iterator push_back(const value_type& a_value) { return emplace_back(a_value); }
		iterator push_back(value_type&& a_value) { return emplace_back(std::move(a_value)); }

		template <class... Args>
		iterator emplace_back(Args&&... a_args)
		{
			const auto buf = allocate_buffer();
			std::construct_at(
				reinterpret_cast<value_type*>(buf.data()),
				std::forward<Args>(a_args)...);
			return iterator{ _tail, buf.data(), _end };
		}

	private:
		[[nodiscard]] auto allocate_buffer()
			-> std::span<std::byte, sizeof(value_type)>
		{
			if (!_tail || _end == _tail->cend()) {
				const auto page =
					_free ?
						std::exchange(_free, _free->next) :  // pull from free list
						std::construct_at<Page>(
							allocator_type::allocate_bytes(sizeof(Page)));  // go to heap
				if (page) {
					page->next = nullptr;
					*_next = page;
					_next = std::addressof(page->next);
				}

				_tail = page;
				_end = page->buffer;
				if (_begin == nullptr) {
					_begin = page->buffer;
				}
			}

			++_size;
			const auto buf = _end;
			_end += sizeof(value_type);
			return std::span{ buf, sizeof(value_type) };
		}

		// members
		Page*      _head{ nullptr };                // 08 - head of active pages
		Page**     _next{ std::addressof(_head) };  // 10 - used to update next ptr when appending pages
		Page*      _tail{ nullptr };                // 18 - tail of active pages
		Page*      _free{ nullptr };                // 20 - local free list
		std::byte* _end{ nullptr };                 // 28 - ptr to end of active lifetime elements
		std::byte* _begin{ nullptr };               // 30 - ptr to beginning of active lifetime elements
		size_type  _size{ 0 };                      // 38
	};

	template <class T, std::uint32_t N = DEFAULT_OBJECT_ARENA_PAGE_SIZE>
	using BSTHeapObjectArena = BSTObjectArena<T, BSTObjectArenaHeapAlloc, N>;

	template <class T, std::uint32_t N = DEFAULT_OBJECT_ARENA_PAGE_SIZE>
	using BSTScrapObjectArena = BSTObjectArena<T, BSTObjectArenaScrapAlloc, N>;
}
