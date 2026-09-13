#include "RE/T/ThirdPersonState.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void ThirdPersonState::Unk_03()
	{
		// VR-only function at vtable slot 0x03
		if (REL::Module::IsVR()) {
			REL::RelocateVirtual<decltype(&ThirdPersonState::Unk_03)>(0x03, 0x03, this);
		}
		// SE/AE: no-op, this function should never be called
	}

	void ThirdPersonState::SetCameraHandle(RefHandle& a_handle)
	{
		REL::RelocateVirtual<decltype(&ThirdPersonState::SetCameraHandle)>(0x09, 0x0A, this, a_handle);
	}

	void ThirdPersonState::Unk_0A(void)
	{
		REL::RelocateVirtual<decltype(&ThirdPersonState::Unk_0A)>(0x0A, 0x0B, this);
	}

	void ThirdPersonState::ProcessWeaponDrawnChange(bool a_drawn)
	{
		REL::RelocateVirtual<decltype(&ThirdPersonState::ProcessWeaponDrawnChange)>(0x0B, 0x0C, this, a_drawn);
	}

	bool ThirdPersonState::GetFreeRotationMode() const
	{
		return REL::RelocateVirtual<decltype(&ThirdPersonState::GetFreeRotationMode)>(0x0C, 0x0D, this);
	}

	void ThirdPersonState::SetFreeRotationMode(bool a_weaponSheathed)
	{
		REL::RelocateVirtual<decltype(&ThirdPersonState::SetFreeRotationMode)>(0x0D, 0x0E, this, a_weaponSheathed);
	}

	void ThirdPersonState::UpdateRotation()
	{
		REL::RelocateVirtual<decltype(&ThirdPersonState::UpdateRotation)>(0x0E, 0x0F, this);
	}

	void ThirdPersonState::HandleLookInput(const NiPoint2& a_input)
	{
		REL::RelocateVirtual<decltype(&ThirdPersonState::HandleLookInput)>(0x0F, 0x10, this, a_input);
	}

	void ThirdPersonState::UpdateTranslation(float* a_rotationInput)
	{
		REL::RelocateVirtual<decltype(&ThirdPersonState::UpdateTranslation)>(0x10, 0x11, this, a_rotationInput);
	}
#endif

	void ThirdPersonState::ResetFreeRotation()
	{
		using func_t = decltype(&ThirdPersonState::ResetFreeRotation);
		static REL::Relocation<func_t> func{ RELOCATION_ID(49966, 50902) };
		func(this);
	}

	void ThirdPersonState::UpdateCameraCollision()
	{
		if (REL::Module::IsVR() || REL::Module::IsSE()) {
			using func_t = decltype(&ThirdPersonState::UpdateCameraCollision);
			static REL::Relocation<func_t> func{ RELOCATION_ID(49980, 0) };
			func(this);
		}
	}
}
