#pragma once

namespace RE
{
	class NiPoint3;

	class NiMatrix3
	{
	public:
		constexpr NiMatrix3() noexcept
		{
			entry[0][0] = 1.0f;
			entry[0][1] = 0.0f;
			entry[0][2] = 0.0f;
			entry[1][0] = 0.0f;
			entry[1][1] = 1.0f;
			entry[1][2] = 0.0f;
			entry[2][0] = 0.0f;
			entry[2][1] = 0.0f;
			entry[2][2] = 1.0f;
		}

		NiMatrix3(const NiPoint3& a_point);
		NiMatrix3(float a_x, float a_y, float a_z);
		NiMatrix3(const NiPoint3& a_x, const NiPoint3& a_y, const NiPoint3& a_z);

		NiPoint3 GetVectorX() const;
		NiPoint3 GetVectorY() const;
		NiPoint3 GetVectorZ() const;

		bool      ToEulerAnglesXYZ(NiPoint3& a_angle) const;
		bool      ToEulerAnglesXYZ(float& a_xAngle, float& a_yAngle, float& a_zAngle) const;
		void      EulerAnglesToAxesZXY(const NiPoint3& a_angle);
		void      EulerAnglesToAxesZXY(float a_xAngle, float a_yAngle, float a_zAngle);
		void      SetEulerAnglesXYZ(const NiPoint3& a_point);
		void      SetEulerAnglesXYZ(float a_x, float a_y, float a_z);
		NiMatrix3 Transpose() const;

		bool      operator==(const NiMatrix3& a_rhs) const;
		bool      operator!=(const NiMatrix3& a_rhs) const;
		NiMatrix3 operator*(const NiMatrix3& a_rhs) const;
		NiPoint3  operator*(const NiPoint3& a_point) const;
		NiMatrix3 operator*(float a_scalar) const;

		// members
		float entry[3][3];  // 00
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(NiMatrix3) == 0x24);
}
