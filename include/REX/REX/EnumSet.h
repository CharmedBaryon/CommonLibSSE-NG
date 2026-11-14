#pragma once

namespace REX
{
	template <
		class E,
		class U = std::underlying_type_t<E>>
	class EnumSet
	{
	public:
		using enum_type = E;
		using underlying_type = U;

		static_assert(std::is_enum_v<E>, "EnumSet<E, ...> must be an enum");
		static_assert(std::is_integral_v<U>, "EnumSet<..., U> must be an integral");

		constexpr EnumSet() noexcept = default;
		constexpr EnumSet(const EnumSet&) noexcept = default;
		constexpr EnumSet(EnumSet&&) noexcept = default;

		template <class U2>  // NOLINTNEXTLINE(google-explicit-constructor)
		constexpr EnumSet(EnumSet<E, U2> a_rhs) noexcept :
			_impl(static_cast<U>(a_rhs.get()))
		{}

		template <class... Args>
		constexpr EnumSet(Args... a_values) noexcept
			requires(std::same_as<Args, E> && ...)
			:
			_impl((static_cast<U>(a_values) | ...))
		{}

		~EnumSet() noexcept = default;

		constexpr EnumSet& operator=(const EnumSet&) noexcept = default;
		constexpr EnumSet& operator=(EnumSet&&) noexcept = default;

		template <class U2>
		constexpr EnumSet& operator=(EnumSet<E, U2> a_rhs) noexcept
		{
			_impl = static_cast<U>(a_rhs.get());
			return *this;
		}

		constexpr EnumSet& operator=(E a_value) noexcept
		{
			_impl = static_cast<U>(a_value);
			return *this;
		}

	public:
		[[nodiscard]] explicit constexpr operator bool() const noexcept { return _impl != static_cast<U>(0); }

		[[nodiscard]] constexpr E operator*() const noexcept { return get(); }
		[[nodiscard]] constexpr E get() const noexcept { return static_cast<E>(_impl); }
		[[nodiscard]] constexpr U underlying() const noexcept { return _impl; }

	public:
		template <class... Args>
		constexpr EnumSet& set(Args... a_args) noexcept
			requires(std::same_as<Args, E> && ...)
		{
			_impl |= (static_cast<U>(a_args) | ...);
			return *this;
		}

		template <class... Args>
		constexpr EnumSet& set(bool a_set, Args... a_args) noexcept
			requires(std::same_as<Args, E> && ...)
		{
			if (a_set)
				_impl |= (static_cast<U>(a_args) | ...);
			else
				_impl &= ~(static_cast<U>(a_args) | ...);

			return *this;
		}

		template <class... Args>
		constexpr EnumSet& reset(Args... a_args) noexcept
			requires(std::same_as<Args, E> && ...)
		{
			_impl &= ~(static_cast<U>(a_args) | ...);
			return *this;
		}

		constexpr EnumSet& reset() noexcept
		{
			_impl = 0;
			return *this;
		}

		template <class... Args>
		[[nodiscard]] constexpr bool any(Args... a_args) const noexcept
			requires(std::same_as<Args, E> && ...)
		{
			return (_impl & (static_cast<U>(a_args) | ...)) != static_cast<U>(0);
		}

		template <class... Args>
		[[nodiscard]] constexpr bool all(Args... a_args) const noexcept
			requires(std::same_as<Args, E> && ...)
		{
			return (_impl & (static_cast<U>(a_args) | ...)) == (static_cast<U>(a_args) | ...);
		}

		template <class... Args>
		[[nodiscard]] constexpr bool none(Args... a_args) const noexcept
			requires(std::same_as<Args, E> && ...)
		{
			return (_impl & (static_cast<U>(a_args) | ...)) == static_cast<U>(0);
		}

	public:
		friend constexpr bool operator==(EnumSet a_lhs, EnumSet a_rhs) noexcept { return a_lhs.underlying() == a_rhs.underlying(); }
		friend constexpr bool operator==(EnumSet a_lhs, E a_rhs) noexcept { return a_lhs.underlying() == static_cast<U>(a_rhs); }
		friend constexpr bool operator==(E a_lhs, EnumSet a_rhs) noexcept { return static_cast<U>(a_lhs) == a_rhs.underlying(); }

		friend constexpr std::strong_ordering operator<=>(EnumSet a_lhs, EnumSet a_rhs) noexcept { return a_lhs.underlying() <=> a_rhs.underlying(); }
		friend constexpr std::strong_ordering operator<=>(EnumSet a_lhs, E a_rhs) noexcept { return a_lhs.underlying() <=> static_cast<U>(a_rhs); }
		friend constexpr std::strong_ordering operator<=>(E a_lhs, EnumSet a_rhs) noexcept { return static_cast<U>(a_lhs) <=> a_rhs.underlying(); }

		friend constexpr EnumSet operator&(EnumSet a_lhs, EnumSet a_rhs) noexcept { return static_cast<E>(a_lhs.underlying() & a_rhs.underlying()); }
		friend constexpr EnumSet operator&(EnumSet a_lhs, E a_rhs) noexcept { return static_cast<E>(a_lhs.underlying() & static_cast<U>(a_rhs)); }
		friend constexpr EnumSet operator&(E a_lhs, EnumSet a_rhs) noexcept { return static_cast<E>(static_cast<U>(a_lhs) & a_rhs.underlying()); }

		friend constexpr EnumSet& operator&=(EnumSet& a_lhs, EnumSet a_rhs) noexcept { return a_lhs = a_lhs & a_rhs; }
		friend constexpr EnumSet& operator&=(EnumSet& a_lhs, E a_rhs) noexcept { return a_lhs = a_lhs & a_rhs; }

		friend constexpr EnumSet operator|(EnumSet a_lhs, EnumSet a_rhs) noexcept { return static_cast<E>(a_lhs.underlying() | a_rhs.underlying()); }
		friend constexpr EnumSet operator|(EnumSet a_lhs, E a_rhs) noexcept { return static_cast<E>(a_lhs.underlying() | static_cast<U>(a_rhs)); }
		friend constexpr EnumSet operator|(E a_lhs, EnumSet a_rhs) noexcept { return static_cast<E>(static_cast<U>(a_lhs) | a_rhs.underlying()); }

		friend constexpr EnumSet& operator|=(EnumSet& a_lhs, EnumSet a_rhs) noexcept { return a_lhs = a_lhs | a_rhs; }
		friend constexpr EnumSet& operator|=(EnumSet& a_lhs, E a_rhs) noexcept { return a_lhs = a_lhs | a_rhs; }

		friend constexpr EnumSet operator^(EnumSet a_lhs, EnumSet a_rhs) noexcept { return static_cast<E>(a_lhs.underlying() ^ a_rhs.underlying()); }
		friend constexpr EnumSet operator^(EnumSet a_lhs, E a_rhs) noexcept { return static_cast<E>(a_lhs.underlying() ^ static_cast<U>(a_rhs)); }
		friend constexpr EnumSet operator^(E a_lhs, EnumSet a_rhs) noexcept { return static_cast<E>(static_cast<U>(a_lhs) ^ a_rhs.underlying()); }

		friend constexpr EnumSet& operator^=(EnumSet& a_lhs, EnumSet a_rhs) noexcept { return a_lhs = a_lhs ^ a_rhs; }
		friend constexpr EnumSet& operator^=(EnumSet& a_lhs, E a_rhs) noexcept { return a_lhs = a_lhs ^ a_rhs; }

		friend constexpr EnumSet operator+(EnumSet a_lhs, EnumSet a_rhs) noexcept { return static_cast<E>(a_lhs.underlying() + a_rhs.underlying()); }
		friend constexpr EnumSet operator+(EnumSet a_lhs, E a_rhs) noexcept { return static_cast<E>(a_lhs.underlying() + static_cast<U>(a_rhs)); }
		friend constexpr EnumSet operator+(E a_lhs, EnumSet a_rhs) noexcept { return static_cast<E>(static_cast<U>(a_lhs) + a_rhs.underlying()); }

		friend constexpr EnumSet& operator+=(EnumSet& a_lhs, EnumSet a_rhs) noexcept { return a_lhs = a_lhs + a_rhs; }
		friend constexpr EnumSet& operator+=(EnumSet& a_lhs, E a_rhs) noexcept { return a_lhs = a_lhs + a_rhs; }

		friend constexpr EnumSet operator-(EnumSet a_lhs, EnumSet a_rhs) noexcept { return static_cast<E>(a_lhs.underlying() - a_rhs.underlying()); }
		friend constexpr EnumSet operator-(EnumSet a_lhs, E a_rhs) noexcept { return static_cast<E>(a_lhs.underlying() - static_cast<U>(a_rhs)); }
		friend constexpr EnumSet operator-(E a_lhs, EnumSet a_rhs) noexcept { return static_cast<E>(static_cast<U>(a_lhs) - a_rhs.underlying()); }

		friend constexpr EnumSet& operator-=(EnumSet& a_lhs, EnumSet a_rhs) noexcept { return a_lhs = a_lhs - a_rhs; }
		friend constexpr EnumSet& operator-=(EnumSet& a_lhs, E a_rhs) noexcept { return a_lhs = a_lhs - a_rhs; }

		friend constexpr EnumSet operator<<(EnumSet a_lhs, EnumSet a_rhs) noexcept { return static_cast<E>(a_lhs.underlying() << a_rhs.underlying()); }
		friend constexpr EnumSet operator<<(EnumSet a_lhs, E a_rhs) noexcept { return static_cast<E>(a_lhs.underlying() << static_cast<U>(a_rhs)); }
		friend constexpr EnumSet operator<<(E a_lhs, EnumSet a_rhs) noexcept { return static_cast<E>(static_cast<U>(a_lhs) << a_rhs.underlying()); }

		friend constexpr EnumSet& operator<<=(EnumSet& a_lhs, EnumSet a_rhs) noexcept { return a_lhs = a_lhs << a_rhs; }
		friend constexpr EnumSet& operator<<=(EnumSet& a_lhs, E a_rhs) noexcept { return a_lhs = a_lhs << a_rhs; }

		friend constexpr EnumSet operator>>(EnumSet a_lhs, EnumSet a_rhs) noexcept { return static_cast<E>(a_lhs.underlying() >> a_rhs.underlying()); }
		friend constexpr EnumSet operator>>(EnumSet a_lhs, E a_rhs) noexcept { return static_cast<E>(a_lhs.underlying() >> static_cast<U>(a_rhs)); }
		friend constexpr EnumSet operator>>(E a_lhs, EnumSet a_rhs) noexcept { return static_cast<E>(static_cast<U>(a_lhs) >> a_rhs.underlying()); }

		friend constexpr EnumSet& operator>>=(EnumSet& a_lhs, EnumSet a_rhs) noexcept { return a_lhs = a_lhs >> a_rhs; }
		friend constexpr EnumSet& operator>>=(EnumSet& a_lhs, E a_rhs) noexcept { return a_lhs = a_lhs >> a_rhs; }

		friend constexpr EnumSet& operator~(EnumSet& a_lhs) noexcept { return a_lhs = ~a_lhs.underlying(); }

	private:
		U _impl{ 0 };
	};

	template <class... Args>
	EnumSet(Args...) -> EnumSet<
		std::common_type_t<Args...>,
		std::underlying_type_t<
			std::common_type_t<Args...>>>;
}
