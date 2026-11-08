#include "RE/G/GMatrix2D.h"

#include "RE/G/GPoint.h"
#include "RE/G/GRect.h"

namespace RE
{
	GMatrix2D::GMatrix2D()
	{
		SetIdentity();
	}

	GMatrix2D::GMatrix2D(float a_v0, float a_v1, float a_v2, float a_v3, float a_v4, float a_v5)
	{
		SetMatrix(a_v0, a_v1, a_v2, a_v3, a_v4, a_v5);
	}

	GMatrix2D GMatrix2D::Translation(float a_dx, float a_dy)
	{
		return GMatrix2D(1.0f, 0.0f, 0.0f, 1.0f, a_dx, a_dy);
	}

	GMatrix2D GMatrix2D::Rotation(float a_radians)
	{
		float cosa = std::cosf(a_radians);
		float sina = std::sinf(a_radians);
		return GMatrix2D(cosa, -sina, sina, cosa, 0.0f, 0.0f);
	}

	GMatrix2D GMatrix2D::Scaling(float a_scale)
	{
		return GMatrix2D(a_scale, 0.0f, 0.0f, a_scale, 0.0f, 0.0f);
	}

	GMatrix2D& GMatrix2D::operator=(const GMatrix2D& a_rhs)
	{
		for (std::size_t i = 0; i < std::extent<decltype(data), 0>::value; ++i) {
			for (std::size_t j = 0; j < std::extent<decltype(data), 1>::value; ++j) {
				data[i][j] = a_rhs.data[i][j];
			}
		}
		return *this;
	}

	GMatrix2D& GMatrix2D::operator*=(const GMatrix2D& a_rhs)
	{
		Prepend(a_rhs);
		return *this;
	}

	GMatrix2D operator*(const GMatrix2D& a_lhs, const GMatrix2D& a_rhs)
	{
		GMatrix2D result = a_lhs;
		result.Prepend(a_rhs);
		return result;
	}

	void GMatrix2D::Append(const GMatrix2D& a_matrix)
	{
		GMatrix2D t = *this;
		data[0][0] = a_matrix.data[0][0] * t.data[0][0] + a_matrix.data[0][1] * t.data[1][0];
		data[1][0] = a_matrix.data[1][0] * t.data[0][0] + a_matrix.data[1][1] * t.data[1][0];
		data[0][1] = a_matrix.data[0][0] * t.data[0][1] + a_matrix.data[0][1] * t.data[1][1];
		data[1][1] = a_matrix.data[1][0] * t.data[0][1] + a_matrix.data[1][1] * t.data[1][1];
		data[0][2] = a_matrix.data[0][0] * t.data[0][2] + a_matrix.data[0][1] * t.data[1][2] + a_matrix.data[0][2];
		data[1][2] = a_matrix.data[1][0] * t.data[0][2] + a_matrix.data[1][1] * t.data[1][2] + a_matrix.data[1][2];
	}

	GRectF GMatrix2D::EncloseTransform(const GRectF& a_rect) const
	{
		// Get the transformed bounding box.
		const auto p0 = Transform(GPointF{ a_rect.left, a_rect.top });
		const auto p1 = Transform(GPointF{ a_rect.right, a_rect.top });
		const auto p2 = Transform(GPointF{ a_rect.right, a_rect.bottom });
		const auto p3 = Transform(GPointF{ a_rect.left, a_rect.bottom });

		GRectF result;
		result.SetRect(p0, p0);
		result.ExpandToPoint(p1);
		result.ExpandToPoint(p2);
		result.ExpandToPoint(p3);
		return result;
	}

	float GMatrix2D::GetDeterminant() const
	{
		return data[0][0] * data[1][1] - data[1][0] * data[0][1];
	}

	float GMatrix2D::GetXScale() const
	{
		return std::sqrt(data[0][0] * data[0][0] + data[1][0] * data[1][0]);
	}

	float GMatrix2D::GetYScale() const
	{
		return std::sqrt(data[1][1] * data[1][1] + data[0][1] * data[0][1]);
	}

	float GMatrix2D::GetRotation() const
	{
		return std::atan2(data[1][0], data[0][0]);
	}

	float GMatrix2D::GetMaxScale() const
	{
		return std::sqrt(std::max(data[0][0] * data[0][0] + data[1][0] * data[1][0], data[0][1] * data[0][1] + data[1][1] * data[1][1]));
	}

	GMatrix2D GMatrix2D::GetInverse() const
	{
		GMatrix2D result;
		result.SetInverse(*this);
		return result;
	}

	void GMatrix2D::Prepend(const GMatrix2D& a_matrix)
	{
		GMatrix2D t = *this;
		data[0][0] = t.data[0][0] * a_matrix.data[0][0] + t.data[0][1] * a_matrix.data[1][0];
		data[1][0] = t.data[1][0] * a_matrix.data[0][0] + t.data[1][1] * a_matrix.data[1][0];
		data[0][1] = t.data[0][0] * a_matrix.data[0][1] + t.data[0][1] * a_matrix.data[1][1];
		data[1][1] = t.data[1][0] * a_matrix.data[0][1] + t.data[1][1] * a_matrix.data[1][1];
		data[0][2] = t.data[0][0] * a_matrix.data[0][2] + t.data[0][1] * a_matrix.data[1][2] + t.data[0][2];
		data[1][2] = t.data[1][0] * a_matrix.data[0][2] + t.data[1][1] * a_matrix.data[1][2] + t.data[1][2];
	}

	void GMatrix2D::SetMatrix(const GMatrix2D& a_matrix)
	{
		data[0][0] = a_matrix.data[0][0];
		data[0][1] = a_matrix.data[0][1];
		data[0][2] = a_matrix.data[0][2];
		data[1][0] = a_matrix.data[1][0];
		data[1][1] = a_matrix.data[1][1];
		data[1][2] = a_matrix.data[1][2];
	}

	void GMatrix2D::SetMatrix(float a_v0, float a_v1, float a_v2, float a_v3, float a_v4, float a_v5)
	{
		data[0][0] = a_v0;
		data[0][1] = a_v1;
		data[0][2] = a_v4;
		data[1][0] = a_v2;
		data[1][1] = a_v3;
		data[1][2] = a_v5;
	}

	void GMatrix2D::SetIdentity()
	{
		data[0][0] = 1.0f;
		data[0][1] = 0.0f;
		data[0][2] = 0.0f;
		data[1][0] = 0.0f;
		data[1][1] = 1.0f;
		data[1][2] = 0.0f;
	}

	void GMatrix2D::SetInverse(const GMatrix2D& a_matrix)
	{
		// Invert the rotation part.
		float det = a_matrix.GetDeterminant();
		if (det == 0.0f) {
			SetIdentity();
			data[0][2] = -a_matrix.data[0][2];
			data[1][2] = -a_matrix.data[1][2];
		} else {
			float invDet = 1.0f / det;
			data[0][0] = a_matrix.data[1][1] * invDet;
			data[1][1] = a_matrix.data[0][0] * invDet;
			data[0][1] = -a_matrix.data[0][1] * invDet;
			data[1][0] = -a_matrix.data[1][0] * invDet;

			data[0][2] = -(data[0][0] * a_matrix.data[0][2] + data[0][1] * a_matrix.data[1][2]);
			data[1][2] = -(data[1][0] * a_matrix.data[0][2] + data[1][1] * a_matrix.data[1][2]);
		}
	}

	GPointF GMatrix2D::Transform(const GPointF& point) const
	{
		return {
			data[0][0] * point.x + data[0][1] * point.y + data[0][2],
			data[1][0] * point.x + data[1][1] * point.y + data[1][2]
		};
	}
}
