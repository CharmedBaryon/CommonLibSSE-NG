#include "RE/B/BSOcclusionPlane.h"

namespace RE
{
	bool BSOcclusionPlane::WithinFrustumDistFirst(const NiFrustumPlanes* a_planes, const NiPoint3* a_point)
	{
		using func_t = decltype(&BSOcclusionPlane::WithinFrustumDistFirst);
		static REL::Relocation<func_t> func{ RELOCATION_ID(74702, 76436) };
		return func(this, a_planes, a_point);
	}
}
