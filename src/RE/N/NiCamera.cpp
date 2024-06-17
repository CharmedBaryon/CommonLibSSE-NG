#include "RE/N/NiCamera.h"

namespace RE
{
	bool NiCamera::WorldPtToScreenPt3(const NiPoint3& a_point, float& a_xOut, float& a_yOut, float& a_zOut, float a_zeroTolerance)
	{
		return WorldPtToScreenPt3(GetRuntimeData().worldToCam, GetRuntimeData2().port, a_point, a_xOut, a_yOut, a_zOut, a_zeroTolerance);
	}

	bool NiCamera::BoundInFrustum(const NiBound& a_bound, NiCamera* a_camera)
	{
		using func_t = decltype(&BoundInFrustum);
		REL::Relocation<func_t> func{ RELOCATION_ID(15671, 15899) };
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

	bool NiCamera::WorldPtToScreenPt3(const float a_matrix[4][4], const NiRect<float>& a_port, const NiPoint3& a_point, float& a_xOut, float& a_yOut, float& a_zOut, float a_zeroTolerance)
	{
		using func_t = bool (*)(const float[4][4], const NiRect<float>&, const NiPoint3&, float&, float&, float&, float);
		REL::Relocation<func_t> func{ Offset::NiCamera::WorldPtToScreenPt3 };
		return func(a_matrix, a_port, a_point, a_xOut, a_yOut, a_zOut, a_zeroTolerance);
	}
}
