#include "RE/N/NiMatrix3.h"

#include "RE/N/NiMath.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	NiMatrix3::NiMatrix3(const NiPoint3& a_point)
	{
		SetEulerAnglesXYZ(a_point);
	}

	NiMatrix3::NiMatrix3(float a_x, float a_y, float a_z)
	{
		SetEulerAnglesXYZ(a_x, a_y, a_z);
	}

	NiMatrix3::NiMatrix3(const NiPoint3& a_x, const NiPoint3& a_y, const NiPoint3& a_z)
	{
		entry[0][0] = a_x.x;
		entry[0][1] = a_x.y;
		entry[0][2] = a_x.z;
		entry[1][0] = a_y.x;
		entry[1][1] = a_y.y;
		entry[1][2] = a_y.z;
		entry[2][0] = a_z.x;
		entry[2][1] = a_z.y;
		entry[2][2] = a_z.z;
	}

	NiPoint3 NiMatrix3::GetVectorX() const
	{
		return NiPoint3{ entry[0][0], entry[1][0], entry[2][0] };
	}

	NiPoint3 NiMatrix3::GetVectorY() const
	{
		return NiPoint3{ entry[0][1], entry[1][1], entry[2][1] };
	}

	NiPoint3 NiMatrix3::GetVectorZ() const
	{
		return NiPoint3{ entry[0][2], entry[1][2], entry[2][2] };
	}

	bool NiMatrix3::ToEulerAnglesXYZ(NiPoint3& a_angle) const
	{
		return ToEulerAnglesXYZ(a_angle.x, a_angle.y, a_angle.z);
	}

	bool NiMatrix3::ToEulerAnglesXYZ(float& a_xAngle, float& a_yAngle, float& a_zAngle) const
	{
		a_yAngle = -NiASin(entry[0][2]);
		if (a_yAngle < NI_HALF_PI) {
			if (a_yAngle > -NI_HALF_PI) {
				a_xAngle = -NiFastATan2(-entry[1][2], entry[2][2]);
				a_zAngle = -NiFastATan2(-entry[0][1], entry[0][0]);
				return true;
			} else {
				float rmY = NiFastATan2(entry[1][0], entry[1][1]);
				a_zAngle = 0.0;
				a_xAngle = rmY - a_zAngle;
				return false;
			}
		} else {
			float rpY = NiFastATan2(entry[1][0], entry[1][1]);
			a_zAngle = 0.0;
			a_xAngle = a_zAngle - rpY;
			return false;
		}
	}

	void NiMatrix3::EulerAnglesToAxesZXY(const NiPoint3& a_angle)
	{
		EulerAnglesToAxesZXY(a_angle.x, a_angle.y, a_angle.z);
	}

	void NiMatrix3::EulerAnglesToAxesZXY(float a_xAngle, float a_yAngle, float a_zAngle)
	{
		auto cosx = std::cosf(a_xAngle);
		auto sinx = std::sinf(a_xAngle);
		auto cosy = std::cosf(a_yAngle);
		auto siny = std::sinf(a_yAngle);
		auto cosz = std::cosf(a_zAngle);
		auto sinz = std::sinf(a_zAngle);

		entry[0][0] = cosz * cosy + sinz * sinx * siny;
		entry[0][1] = sinz * cosx;
		entry[0][2] = -cosz * siny + sinz * sinx * cosy;

		entry[1][0] = -sinz * cosy + cosz * sinx * siny;
		entry[1][1] = cosz * cosx;
		entry[1][2] = sinz * siny + cosz * sinx * cosy;

		entry[2][0] = cosx * siny;
		entry[2][1] = -sinx;
		entry[2][2] = cosx * cosy;
	}

	void NiMatrix3::SetEulerAnglesXYZ(const NiPoint3& a_point)
	{
		SetEulerAnglesXYZ(a_point.x, a_point.y, a_point.z);
	}

	void NiMatrix3::SetEulerAnglesXYZ(float a_x, float a_y, float a_z)
	{
		float sinX = std::sinf(a_x);
		float sinY = std::sinf(a_y);
		float sinZ = std::sinf(a_z);

		float cosX = std::cosf(a_x);
		float cosY = std::cosf(a_y);
		float cosZ = std::cosf(a_z);

		entry[0][0] = cosY * cosZ;
		entry[0][1] = cosY * sinZ;
		entry[0][2] = -sinY;
		entry[1][0] = sinX * sinY * cosZ - cosX * sinZ;
		entry[1][1] = sinX * sinY * sinZ + cosX * cosZ;
		entry[1][2] = sinX * cosY;
		entry[2][0] = cosX * sinY * cosZ + sinX * sinZ;
		entry[2][1] = cosX * sinY * sinZ - sinX * cosZ;
		entry[2][2] = cosX * cosY;
	}

	NiMatrix3 NiMatrix3::Transpose() const
	{
		NiMatrix3 result;
		result.entry[0][0] = entry[0][0];
		result.entry[0][1] = entry[1][0];
		result.entry[0][2] = entry[2][0];
		result.entry[1][0] = entry[0][1];
		result.entry[1][1] = entry[1][1];
		result.entry[1][2] = entry[2][1];
		result.entry[2][0] = entry[0][2];
		result.entry[2][1] = entry[1][2];
		result.entry[2][2] = entry[2][2];
		return result;
	}

	bool NiMatrix3::operator==(const NiMatrix3& a_rhs) const
	{
		return entry[0][0] == a_rhs.entry[0][0] &&
		       entry[0][1] == a_rhs.entry[0][1] &&
		       entry[0][2] == a_rhs.entry[0][2] &&
		       entry[1][0] == a_rhs.entry[1][0] &&
		       entry[1][1] == a_rhs.entry[1][1] &&
		       entry[1][2] == a_rhs.entry[1][2] &&
		       entry[2][0] == a_rhs.entry[2][0] &&
		       entry[2][1] == a_rhs.entry[2][1] &&
		       entry[2][2] == a_rhs.entry[2][2];
	}

	bool NiMatrix3::operator!=(const NiMatrix3& a_rhs) const
	{
		return !operator==(a_rhs);
	}

	NiMatrix3 NiMatrix3::operator*(const NiMatrix3& a_rhs) const
	{
		NiMatrix3 result;
		result.entry[0][0] =
			entry[0][0] * a_rhs.entry[0][0] +
			entry[0][1] * a_rhs.entry[1][0] +
			entry[0][2] * a_rhs.entry[2][0];
		result.entry[1][0] =
			entry[1][0] * a_rhs.entry[0][0] +
			entry[1][1] * a_rhs.entry[1][0] +
			entry[1][2] * a_rhs.entry[2][0];
		result.entry[2][0] =
			entry[2][0] * a_rhs.entry[0][0] +
			entry[2][1] * a_rhs.entry[1][0] +
			entry[2][2] * a_rhs.entry[2][0];
		result.entry[0][1] =
			entry[0][0] * a_rhs.entry[0][1] +
			entry[0][1] * a_rhs.entry[1][1] +
			entry[0][2] * a_rhs.entry[2][1];
		result.entry[1][1] =
			entry[1][0] * a_rhs.entry[0][1] +
			entry[1][1] * a_rhs.entry[1][1] +
			entry[1][2] * a_rhs.entry[2][1];
		result.entry[2][1] =
			entry[2][0] * a_rhs.entry[0][1] +
			entry[2][1] * a_rhs.entry[1][1] +
			entry[2][2] * a_rhs.entry[2][1];
		result.entry[0][2] =
			entry[0][0] * a_rhs.entry[0][2] +
			entry[0][1] * a_rhs.entry[1][2] +
			entry[0][2] * a_rhs.entry[2][2];
		result.entry[1][2] =
			entry[1][0] * a_rhs.entry[0][2] +
			entry[1][1] * a_rhs.entry[1][2] +
			entry[1][2] * a_rhs.entry[2][2];
		result.entry[2][2] =
			entry[2][0] * a_rhs.entry[0][2] +
			entry[2][1] * a_rhs.entry[1][2] +
			entry[2][2] * a_rhs.entry[2][2];
		return result;
	}

	NiPoint3 NiMatrix3::operator*(const NiPoint3& a_point) const
	{
		return NiPoint3(
			entry[0][0] * a_point.x + entry[0][1] * a_point.y + entry[0][2] * a_point.z,
			entry[1][0] * a_point.x + entry[1][1] * a_point.y + entry[1][2] * a_point.z,
			entry[2][0] * a_point.x + entry[2][1] * a_point.y + entry[2][2] * a_point.z);
	}

	NiMatrix3 NiMatrix3::operator*(float a_scalar) const
	{
		NiMatrix3 result;
		result.entry[0][0] = entry[0][0] * a_scalar;
		result.entry[0][1] = entry[0][1] * a_scalar;
		result.entry[0][2] = entry[0][2] * a_scalar;
		result.entry[1][0] = entry[1][0] * a_scalar;
		result.entry[1][1] = entry[1][1] * a_scalar;
		result.entry[1][2] = entry[1][2] * a_scalar;
		result.entry[2][0] = entry[2][0] * a_scalar;
		result.entry[2][1] = entry[2][1] * a_scalar;
		result.entry[2][2] = entry[2][2] * a_scalar;
		return result;
	}

}
