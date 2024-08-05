#pragma once

namespace RE
{
	class NiPoint3
	{
	public:
		constexpr NiPoint3() noexcept = default;

		constexpr NiPoint3(float a_x, float a_y, float a_z) noexcept :
			x(a_x),
			y(a_y),
			z(a_z){};

		float&       operator[](std::size_t a_idx);
		const float& operator[](std::size_t a_idx) const;
		bool         operator==(const NiPoint3& a_rhs) const;
		bool         operator!=(const NiPoint3& a_rhs) const;
		bool         operator<(const NiPoint3& a_rhs) const;
		NiPoint3     operator+(const NiPoint3& a_rhs) const;
		NiPoint3     operator-(const NiPoint3& a_rhs) const;
		float        operator*(const NiPoint3& a_rhs) const;
		NiPoint3     operator*(float a_scalar) const;
		NiPoint3     operator/(float a_scalar) const;
		NiPoint3     operator-() const;
		NiPoint3&    operator+=(const NiPoint3& a_rhs);
		NiPoint3&    operator-=(const NiPoint3& a_rhs);
		NiPoint3&    operator*=(const NiPoint3& a_rhs);
		NiPoint3&    operator/=(const NiPoint3& a_rhs);
		NiPoint3&    operator*=(float a_scalar);
		NiPoint3&    operator/=(float a_scalar);

		[[nodiscard]] NiPoint3 Cross(const NiPoint3& pt) const;
		[[nodiscard]] float    Dot(const NiPoint3& pt) const;
		[[nodiscard]] float    GetDistance(const NiPoint3& a_pt) const noexcept;
		[[nodiscard]] float    GetSquaredDistance(const NiPoint3& a_pt) const noexcept;
		[[nodiscard]] float    Length() const;
		[[nodiscard]] float    SqrLength() const;
		[[nodiscard]] NiPoint3 UnitCross(const NiPoint3& a_pt) const;
		float                  Unitize();

		static const NiPoint3& Zero();

		// members
		float x{ 0.0F };  // 0
		float y{ 0.0F };  // 4
		float z{ 0.0F };  // 8
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(NiPoint3) == 0xC);
}

#ifdef FMT_VERSION
template <>
struct fmt::formatter<RE::NiPoint3>
{
	// Presentation format: 'f' - fixed, 'e' - exponential.
	char presentation = 'f';

	// Parses format specifications of the form ['f' | 'e'].
	constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator
	{
		auto it = ctx.begin(), end = ctx.end();
		if (it != end && (*it == 'f' || *it == 'e'))
			presentation = *it++;

		// Check if reached the end of the range:
		if (it != end && *it != '}')
			format_error("invalid format");

		// Return an iterator past the end of the parsed range:
		return it;
	}

	// Formats the point p using the parsed format specification (presentation)
	// stored in this formatter.
	auto format(const RE::NiPoint3& v, format_context& ctx) const -> format_context::iterator
	{
		// ctx.out() is an output iterator to write to.
		return presentation == 'f' ? fmt::format_to(ctx.out(), "({:.1f}, {:.1f}, {:.1f})", v.x, v.y, v.z) : fmt::format_to(ctx.out(), "({:.1e}, {:.1e}, {:.1e})", v.x, v.y, v.z);
	}
};
#endif