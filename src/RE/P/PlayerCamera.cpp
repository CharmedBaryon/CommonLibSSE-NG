#include "RE/P/PlayerCamera.h"

namespace RE
{
	PlayerCamera* PlayerCamera::GetSingleton()
	{
		REL::Relocation<PlayerCamera**> singleton{ RELOCATION_ID(514642, 400802) };
		return *singleton;
	}

	bool PlayerCamera::ForceFirstPerson()
	{
		if (REL::Module::IsVR()) {
			return false;
		}
		using func_t = decltype(&PlayerCamera::ForceFirstPerson);
		static REL::Relocation<func_t> func{ RELOCATION_ID(49858, 50790) };
		func(this);
		return true;
	}

	bool PlayerCamera::ForceThirdPerson()
	{
		if (REL::Module::IsVR()) {
			return false;
		}
		using func_t = decltype(&PlayerCamera::ForceThirdPerson);
		static REL::Relocation<func_t> func{ RELOCATION_ID(49863, 50796) };
		func(this);
		return true;
	}

	bool PlayerCamera::IsInBleedoutMode() const
	{
		return QCameraEquals((!REL::Module::IsVR() ? CameraState::kBleedout : CameraState::kVRBleedout));
	}

	bool PlayerCamera::IsInFirstPerson() const
	{
		return QCameraEquals(CameraState::kFirstPerson);
	}

	bool PlayerCamera::IsInFreeCameraMode() const
	{
		return QCameraEquals(CameraState::kFree);
	}

	bool PlayerCamera::IsInThirdPerson() const
	{
		return QCameraEquals((!REL::Module::IsVR() ? CameraState::kThirdPerson : CameraState::kVRThirdPerson));
	}

	bool PlayerCamera::QCameraEquals(CameraState a_cameraState) const
	{
		return currentState && currentState == (!REL::Module::IsVR() ? GetRuntimeData().cameraStates[a_cameraState] : GetVRRuntimeData().cameraStates[a_cameraState]);
	}

	void PlayerCamera::ToggleFreeCameraMode(bool a_freezeTime)
	{
		using func_t = decltype(&PlayerCamera::ToggleFreeCameraMode);
		static REL::Relocation<func_t> func{ RELOCATION_ID(49876, 50809) };
		return func(this, a_freezeTime);
	}

	void PlayerCamera::UpdateThirdPerson(bool a_weaponDrawn)
	{
		using func_t = decltype(&PlayerCamera::UpdateThirdPerson);
		static REL::Relocation<func_t> func{ RELOCATION_ID(49908, 50841) };
		return func(this, a_weaponDrawn);
	}
}
