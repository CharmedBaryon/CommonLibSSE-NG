#pragma once

#include "RE/G/GPoint.h"
#include "RE/G/GRect.h"

namespace RE
{
	class GMatrix2D
	{
	public:
		GMatrix2D();
		GMatrix2D(float a_v0, float a_v1, float a_v2, float a_v3, float a_v4, float a_v5);
		GMatrix2D(const GMatrix2D&) = default;

		static GMatrix2D Translation(float a_dx, float a_dy);
		static GMatrix2D Rotation(float a_radians);
		static GMatrix2D Scaling(float a_scale);

		GMatrix2D& Append(const GMatrix2D& a_matrix);
		GRectF     EncloseTransform(const GRectF& a_rect) const;
		float      GetDeterminant() const;
		double     GetXScale() const;
		double     GetYScale() const;
		double     GetRotation() const;
		float      GetMaxScale() const;
		GMatrix2D  GetInverse() const;
		GMatrix2D& Prepend(const GMatrix2D& a_matrix);
		void       SetMatrix(const GMatrix2D& a_matrix);
		void       SetMatrix(float a_v0, float a_v1, float a_v2, float a_v3, float a_v4, float a_v5);
		void       SetIdentity();
		void       SetInverse(const GMatrix2D& a_matrix);
		GPointF    Transform(const GPointF& a_point) const;

		GMatrix2D& operator=(const GMatrix2D& a_rhs);
		GMatrix2D& operator*=(const GMatrix2D& a_rhs);

		friend GMatrix2D operator*(const GMatrix2D& a_lhs, const GMatrix2D& a_rhs);

		// members
		float data[2][3];  // 00
	};
	static_assert(sizeof(GMatrix2D) == 0x18);
}
