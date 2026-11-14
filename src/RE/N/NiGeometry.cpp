#include "RE/N/NiGeometry.h"

using namespace REL;

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void NiGeometry::Unk_35()
	{
		RelocateVirtual<decltype(&NiGeometry::Unk_35)>(0x35, 0x36, this);
	}

	void NiGeometry::Unk_36()
	{
		RelocateVirtual<decltype(&NiGeometry::Unk_36)>(0x36, 0x37, this);
	}

	void NiGeometry::Unk_37()
	{
		RelocateVirtual<decltype(&NiGeometry::Unk_37)>(0x37, 0x38, this);
	}

	void* NiGeometry::Unk_38()
	{
		return RelocateVirtual<decltype(&NiGeometry::Unk_38)>(0x38, 0x39, this);
	}

	void NiGeometry::SetGeometryData(NiGeometryData* unk1)
	{
		RelocateVirtual<decltype(&NiGeometry::SetGeometryData)>(0x39, 0x3A, this, unk1);
	}

	void* NiGeometry::Unk_3A()
	{
		return RelocateVirtual<decltype(&NiGeometry::Unk_3A)>(0x3A, 0x3B, this);
	}
#endif
}
