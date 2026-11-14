#include "RE/D/DragonCameraState.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void DragonCameraState::Unk_03()
	{
		// VR-only function at vtable slot 0x03
		if (REL::Module::IsVR()) {
			REL::RelocateVirtual<decltype(&DragonCameraState::Unk_03)>(0x03, 0x03, this);
		}
		// SE/AE: no-op, this function should never be called
	}

	void DragonCameraState::SetCameraHandle(RefHandle& a_handle)
	{
		REL::RelocateVirtual<decltype(&DragonCameraState::SetCameraHandle)>(0x09, 0x0A, this, a_handle);
	}

	void DragonCameraState::Unk_0A(void)
	{
		REL::RelocateVirtual<decltype(&DragonCameraState::Unk_0A)>(0x0A, 0x0B, this);
	}

	void DragonCameraState::ProcessWeaponDrawnChange(bool a_drawn)
	{
		REL::RelocateVirtual<decltype(&DragonCameraState::ProcessWeaponDrawnChange)>(0x0B, 0x0C, this, a_drawn);
	}

	bool DragonCameraState::GetFreeRotationMode() const
	{
		return REL::RelocateVirtual<decltype(&DragonCameraState::GetFreeRotationMode)>(0x0C, 0x0D, this);
	}

	void DragonCameraState::SetFreeRotationMode(bool a_weaponSheathed)
	{
		REL::RelocateVirtual<decltype(&DragonCameraState::SetFreeRotationMode)>(0x0D, 0x0E, this, a_weaponSheathed);
	}

	void DragonCameraState::UpdateRotation()
	{
		REL::RelocateVirtual<decltype(&DragonCameraState::UpdateRotation)>(0x0E, 0x0F, this);
	}

	void DragonCameraState::HandleLookInput(const NiPoint2& a_input)
	{
		REL::RelocateVirtual<decltype(&DragonCameraState::HandleLookInput)>(0x0F, 0x10, this, a_input);
	}
#endif
}
