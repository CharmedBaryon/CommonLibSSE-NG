#include "RE/B/BSGeometry.h"
#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	BSMultiIndexTriShape* BSGeometry::AsMultiIndexTriShape()
	{
		return REL::RelocateVirtual<decltype(&BSGeometry::AsMultiIndexTriShape)>(0x35, 0x36, this);
	}

	BSSkinnedDecalTriShape* BSGeometry::AsSkinnedDecalTriShape()
	{
		return REL::RelocateVirtual<decltype(&BSGeometry::AsSkinnedDecalTriShape)>(0x36, 0x37, this);
	}

	std::uint32_t BSGeometry::GetVisibleGroupsTriangleCount()
	{
		return REL::RelocateVirtual<decltype(&BSGeometry::GetVisibleGroupsTriangleCount)>(0x37, 0x38, this);
	}
#endif
}