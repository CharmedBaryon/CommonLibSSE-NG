#include "RE/B/BSInvMarker.h"
#include "RE/N/NiMath.h"

namespace RE
{
	NiPoint3 BSInvMarker::GetRotationEulerAnglesXYZ() const
	{
		return {
			fixed_range_to_radians(rotationX),
			fixed_range_to_radians(rotationY),
			fixed_range_to_radians(rotationZ)
		};
	}
}
