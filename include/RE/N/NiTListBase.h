#pragma once

namespace RE
{
	template <class T>
	class NiTListItem
	{
	public:
		NiTListItem() :
			next(nullptr),
			prev(nullptr),
			element{}
		{}

		NiTListItem* next;     // 00
		NiTListItem* prev;     // 08
		T            element;  // 10
	};
	static_assert(sizeof(NiTListItem<void*>) == 0x18);

	template <class Allocator, class T>
	class NiTListBase
	{
	private:
		using Node = NiTListItem<T>;

	public:
		using value_type = T;
		using size_type = std::uint32_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const value_type&;

		template <class U>
		class iterator_base
		{
		public:
			using difference_type = std::ptrdiff_t;
			using value_type = U;
			using pointer = U*;
			using reference = U&;
			using iterator_category = std::bidirectional_iterator_tag;

			constexpr iterator_base() noexcept :
				_cur(nullptr)
			{}

			constexpr iterator_base(Node* a_node) noexcept :
				_cur(a_node)
			{}

			constexpr iterator_base(const iterator_base& a_rhs) noexcept :
				_cur(a_rhs._cur)
			{}

			constexpr iterator_base(iterator_base&& a_rhs) noexcept :
				_cur(std::move(a_rhs._cur))
			{
				a_rhs._cur = nullptr;
			}

			inline ~iterator_base() noexcept { _cur = nullptr; }

			constexpr iterator_base& operator=(const iterator_base& a_rhs) noexcept
			{
				if (this != std::addressof(a_rhs)) {
					_cur = a_rhs._cur;
				}
				return *this;
			}

			constexpr iterator_base& operator=(iterator_base&& a_rhs) noexcept
			{
				if (this != std::addressof(a_rhs)) {
					_cur = std::move(a_rhs._cur);
					a_rhs._cur = nullptr;
				}
				return *this;
			}

			[[nodiscard]] constexpr reference operator*() const noexcept { return _cur->element; }
			[[nodiscard]] constexpr pointer   operator->() const noexcept { return std::addressof(_cur->element); }

			[[nodiscard]] constexpr bool operator==(const iterator_base& a_rhs) const noexcept { return _cur == a_rhs._cur; }
			[[nodiscard]] constexpr bool operator!=(const iterator_base& a_rhs) const noexcept { return !(*this == a_rhs); }

		protected:
			friend class NiTListBase<T, Allocator>;

			Node* _cur;
		};

		template <class U>
		class forward_iterator : public iterator_base<U>
		{
		public:
			// prefix
			constexpr forward_iterator& operator++() noexcept
			{
				assert(this->_cur);
				this->_cur = this->_cur->next;
				return *this;
			}

			// postfix
			[[nodiscard]] constexpr forward_iterator operator++(int) noexcept
			{
				iterator_base tmp(*this);
				++(*this);
				return tmp;
			}
		};

		template <class U>
		class backward_iterator : public iterator_base<U>
		{
		public:
			// prefix
			constexpr backward_iterator& operator++() noexcept
			{
				assert(this->_cur);
				this->_cur = this->_cur->prev;
				return *this;
			}

			// postfix
			[[nodiscard]] constexpr backward_iterator operator++(int) noexcept
			{
				iterator_base tmp(*this);
				++(*this);
				return tmp;
			}
		};

		using iterator = forward_iterator<value_type>;
		using const_iterator = forward_iterator<const value_type>;
		using reverse_iterator = backward_iterator<value_type>;
		using const_reverse_iterator = backward_iterator<const value_type>;

		inline NiTListBase() :
			head(nullptr),
			tail(nullptr),
			allocator(0)
		{}

		[[nodiscard]] inline reference front()
		{
			assert(!empty());
			return *begin();
		}

		[[nodiscard]] inline const_reference front() const
		{
			assert(!empty());
			return *begin();
		}

		[[nodiscard]] inline reference back()
		{
			assert(!empty());
			return *rbegin();
		}

		[[nodiscard]] inline const_reference back() const
		{
			assert(!empty());
			return *rbegin();
		}

		[[nodiscard]] inline iterator       begin() { return empty() ? end() : iterator(head); }
		[[nodiscard]] inline const_iterator begin() const { return empty() ? end() : const_iterator(head); }
		[[nodiscard]] inline const_iterator cbegin() const { return begin(); }

		[[nodiscard]] constexpr iterator       end() noexcept { return iterator(nullptr); }
		[[nodiscard]] constexpr const_iterator end() const noexcept { return const_iterator(nullptr); }
		[[nodiscard]] constexpr const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] inline reverse_iterator       rbegin() { return empty() ? rend() : reverse_iterator(tail); }
		[[nodiscard]] inline const_reverse_iterator rbegin() const { return empty() ? rend() : const_reverse_iterator(tail); }
		[[nodiscard]] inline const_reverse_iterator crbegin() const { return rbegin(); }

		[[nodiscard]] constexpr reverse_iterator       rend() noexcept { return reverse_iterator(nullptr); }
		[[nodiscard]] constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(nullptr); }
		[[nodiscard]] constexpr const_reverse_iterator crend() const noexcept { return rend(); }

		[[nodiscard]] inline bool empty() const { return allocator.size == 0; }
		[[nodiscard]] size_type   size() const noexcept { return allocator.size; }

	protected:
		struct AntiBloatAllocator : public Allocator
		{
			// members
			std::uint32_t size;  // ??
		};

		// members
		NiTListItem<T>*    head;       // 00
		NiTListItem<T>*    tail;       // 08
		AntiBloatAllocator allocator;  // 10
	};
}
