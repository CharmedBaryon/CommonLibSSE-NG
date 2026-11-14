#pragma once

#include "RE/M/MemoryManager.h"

namespace RE
{
	template <class T>
	class BSTListNode
	{
	public:
		using value_type = T;

		template <class... Args>
		inline BSTListNode(Args&&... a_args) :
			item(std::forward<Args>(a_args)...)
		{}

		// members
		BSTListNode<T>* next;  // 00
		BSTListNode<T>* prev;  // 08
		value_type      item;  // 10
	};

	template <class T>
	class BSTListHeapAllocator
	{
	public:
		[[nodiscard]] inline BSTListNode<T>* allocate()
		{
			return malloc<BSTListNode<T>>();
		}

		inline void deallocate(BSTListNode<T>* a_node)
		{
			free(a_node);
		}
	};

	template <class T, class Allocator = BSTListHeapAllocator<T>>
	class BSTList
	{
	public:
		using value_type = T;
		using allocator_type = Allocator;
		using reference = T&;
		using const_reference = const T&;

		struct const_iterator
		{
		public:
			using value_type = T;
			using const_pointer = const T*;
			using iterator_category = std::bidirectional_iterator_tag;

			friend BSTList<T, Allocator>;

			const_iterator(BSTListNode<T>* a_node) noexcept :
				_cur(a_node)
			{}

			constexpr const_iterator(const const_iterator& a_rhs) noexcept :
				_cur(a_rhs._cur)
			{}

			constexpr const_iterator(const const_iterator&& a_rhs) noexcept :
				_cur(a_rhs._cur)
			{
				a_rhs._cur = nullptr;
			}

			constexpr const_iterator& operator=(const const_iterator& a_rhs) noexcept
			{
				if (this != std::addressof(a_rhs)) {
					_cur = a_rhs._cur;
				}
				return *this;
			}

			constexpr const_iterator& operator=(const_iterator&& a_rhs) noexcept
			{
				if (this != std::addressof(a_rhs)) {
					_cur = std::move(a_rhs._cur);
					a_rhs._cur = nullptr;
				}
				return *this;
			}

			[[nodiscard]] constexpr const_reference operator*() const noexcept { return _cur->item; }
			[[nodiscard]] constexpr const_pointer   operator->() const noexcept { return std::addressof(_cur->item); }

			[[nodiscard]] constexpr bool operator==(const const_iterator& a_rhs) const noexcept { return _cur == a_rhs._cur; }
			[[nodiscard]] constexpr bool operator!=(const const_iterator& a_rhs) const noexcept { return !(*this == a_rhs); }

			// prefix
			constexpr const_iterator& operator++() noexcept
			{
				assert(_cur);
				_cur = _cur->next;
				return *this;
			}

			// postfix
			[[nodiscard]] constexpr const_iterator operator++(int) noexcept
			{
				const_iterator tmp(*this);
				++(*this);
				return tmp;
			}

			// prefix
			constexpr const_iterator& operator--() noexcept
			{
				assert(_cur);
				_cur = _cur->prev;
				return *this;
			}

			// postfix
			[[nodiscard]] constexpr const_iterator operator--(int) noexcept
			{
				const_iterator tmp(*this);
				--(*this);
				return tmp;
			}

		protected:
			BSTListNode<T>* _cur;
		};

		struct iterator : public const_iterator
		{
		public:
			using pointer = T*;

			using const_iterator::const_iterator;

			[[nodiscard]] constexpr reference operator*() const noexcept { return const_iterator::_cur->item; }
			[[nodiscard]] constexpr pointer   operator->() const noexcept { return std::addressof(const_iterator::_cur->item); }

			// prefix
			constexpr iterator& operator++() noexcept
			{
				const_iterator::operator++();
				return *this;
			}

			// postfix
			[[nodiscard]] constexpr iterator operator++(int) noexcept
			{
				iterator tmp(*this);
				const_iterator::operator++();
				return tmp;
			}

			// prefix
			constexpr iterator& operator--() noexcept
			{
				const_iterator::operator--();
				return *this;
			}

			// postfix
			[[nodiscard]] constexpr iterator operator--(int) noexcept
			{
				iterator tmp(*this);
				const_iterator::operator--();
				return tmp;
			}
		};

		constexpr BSTList() :
			_sentinel(nullptr)
		{}

		BSTList(const BSTList&) = delete;
		BSTList(BSTList&&) = delete;

		inline ~BSTList()
		{
			clear();
			if (_sentinel) {
				destroy_list();
			}
		}

		BSTList& operator=(const BSTList&) = delete;
		BSTList& operator=(BSTList&&) = delete;

		inline reference front()
		{
			return _sentinel->next->item;
		}

		inline const_reference front() const
		{
			return _sentinel->next->item;
		}

		inline reference back()
		{
			return _sentinel->prev->item;
		}

		inline const_reference back() const
		{
			return _sentinel->prev->item;
		}

		inline iterator begin()
		{
			return iterator(_sentinel ? _sentinel->next : nullptr);
		}

		inline const_iterator begin() const
		{
			return const_iterator(_sentinel ? _sentinel->next : nullptr);
		}

		inline const_iterator cbegin() const
		{
			return const_iterator(_sentinel ? _sentinel->next : nullptr);
		}

		inline iterator end()
		{
			return iterator(_sentinel);
		}

		inline const_iterator end() const
		{
			return const_iterator(_sentinel);
		}

		inline const_iterator cend() const
		{
			return const_iterator(_sentinel);
		}

		constexpr bool empty() const
		{
			return !_sentinel || _sentinel->next == _sentinel;
		}

		inline void clear()
		{
			if (!_sentinel) {
				return;
			}

			for (auto node = _sentinel->next; node != _sentinel; node = node->next) {
				std::destroy_at(node);
				allocator_type{}.deallocate(node);
			}

			destroy_list();
		}

		template <class... Args>
		inline iterator emplace(const_iterator a_pos, Args&&... a_args)
		{
			emplace_impl(a_pos, std::forward<Args>(a_args)...);
			return a_pos._cur->prev;
		}

		inline iterator erase(const_iterator a_pos)
		{
			const auto node = a_pos._cur;
			const auto next = node->next;
			node->prev->next = next;
			next->prev = node->prev;

			node->prev = nullptr;
			node->next = nullptr;
			allocator_type{}.deallocate(node);

			return iterator(next);
		}

		inline void push_back(const T& a_value)
		{
			emplace_back(a_value);
		}

		inline void push_back(T&& a_value)
		{
			emplace_back(std::move(a_value));
		}

		template <class... Args>
		inline reference emplace_back(Args&&... a_args)
		{
			emplace_back_impl(std::forward<Args>(a_args)...);
			return back();
		}

		inline void push_front(const T& a_value)
		{
			emplace_front(a_value);
		}

		inline void push_front(T&& a_value)
		{
			emplace_front(std::move(a_value));
		}

		template <class... Args>
		inline reference emplace_front(Args&&... a_args)
		{
			emplace_front_impl(std::forward<Args>(a_args)...);
			return front();
		}

	private:
		template <class... Args>
		inline void emplace_impl(const_iterator a_pos, Args&&... a_args)
		{
			const auto node = allocator_type{}.allocate();
			if (!node) {
				return;
			}

			std::construct_at(node, std::forward<Args>(a_args)...);
			node->next = a_pos._cur;
			node->prev = a_pos._cur->prev;
			a_pos._cur->prev->next = node;
			a_pos._cur->prev = node;
		}

		template <class... Args>
		inline void emplace_back_impl(Args&&... a_args)
		{
			if (!_sentinel) {
				create_list();
			}

			const auto node = allocator_type{}.allocate();
			if (!node) {
				return;
			}

			std::construct_at(node, std::forward<Args>(a_args)...);
			node->next = _sentinel;
			node->prev = _sentinel->prev;
			_sentinel->prev->next = node;
			_sentinel->prev = node;
		}

		template <class... Args>
		inline void emplace_front_impl(Args&&... a_args)
		{
			if (!_sentinel) {
				create_list();
			}

			const auto node = allocator_type{}.allocate();
			if (!node) {
				return;
			}

			std::construct_at(node, std::forward<Args>(a_args)...);
			node->prev = _sentinel;
			node->next = _sentinel->next;
			_sentinel->next->prev = node;
			_sentinel->next = node;
		}

		inline bool create_list()
		{
			_sentinel = allocator_type{}.allocate();
			if (_sentinel) {
				_sentinel->next = _sentinel;
				_sentinel->prev = _sentinel;
			}
			return _sentinel;
		}

		inline void destroy_list()
		{
			allocator_type{}.deallocate(_sentinel);
			_sentinel = nullptr;
		}

		// members

		BSTListNode<T>* _sentinel;  // 0
	};
}
