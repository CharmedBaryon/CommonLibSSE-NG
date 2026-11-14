#include "RE/V/VATSCameraState.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void VATSCameraState::Unk_03()
	{
		// VR-only function at vtable slot 0x03
		if (REL::Module::IsVR()) {
			REL::RelocateVirtual<decltype(&VATSCameraState::Unk_03)>(0x03, 0x03, this);
		}
		// SE/AE: no-op, this function should never be called
	}

	void VATSCameraState::Update(BSTSmartPointer<TESCameraState>& a_nextState)
	{
		REL::RelocateVirtual<decltype(&VATSCameraState::Update)>(0x03, 0x04, this, a_nextState);
	}

	void VATSCameraState::GetRotation(NiQuaternion& a_rotation)
	{
		REL::RelocateVirtual<decltype(&VATSCameraState::GetRotation)>(0x04, 0x05, this, a_rotation);
	}

	void VATSCameraState::GetTranslation(NiPoint3& a_translation)
	{
		REL::RelocateVirtual<decltype(&VATSCameraState::GetTranslation)>(0x05, 0x06, this, a_translation);
	}

	void VATSCameraState::SaveGame(BGSSaveFormBuffer* a_buf)
	{
		REL::RelocateVirtual<decltype(&VATSCameraState::SaveGame)>(0x06, 0x07, this, a_buf);
	}

	void VATSCameraState::LoadGame(BGSLoadFormBuffer* a_buf)
	{
		REL::RelocateVirtual<decltype(&VATSCameraState::LoadGame)>(0x07, 0x08, this, a_buf);
	}

	void VATSCameraState::Revert(BGSLoadFormBuffer* a_buf)
	{
		REL::RelocateVirtual<decltype(&VATSCameraState::Revert)>(0x08, 0x09, this, a_buf);
	}
#endif
}