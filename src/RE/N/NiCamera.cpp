#include "RE/N/NiCamera.h"

namespace RE
{
	bool NiCamera::BoundInFrustum(const NiBound& a_bound, NiCamera* a_camera)
	{
		using func_t = decltype(&NiCamera::BoundInFrustum);
		static REL::Relocation<func_t> func{ RELOCATION_ID(15671, 15899) };
		return func(a_bound, a_camera);
	}

	bool NiCamera::NodeInFrustum(NiAVObject* a_node, NiCamera* a_camera)
	{
		if (!a_node) {
			return false;
		}

		return BoundInFrustum(a_node->worldBound, a_camera);
	}

	bool NiCamera::PointInFrustum(const NiPoint3& a_point, NiCamera* a_camera, float a_radius)
	{
		if (!a_camera) {
			return false;
		}

		const NiBound bound{ a_point, a_radius };
		return BoundInFrustum(bound, a_camera);
	}

	bool NiCamera::WindowPointToRay(std::int32_t a_x, std::int32_t a_y, NiPoint3& a_origin, NiPoint3& a_dir, float a_windowWidth, float a_windowHeight)
	{
		using func_t = decltype(&NiCamera::WindowPointToRay);
		static REL::Relocation<func_t> func{ RELOCATION_ID(69263, 70630) };
		return func(this, a_x, a_y, a_origin, a_dir, a_windowWidth, a_windowHeight);
	}

	bool NiCamera::WorldPtToScreenPt3(const NiPoint3& a_point, float& a_xOut, float& a_yOut, float& a_zOut, float a_zeroTolerance)
	{
		return WorldPtToScreenPt3(GetRuntimeData().worldToCam, GetRuntimeData2().port, a_point, a_xOut, a_yOut, a_zOut, a_zeroTolerance);
	}

	bool NiCamera::WorldPtToScreenPt3(const float a_matrix[4][4], const NiRect<float>& a_port, const NiPoint3& a_point, float& a_xOut, float& a_yOut, float& a_zOut, float a_zeroTolerance)
	{
		using func_t = bool (*)(const float[4][4], const NiRect<float>&, const NiPoint3&, float&, float&, float&, float);
		static REL::Relocation<func_t> func{ RELOCATION_ID(69270, 70640) };
		return func(a_matrix, a_port, a_point, a_xOut, a_yOut, a_zOut, a_zeroTolerance);
	}
}
