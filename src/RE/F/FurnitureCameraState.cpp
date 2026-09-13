#include "RE/F/FurnitureCameraState.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void FurnitureCameraState::Unk_03()
	{
		// VR-only function at vtable slot 0x03
		if (REL::Module::IsVR()) {
			REL::RelocateVirtual<decltype(&FurnitureCameraState::Unk_03)>(0x03, 0x03, this);
		}
		// SE/AE: no-op, this function should never be called
	}

	void FurnitureCameraState::Update(BSTSmartPointer<TESCameraState>& a_nextState)
	{
		REL::RelocateVirtual<decltype(&FurnitureCameraState::Update)>(0x03, 0x04, this, a_nextState);
	}

	void FurnitureCameraState::GetRotation(NiQuaternion& a_rotation)
	{
		REL::RelocateVirtual<decltype(&FurnitureCameraState::GetRotation)>(0x04, 0x05, this, a_rotation);
	}

	void FurnitureCameraState::GetTranslation(NiPoint3& a_translation)
	{
		REL::RelocateVirtual<decltype(&FurnitureCameraState::GetTranslation)>(0x05, 0x06, this, a_translation);
	}

	void FurnitureCameraState::SaveGame(BGSSaveFormBuffer* a_buf)
	{
		REL::RelocateVirtual<decltype(&FurnitureCameraState::SaveGame)>(0x06, 0x07, this, a_buf);
	}

	void FurnitureCameraState::LoadGame(BGSLoadFormBuffer* a_buf)
	{
		REL::RelocateVirtual<decltype(&FurnitureCameraState::LoadGame)>(0x07, 0x08, this, a_buf);
	}

	void FurnitureCameraState::Revert(BGSLoadFormBuffer* a_buf)
	{
		REL::RelocateVirtual<decltype(&FurnitureCameraState::Revert)>(0x08, 0x09, this, a_buf);
	}
#endif
}