#pragma once

#include "RE/G/GPoint.h"

namespace RE
{
	template <class T>
	class GRect
	{
	public:
		T Width() const { return right - left; }
		T Height() const { return bottom - top; }

		bool IsNull() const { return (right == left) && (bottom == top); }
		bool IsEmpty() const { return (left >= right) || (top >= bottom); }
		bool IsNormal() const { return (right >= left) && (bottom >= top); }

		void SetRect(T a_left, T a_top, T a_right, T a_bottom)
		{
			left = a_left;
			top = a_top;
			right = a_right;
			bottom = a_bottom;
		}

		void SetRect(const GPoint<T>& a_topLeft, const GPoint<T>& a_bottomRight)
		{
			SetRect(a_topLeft.x, a_topLeft.y, a_bottomRight.x, a_bottomRight.y);
		}

		GRect& Expand(T a_value)
		{
			left -= a_value;
			top -= a_value;
			right += a_value;
			bottom += a_value;
			return *this;
		}

		GRect& ExpandToPoint(T a_x, T a_y)
		{
			left = std::min(left, a_x);
			top = std::min(top, a_y);
			right = std::max(right, a_x);
			bottom = std::max(bottom, a_y);
			return *this;
		}

		GRect& ExpandToPoint(const GPoint<T>& a_point)
		{
			return ExpandToPoint(a_point.x, a_point.y);
		}

		GRect& Union(T a_left, T a_top, T a_right, T a_bottom)
		{
			left = std::min(left, a_left);
			top = std::min(top, a_top);
			right = std::max(right, a_right);
			bottom = std::max(bottom, a_bottom);
			return *this;
		}

		void Union(const GRect& a_rect)
		{
			if (IsEmpty()) {
				*this = a_rect;
			} else if (!a_rect.IsEmpty()) {
				Union(a_rect.left, a_rect.top, a_rect.right, a_rect.bottom);
			}
		}

		// members
		T left;    // 00
		T top;     // ??
		T right;   // ??
		T bottom;  // ??
	};

	using GRectF = GRect<float>;
	static_assert(sizeof(GRectF) == 0x10);

	using GRectD = GRect<double>;
	static_assert(sizeof(GRectD) == 0x20);
}
