#include "RE/T/TESCameraState.h"

#include "REL/Relocation.h"

using namespace REL;

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void TESCameraState::Unk_03()
	{
		// VR-only function at vtable slot 0x03
		if (REL::Module::IsVR()) {
			REL::RelocateVirtual<decltype(&TESCameraState::Unk_03)>(0x03, 0x03, this);
		}
		// SE/AE: no-op, this function should never be called
	}

	void TESCameraState::Update(BSTSmartPointer<TESCameraState>& a_nextState)
	{
		REL::RelocateVirtual<decltype(&TESCameraState::Update)>(0x03, 0x04, this, a_nextState);
	}

	void TESCameraState::GetRotation(NiQuaternion& a_rotation)
	{
		REL::RelocateVirtual<decltype(&TESCameraState::GetRotation)>(0x04, 0x05, this, a_rotation);
	}

	void TESCameraState::GetTranslation(NiPoint3& a_translation)
	{
		REL::RelocateVirtual<decltype(&TESCameraState::GetTranslation)>(0x05, 0x06, this, a_translation);
	}

	void TESCameraState::SaveGame(BGSSaveFormBuffer* a_buf)
	{
		REL::RelocateVirtual<decltype(&TESCameraState::SaveGame)>(0x06, 0x07, this, a_buf);
	}

	void TESCameraState::LoadGame(BGSLoadFormBuffer* a_buf)
	{
		REL::RelocateVirtual<decltype(&TESCameraState::LoadGame)>(0x07, 0x08, this, a_buf);
	}

	void TESCameraState::Revert(BGSLoadFormBuffer* a_buf)
	{
		REL::RelocateVirtual<decltype(&TESCameraState::Revert)>(0x08, 0x09, this, a_buf);
	}
#endif
}
