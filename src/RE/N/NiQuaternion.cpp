#include "RE/N/NiQuaternion.h"

namespace RE
{
	NiQuaternion::NiQuaternion(const NiMatrix3& a_mat)
	{
		SetRotation(a_mat);
	}

	NiQuaternion::NiQuaternion(float a_x, float a_y, float a_z)
	{
		SetEulerAnglesXYZ(a_x, a_y, a_z);
	}

	void NiQuaternion::SetRotation(const NiMatrix3& a_mat)
	{
		float X = a_mat.entry[0][0];
		float Y = a_mat.entry[1][1];
		float Z = a_mat.entry[2][2];
		float Tr = X + Y + Z;

		if (Tr <= 0.0f) {
			// 0 if M[0][0], 1 if M[1][1], 2 if M[2][2]
			uint32_t argmax = Y > X;

			const float* ptr = static_cast<const float*>(&a_mat.entry[0][0]);

			// Z > max(X, Y)
			if (Z > *(ptr + 4 * argmax))
				argmax = 2i64;

			uint32_t ind2 = next[argmax];
			uint32_t ind3 = next[ind2];
			float    S = *(ptr + 4 * argmax) - *(ptr + 4 * ind2) - *(ptr + 4 * ind3);

			float* ans[3] = { &x, &y, &z };
			S = std::sqrt(S + 1.0f);

			*ans[argmax] = S * 0.5f;
			S = 0.5f / S;
			w = (*(ptr + 3 * ind3 + ind2) - *(ptr + 3 * ind2 + ind3)) * S;
			*ans[ind2] =
				(*(ptr + 3 * argmax + ind2) + *(ptr + 3 * ind2 + argmax)) *
				S;
			*ans[ind3] =
				(*(ptr + 3 * argmax + ind3) + *(ptr + 3 * ind3 + argmax)) *
				S;
		} else {
			float S = std::sqrt(Tr + 1.0f);
			w = S * 0.5f;
			S = 0.5f / S;
			x = (a_mat.entry[2][1] - a_mat.entry[1][2]) * S;
			y = (a_mat.entry[0][2] - a_mat.entry[2][0]) * S;
			z = (a_mat.entry[1][0] - a_mat.entry[0][1]) * S;
		}
	}

	void NiQuaternion::SetEulerAnglesXYZ(float a_x, float a_y, float a_z)
	{
		float cos_x = std::cos(a_x * -0.5f);
		float cos_y = std::cos(a_y * 0.5f);
		float cos_z = std::cos(a_z * -0.5f);
		float sin_x = std::sin(a_x * -0.5f);
		float sin_y = std::sin(a_y * 0.5f);
		float sin_z = std::sin(a_z * -0.5f);

		w = sin_z * sin_y * sin_x + cos_z * cos_y * cos_x;
		x = cos_z * cos_y * sin_x - sin_z * sin_y * cos_x;
		y = sin_x * cos_y * sin_z + sin_y * cos_x * cos_z;
		z = cos_y * cos_x * sin_z - sin_y * sin_x * cos_z;
	}
}
