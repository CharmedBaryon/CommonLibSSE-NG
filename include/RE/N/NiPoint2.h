#pragma once

namespace RE
{
	class NiPoint2
	{
	public:
		constexpr NiPoint2() noexcept = default;

		constexpr NiPoint2(float a_x, float a_y) noexcept :
			x(a_x),
			y(a_y){};

		float&       operator[](std::size_t a_idx);
		const float& operator[](std::size_t a_idx) const;
		bool         operator==(const NiPoint2& a_rhs) const;
		bool         operator!=(const NiPoint2& a_rhs) const;
		NiPoint2     operator+(const NiPoint2& a_rhs) const;
		NiPoint2     operator-(const NiPoint2& a_rhs) const;
		float        operator*(const NiPoint2& a_rhs) const;
		NiPoint2     operator*(float a_scalar) const;
		NiPoint2     operator/(float a_scalar) const;
		NiPoint2     operator-() const;
		NiPoint2&    operator+=(const NiPoint2& a_rhs);
		NiPoint2&    operator-=(const NiPoint2& a_rhs);
		NiPoint2&    operator*=(float a_scalar);
		NiPoint2&    operator/=(float a_scalar);

		[[nodiscard]] float Cross(const NiPoint2& a_pt) const;
		[[nodiscard]] float Dot(const NiPoint2& a_pt) const;
		[[nodiscard]] float GetDistance(const NiPoint2& a_pt) const noexcept;
		[[nodiscard]] float GetSquaredDistance(const NiPoint2& a_pt) const noexcept;
		[[nodiscard]] float Length() const;
		[[nodiscard]] float SqrLength() const;
		float               Unitize();

		// members
		float x{ 0.0F };  // 0
		float y{ 0.0F };  // 4
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(NiPoint2) == 0x8);
}
