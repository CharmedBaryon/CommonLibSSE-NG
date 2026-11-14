#include "RE/N/NiTriShape.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	std::uint16_t NiTriShape::Unk_3B(bool unk1)
	{
		if (REL::Module::IsVR()) {
			return REL::RelocateVirtual<decltype(&NiTriShape::Unk_3B)>(0, 0x3C, this, unk1);
		}
		// SE/AE: no such function
		return 0;
	}
#endif
}
