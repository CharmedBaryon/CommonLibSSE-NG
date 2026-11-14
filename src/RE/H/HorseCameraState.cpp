#include "RE/H/HorseCameraState.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void HorseCameraState::Unk_03()
	{
		// VR-only function at vtable slot 0x03
		if (REL::Module::IsVR()) {
			REL::RelocateVirtual<decltype(&HorseCameraState::Unk_03)>(0x03, 0x03, this);
		}
		// SE/AE: no-op, this function should never be called
	}

	void HorseCameraState::SetCameraHandle(RefHandle& a_handle)
	{
		REL::RelocateVirtual<decltype(&HorseCameraState::SetCameraHandle)>(0x09, 0x0A, this, a_handle);
	}

	void HorseCameraState::Unk_0A(void)
	{
		REL::RelocateVirtual<decltype(&HorseCameraState::Unk_0A)>(0x0A, 0x0B, this);
	}

	void HorseCameraState::ProcessWeaponDrawnChange(bool a_drawn)
	{
		REL::RelocateVirtual<decltype(&HorseCameraState::ProcessWeaponDrawnChange)>(0x0B, 0x0C, this, a_drawn);
	}

	bool HorseCameraState::GetFreeRotationMode() const
	{
		return REL::RelocateVirtual<decltype(&HorseCameraState::GetFreeRotationMode)>(0x0C, 0x0D, this);
	}

	void HorseCameraState::SetFreeRotationMode(bool a_weaponSheathed)
	{
		REL::RelocateVirtual<decltype(&HorseCameraState::SetFreeRotationMode)>(0x0D, 0x0E, this, a_weaponSheathed);
	}

	void HorseCameraState::HandleLookInput(const NiPoint2& a_input)
	{
		REL::RelocateVirtual<decltype(&HorseCameraState::HandleLookInput)>(0x0F, 0x10, this, a_input);
	}
#endif
}
