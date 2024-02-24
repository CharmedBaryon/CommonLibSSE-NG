#pragma once

#include "REL/Module.h"

namespace REL
{
	namespace detail
	{
		namespace characters
		{
			[[nodiscard]] constexpr bool hexadecimal(char a_ch) noexcept
			{
				return ('0' <= a_ch && a_ch <= '9') ||
				       ('A' <= a_ch && a_ch <= 'F') ||
				       ('a' <= a_ch && a_ch <= 'f');
			}

			[[nodiscard]] constexpr bool space(char a_ch) noexcept
			{
				return a_ch == ' ';
			}

			[[nodiscard]] constexpr bool wildcard(char a_ch) noexcept
			{
				return a_ch == '?';
			}
		}

		namespace rules
		{
			namespace detail
			{
				[[nodiscard]] consteval std::byte hexacharacters_to_hexadecimal(char a_hi, char a_lo) noexcept
				{
					constexpr auto lut = []() noexcept {
						std::array<std::uint8_t, std::numeric_limits<unsigned char>::max() + 1> a = {};

						const auto iterate = [&](std::uint8_t a_iFirst, unsigned char a_cFirst, unsigned char a_cLast) noexcept {
							for (; a_cFirst <= a_cLast; ++a_cFirst, ++a_iFirst) {
								a[a_cFirst] = a_iFirst;
							}
						};

						iterate(0, '0', '9');
						iterate(0xA, 'A', 'F');
						iterate(0xa, 'a', 'f');

						return a;
					}();

					return static_cast<std::byte>(
						lut[static_cast<unsigned char>(a_hi)] * 0x10u +
						lut[static_cast<unsigned char>(a_lo)]);
				}
			}

			template <char HI, char LO>
			class Hexadecimal
			{
			public:
				[[nodiscard]] static constexpr bool match(std::byte a_byte) noexcept
				{
					constexpr auto expected = detail::hexacharacters_to_hexadecimal(HI, LO);
					return a_byte == expected;
				}
			};

			static_assert(Hexadecimal<'5', '7'>::match(std::byte{ 0x57 }));
			static_assert(Hexadecimal<'6', '5'>::match(std::byte{ 0x65 }));
			static_assert(Hexadecimal<'B', 'D'>::match(std::byte{ 0xBD }));
			static_assert(Hexadecimal<'1', 'C'>::match(std::byte{ 0x1C }));
			static_assert(Hexadecimal<'F', '2'>::match(std::byte{ 0xF2 }));
			static_assert(Hexadecimal<'9', 'f'>::match(std::byte{ 0x9f }));

			static_assert(!Hexadecimal<'D', '4'>::match(std::byte{ 0xF8 }));
			static_assert(!Hexadecimal<'6', '7'>::match(std::byte{ 0xAA }));
			static_assert(!Hexadecimal<'7', '8'>::match(std::byte{ 0xE3 }));
			static_assert(!Hexadecimal<'6', 'E'>::match(std::byte{ 0x61 }));

			class Wildcard
			{
			public:
				[[nodiscard]] static constexpr bool match(std::byte) noexcept
				{
					return true;
				}
			};

			static_assert(Wildcard::match(std::byte{ 0xB9 }));
			static_assert(Wildcard::match(std::byte{ 0x96 }));
			static_assert(Wildcard::match(std::byte{ 0x35 }));
			static_assert(Wildcard::match(std::byte{ 0xE4 }));

			template <char, char>
			void rule_for() noexcept;

			template <char C1, char C2>
			Hexadecimal<C1, C2> rule_for() noexcept
				requires(characters::hexadecimal(C1) && characters::hexadecimal(C2));

			template <char C1, char C2>
			Wildcard rule_for() noexcept
				requires(characters::wildcard(C1) && characters::wildcard(C2));
		}

		template <class... Rules>
		class PatternMatcher
		{
		public:
			static_assert(sizeof...(Rules) >= 1, "must provide at least 1 rule for the pattern matcher");

			[[nodiscard]] constexpr bool match(std::span<const std::byte, sizeof...(Rules)> a_bytes) const noexcept
			{
				std::size_t i = 0;
				return (Rules::match(a_bytes[i++]) && ...);
			}

			[[nodiscard]] bool match(std::uintptr_t a_address) const noexcept
			{
				return this->match(*reinterpret_cast<const std::byte(*)[sizeof...(Rules)]>(a_address));
			}

			void match_or_fail(std::uintptr_t a_address, std::source_location a_loc = std::source_location::current()) const noexcept
			{
				if (!this->match(a_address)) {
					const auto version = Module::get().version();
					stl::report_and_fail(
						std::format(
							"A pattern has failed to match.\n"
							"This means the plugin is incompatible with the current version of the game ({}.{}.{}). "
							"Head to the mod page of this plugin to see if an update is available."sv,
							version[0],
							version[1],
							version[2]),
						a_loc);
				}
			}
		};

		void consteval_error(const char* a_error);

		template <stl::nttp::string S, class... Rules>
		[[nodiscard]] constexpr auto do_make_pattern() noexcept
		{
			if constexpr (S.length() == 0) {
				return PatternMatcher<Rules...>();
			} else if constexpr (S.length() == 1) {
				constexpr char c = S[0];
				if constexpr (characters::hexadecimal(c) || characters::wildcard(c)) {
					consteval_error("the given pattern has an unpaired rule (rules are required to be written in pairs of 2)");
				} else {
					consteval_error("the given pattern has trailing characters at the end (which is not allowed)");
				}
			} else {
				using rule_t = decltype(rules::rule_for<S[0], S[1]>());
				if constexpr (std::same_as<rule_t, void>) {
					consteval_error("the given pattern failed to match any known rules");
				} else {
					if constexpr (S.length() <= 3) {
						return do_make_pattern<S.template substr<2>(), Rules..., rule_t>();
					} else if constexpr (characters::space(S[2])) {
						return do_make_pattern<S.template substr<3>(), Rules..., rule_t>();
					} else {
						consteval_error("a space character is required to split byte patterns");
					}
				}
			}
		}

		template <class... Bytes>
		[[nodiscard]] consteval auto make_byte_array(Bytes... a_bytes) noexcept
			-> std::array<std::byte, sizeof...(Bytes)>
		{
			static_assert((std::integral<Bytes> && ...), "all bytes must be an integral type");
			return { static_cast<std::byte>(a_bytes)... };
		}
	}

	template <stl::nttp::string S>
	[[nodiscard]] constexpr auto make_pattern() noexcept
	{
		return detail::do_make_pattern<S>();
	}

	static_assert(make_pattern<"40 10 F2 ??">().match(
		detail::make_byte_array(0x40, 0x10, 0xF2, 0x41)));
	static_assert(make_pattern<"B8 D0 ?? ?? D4 6E">().match(
		detail::make_byte_array(0xB8, 0xD0, 0x35, 0x2A, 0xD4, 0x6E)));
}
