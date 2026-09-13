#include "RE/A/AutoVanityState.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void AutoVanityState::Unk_03()
	{
		// VR-only function at vtable slot 0x03
		if (REL::Module::IsVR()) {
			REL::RelocateVirtual<decltype(&AutoVanityState::Unk_03)>(0x03, 0x03, this);
		}
		// SE/AE: no-op, this function should never be called
	}

	void AutoVanityState::Update(BSTSmartPointer<TESCameraState>& a_nextState)
	{
		REL::RelocateVirtual<decltype(&AutoVanityState::Update)>(0x03, 0x04, this, a_nextState);
	}

	void AutoVanityState::GetRotation(NiQuaternion& a_rotation)
	{
		REL::RelocateVirtual<decltype(&AutoVanityState::GetRotation)>(0x04, 0x05, this, a_rotation);
	}

	void AutoVanityState::GetTranslation(NiPoint3& a_translation)
	{
		REL::RelocateVirtual<decltype(&AutoVanityState::GetTranslation)>(0x05, 0x06, this, a_translation);
	}
#endif
}