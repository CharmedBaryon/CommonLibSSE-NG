#pragma once

namespace REL
{
	class Version
	{
	public:
		using value_type = std::uint16_t;
		using reference = value_type&;
		using const_reference = const value_type&;

		constexpr Version() noexcept = default;

		explicit constexpr Version(std::array<value_type, 4> a_version) noexcept :
			_impl(a_version)
		{}

		constexpr Version(value_type a_v1, value_type a_v2 = 0, value_type a_v3 = 0, value_type a_v4 = 0) noexcept :
			_impl{ a_v1, a_v2, a_v3, a_v4 }
		{}

		explicit constexpr Version(std::string_view a_version)
		{
			std::array<value_type, 4> powers{ 1, 1, 1, 1 };
			std::size_t               position = 0;
			for (std::size_t i = 0; i < a_version.size(); ++i) {
				if (a_version[i] == '.') {
					if (++position == powers.size()) {
						throw std::invalid_argument("Too many parts in version number.");
					}
				} else {
					powers[position] *= 10;
				}
			}
			position = 0;
			for (std::size_t i = 0; i < a_version.size(); ++i) {
				if (a_version[i] == '.') {
					++position;
				} else if (a_version[i] < '0' || a_version[i] > '9') {
					throw std::invalid_argument("Invalid character in version number.");
				} else {
					powers[position] /= 10;
					_impl[position] += static_cast<value_type>((a_version[i] - '0') * powers[position]);
				}
			}
		}

		[[nodiscard]] constexpr reference operator[](std::size_t a_idx) noexcept { return _impl[a_idx]; }

		[[nodiscard]] constexpr const_reference operator[](std::size_t a_idx) const noexcept { return _impl[a_idx]; }

		[[nodiscard]] constexpr decltype(auto) begin() const noexcept { return _impl.begin(); }

		[[nodiscard]] constexpr decltype(auto) cbegin() const noexcept { return _impl.cbegin(); }

		[[nodiscard]] constexpr decltype(auto) end() const noexcept { return _impl.end(); }

		[[nodiscard]] constexpr decltype(auto) cend() const noexcept { return _impl.cend(); }

		[[nodiscard]] std::strong_ordering constexpr compare(const Version& a_rhs) const noexcept
		{
			for (std::size_t i = 0; i < _impl.size(); ++i) {
				if ((*this)[i] != a_rhs[i]) {
					return (*this)[i] < a_rhs[i] ? std::strong_ordering::less : std::strong_ordering::greater;
				}
			}
			return std::strong_ordering::equal;
		}

		[[nodiscard]] constexpr std::uint32_t pack() const noexcept
		{
			return static_cast<std::uint32_t>(
				(_impl[0] & 0x0FF) << 24u |
				(_impl[1] & 0x0FF) << 16u |
				(_impl[2] & 0xFFF) << 4u |
				(_impl[3] & 0x00F) << 0u);
		}

		[[nodiscard]] constexpr value_type major() const noexcept
		{
			return _impl[0];
		}

		[[nodiscard]] constexpr value_type minor() const noexcept
		{
			return _impl[1];
		}

		[[nodiscard]] constexpr value_type patch() const noexcept
		{
			return _impl[2];
		}

		[[nodiscard]] constexpr value_type build() const noexcept
		{
			return _impl[3];
		}

		[[nodiscard]] std::string string(std::string_view a_separator = "-"sv) const
		{
			std::string result;
			for (auto&& ver : _impl) {
				result += std::to_string(ver);
				result.append(a_separator.data(), a_separator.size());
			}
			result.erase(result.size() - a_separator.size(), a_separator.size());
			return result;
		}

		[[nodiscard]] std::wstring wstring(std::wstring_view a_separator = L"-"sv) const
		{
			std::wstring result;
			for (auto&& ver : _impl) {
				result += std::to_wstring(ver);
				result.append(a_separator.data(), a_separator.size());
			}
			result.erase(result.size() - a_separator.size(), a_separator.size());
			return result;
		}

		[[nodiscard]] static constexpr Version unpack(std::uint32_t a_packedVersion) noexcept
		{
			return REL::Version{
				static_cast<value_type>((a_packedVersion >> 24) & 0x0FF),
				static_cast<value_type>((a_packedVersion >> 16) & 0x0FF),
				static_cast<value_type>((a_packedVersion >> 4) & 0xFFF),
				static_cast<value_type>(a_packedVersion & 0x0F)
			};
		}

	private:
		std::array<value_type, 4> _impl{ 0, 0, 0, 0 };
	};

	[[nodiscard]] constexpr bool operator==(const Version& a_lhs, const Version& a_rhs) noexcept
	{
		return a_lhs.compare(a_rhs) == std::strong_ordering::equal;
	}

	[[nodiscard]] constexpr std::strong_ordering
		operator<=>(const Version& a_lhs, const Version& a_rhs) noexcept { return a_lhs.compare(a_rhs); }

	namespace literals
	{
		namespace detail
		{
			template <std::size_t Index, char C>
			constexpr uint8_t read_version(std::array<typename REL::Version::value_type, 4>& result)
			{
				static_assert(C >= '0' && C <= '9', "Invalid character in semantic version literal.");
				static_assert(Index < 4, "Too many components in semantic version literal.");
				result[Index] += (C - '0');
				return 10;
			}

			template <std::size_t Index, char C, char... Rest>
				requires(sizeof...(Rest) > 0)
			constexpr uint8_t read_version(std::array<typename REL::Version::value_type, 4>& result)
			{
				static_assert(C == '.' || (C >= '0' && C <= '9'), "Invalid character in semantic version literal.");
				static_assert(Index < 4, "Too many components in semantic version literal.");
				if constexpr (C == '.') {
					read_version<Index + 1, Rest...>(result);
					return 1;
				} else {
					auto position = read_version<Index, Rest...>(result);
					result[Index] += (C - '0') * position;
					return position * 10;
				}
			}
		}

		template <char... C>
		[[nodiscard]] constexpr REL::Version operator""_v() noexcept
		{
			std::array<typename REL::Version::value_type, 4> result{ 0, 0, 0, 0 };
			detail::read_version<0, C...>(result);
			return REL::Version(result);
		}

		[[nodiscard]] constexpr REL::Version operator""_v(const char* str, std::size_t len)
		{
			return Version(std::string_view(str, len));
		}
	}

	[[nodiscard]] std::optional<Version> GetFileVersion(stl::zwstring a_filename);
}

namespace std
{
	[[nodiscard]] inline std::string to_string(REL::Version a_version)
	{
		return a_version.string("."sv);
	}
}

#ifdef __cpp_lib_format
template <class CharT>
struct std::formatter<REL::Version, CharT> : formatter<std::string, CharT>
{
	template <class FormatContext>
	auto format(const REL::Version& a_version, FormatContext& a_ctx) const
	{
		return formatter<std::string, CharT>::format(a_version.string("."), a_ctx);
	}
};
#endif

#ifdef FMT_VERSION
template <class CharT>
struct fmt::formatter<REL::Version, CharT> : formatter<std::string, CharT>
{
	template <class FormatContext>
	auto format(const REL::Version& a_version, FormatContext& a_ctx)
	{
		return formatter<std::string, CharT>::format(a_version.string("."), a_ctx);
	}
};
#endif
