#include "RE/T/TweenMenuCameraState.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void TweenMenuCameraState::Unk_03()
	{
		// VR-only function at vtable slot 0x03
		if (REL::Module::IsVR()) {
			REL::RelocateVirtual<decltype(&TweenMenuCameraState::Unk_03)>(0x03, 0x03, this);
		}
		// SE/AE: no-op, this function should never be called
	}

	void TweenMenuCameraState::Update(BSTSmartPointer<TESCameraState>& a_nextState)
	{
		REL::RelocateVirtual<decltype(&TweenMenuCameraState::Update)>(0x03, 0x04, this, a_nextState);
	}

	void TweenMenuCameraState::GetRotation(NiQuaternion& a_rotation)
	{
		REL::RelocateVirtual<decltype(&TweenMenuCameraState::GetRotation)>(0x04, 0x05, this, a_rotation);
	}

	void TweenMenuCameraState::GetTranslation(NiPoint3& a_translation)
	{
		REL::RelocateVirtual<decltype(&TweenMenuCameraState::GetTranslation)>(0x05, 0x06, this, a_translation);
	}
#endif
}