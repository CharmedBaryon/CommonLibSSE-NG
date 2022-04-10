#include "RE/B/BSGeometry.h"
#include "REL/Relocation.h"

namespace RE
{
	BSMultiIndexTriShape* BSGeometry::AsMultiIndexTriShape()
	{
		return REL::RelocateVirtual<decltype(&BSGeometry::AsMultiIndexTriShape)>(0x35, 0x36, this);
	}

	BSSkinnedDecalTriShape* BSGeometry::AsSkinnedDecalTriShape()
	{
		return REL::RelocateVirtual<decltype(&BSGeometry::AsSkinnedDecalTriShape)>(0x36, 0x37, this);
	}

	void BSGeometry::Unk_37()
	{
		return REL::RelocateVirtual<decltype(&BSGeometry::Unk_37)>(0x37, 0x38, this);
	}
}