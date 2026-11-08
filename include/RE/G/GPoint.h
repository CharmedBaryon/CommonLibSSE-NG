#pragma once

namespace RE
{
	template <class T>
	class GPoint
	{
	public:
		enum class BoundsType
		{
			kMin,
			kMax
		};

		bool operator==(const GPoint<T>& a_rhs) const { return (x == a_rhs.x && y == a_rhs.y); };
		bool operator!=(const GPoint<T>& a_rhs) const { return !operator==(a_rhs); }

		// members
		T x;  // 00
		T y;  // ??
	};

	using GPointF = GPoint<float>;
	static_assert(sizeof(GPointF) == 0x8);

	using GPointD = GPoint<double>;
	static_assert(sizeof(GPointD) == 0x10);
}
