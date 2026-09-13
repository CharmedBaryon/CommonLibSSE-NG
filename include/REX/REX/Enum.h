#pragma once

namespace REX
{
	template <
		class E,
		class U = std::underlying_type_t<E>>
	class Enum
	{
	public:
		using enum_type = E;
		using underlying_type = U;

		static_assert(std::is_enum_v<E>, "Enum<E, ...> must be an enum");
		static_assert(std::is_integral_v<U>, "Enum<..., U> must be an integral");

		constexpr Enum() noexcept = default;
		constexpr Enum(const Enum&) noexcept = default;
		constexpr Enum(Enum&&) noexcept = default;

		template <class U2>  // NOLINTNEXTLINE(google-explicit-constructor)
		constexpr Enum(Enum<E, U2> a_rhs) noexcept :
			_impl(static_cast<U>(a_rhs.get()))
		{}

		constexpr Enum(E a_value) noexcept :
			_impl(static_cast<U>(a_value))
		{}

		~Enum() noexcept = default;

		constexpr Enum& operator=(const Enum&) noexcept = default;
		constexpr Enum& operator=(Enum&&) noexcept = default;

		template <class U2>
		constexpr Enum& operator=(Enum<E, U2> a_rhs) noexcept
		{
			_impl = static_cast<U>(a_rhs.get());
		}

		constexpr Enum& operator=(E a_value) noexcept
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
		friend constexpr bool operator==(Enum a_lhs, Enum a_rhs) noexcept { return a_lhs.underlying() == a_rhs.underlying(); }
		friend constexpr bool operator==(Enum a_lhs, E a_rhs) noexcept { return a_lhs.underlying() == static_cast<U>(a_rhs); }
		friend constexpr bool operator==(E a_lhs, Enum a_rhs) noexcept { return static_cast<U>(a_lhs) == a_rhs.underlying(); }

	private:
		U _impl{ 0 };
	};

	template <class... Args>
	Enum(Args...) -> Enum<
		std::common_type_t<Args...>,
		std::underlying_type_t<
			std::common_type_t<Args...>>>;
}
