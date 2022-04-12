#include "RE/N/NiGeometry.h"

using namespace REL;

namespace RE
{
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

	std::uint16_t NiGeometry::Unk_3B(bool unk1)
	{
		return RelocateVirtual<decltype(&NiGeometry::Unk_3B)>(0x3B, 0x3C, this, unk1);
	}
}
