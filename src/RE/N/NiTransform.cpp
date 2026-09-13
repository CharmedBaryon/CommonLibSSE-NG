#include "RE/N/NiTransform.h"

namespace RE
{
	NiTransform NiTransform::Invert() const
	{
		NiTransform ret;
		ret.rotate = rotate.Transpose();
		ret.scale = 1.f / scale;
		ret.translate = (ret.rotate * -translate) * ret.scale;
		return ret;
	}

	bool NiTransform::operator==(const NiTransform& a_rhs) const
	{
		return (translate == a_rhs.translate && rotate == a_rhs.rotate && scale == a_rhs.scale);
	}

	bool NiTransform::operator!=(const NiTransform& a_rhs) const
	{
		return !operator==(a_rhs);
	}

	NiTransform NiTransform::operator*(const NiTransform& a_rhs) const
	{
		NiTransform ret;
		ret.scale = scale * a_rhs.scale;
		ret.rotate = rotate * a_rhs.rotate;
		ret.translate = translate + (rotate * a_rhs.translate) * scale;
		return ret;
	}

	NiPoint3 NiTransform::operator*(const NiPoint3& a_point) const
	{
		return (((rotate * a_point) * scale) + translate);
	}

	float NiTransform::GetHeadingAngle(const NiPoint3& a_targPos, bool b_abs) const
	{
		auto ToEulerAngleZ = [](const NiMatrix3& R) -> float {
			auto sy = std::sqrt(R.entry[0][0] * R.entry[0][0] + R.entry[0][1] * R.entry[0][1]);
			return sy < 1e-6 ? 0.f : std::atan2f(R.entry[0][1], R.entry[0][0]);
		};

		float theta = std::atan2f(a_targPos.x - translate.x, a_targPos.y - translate.y);
		float heading = static_cast<float>(180.0f / std::numbers::pi * (theta - ToEulerAngleZ(rotate)));

		if (heading < -180.f)
			heading += 360.f;

		if (heading > 180.f)
			heading -= 360.f;

		return b_abs ? std::abs(heading) : heading;
	}
}
