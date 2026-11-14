#include "RE/B/BleedoutCameraState.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void BleedoutCameraState::Unk_03()
	{
		// VR-only function at vtable slot 0x03
		if (REL::Module::IsVR()) {
			REL::RelocateVirtual<decltype(&BleedoutCameraState::Unk_03)>(0x03, 0x03, this);
		}
		// SE/AE: no-op, this function should never be called
	}
#endif
}