#pragma once

#include "NiMatrix3.h"

namespace RE
{
	class NiQuaternion
	{
	public:
		NiQuaternion() = default;
		explicit NiQuaternion(const NiMatrix3& a_mat);
		NiQuaternion(float a_x, float a_y, float a_z);
		constexpr NiQuaternion(float a_w, float a_x, float a_y, float a_z) :
			w(a_w),
			x(a_x),
			y(a_y),
			z(a_z)
		{}

		constexpr bool operator==(const NiQuaternion& a_rhs) const
		{
			return (x == a_rhs.x && y == a_rhs.y && z == a_rhs.z && w == a_rhs.w);
		}

		void Correct(const NiQuaternion& a_to)
		{
			if (Dot(a_to) < 0.0f) {
				Neg();
			}
		}
		constexpr float Dot(NiQuaternion const& a_qt) const
		{
			return w * a_qt.w + x * a_qt.x + y * a_qt.y + z * a_qt.z;
		}
		constexpr void Neg()
		{
			w = -w;
			x = -x;
			y = -y;
			z = -z;
		}

		void           SetEulerAnglesXYZ(float a_x, float a_y, float a_z);
		void           SetRotation(const NiMatrix3& a_mat);
		constexpr void ToRotation(NiMatrix3& a_mat) const
		{
			float _2x = x * 2.0f;
			float _2z = z * 2.0f;
			float _2x2 = x * _2x;
			float _2xw = w * _2x;
			float _2y2 = y * y * 2.0f;
			float _2yw = w * y * 2.0f;
			float _2xy = x * y * 2.0f;
			float _2xz = x * _2z;
			float _2zw = w * _2z;
			float v12 = z * _2z + _2x2;

			a_mat.entry[0][0] = 1.0f - (z * _2z + _2y2);
			a_mat.entry[1][0] = _2xy + _2zw;
			a_mat.entry[0][1] = _2xy - _2zw;
			a_mat.entry[2][0] = _2xz - _2yw;
			a_mat.entry[0][2] = _2xz + _2yw;
			a_mat.entry[1][2] = (y * _2z) - _2xw;
			a_mat.entry[1][1] = 1.0f - v12;
			a_mat.entry[2][1] = (y * _2z) + _2xw;
			a_mat.entry[2][2] = 1.0f - (_2y2 + _2x2);
		}
		constexpr NiMatrix3 ToRotation() const
		{
			NiMatrix3 ans;
			ToRotation(ans);
			return ans;
		}

		// members
		float w;  // 00
		float x;  // 04
		float y;  // 08
		float z;  // 0C

	private:
		static constexpr std::array<uint32_t, 3> next = { { 1, 2, 0 } };
	};
	static_assert(sizeof(NiQuaternion) == 0x10);
}
