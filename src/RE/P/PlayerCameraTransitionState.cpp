#include "RE/P/PlayerCameraTransitionState.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void PlayerCameraTransitionState::Unk_03()
	{
		// VR-only function at vtable slot 0x03
		if (REL::Module::IsVR()) {
			REL::RelocateVirtual<decltype(&PlayerCameraTransitionState::Unk_03)>(0x03, 0x03, this);
		}
		// SE/AE: no-op, this function should never be called
	}

	void PlayerCameraTransitionState::Update(BSTSmartPointer<TESCameraState>& a_nextState)
	{
		REL::RelocateVirtual<decltype(&PlayerCameraTransitionState::Update)>(0x03, 0x04, this, a_nextState);
	}

	void PlayerCameraTransitionState::GetRotation(NiQuaternion& a_rotation)
	{
		REL::RelocateVirtual<decltype(&PlayerCameraTransitionState::GetRotation)>(0x04, 0x05, this, a_rotation);
	}

	void PlayerCameraTransitionState::GetTranslation(NiPoint3& a_translation)
	{
		REL::RelocateVirtual<decltype(&PlayerCameraTransitionState::GetTranslation)>(0x05, 0x06, this, a_translation);
	}
#endif
}