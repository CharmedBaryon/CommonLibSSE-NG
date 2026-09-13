#include "RE/P/PlayerCamera.h"
#include "RE/M/Main.h"
#include "RE/N/NiAVObject.h"
#include "RE/N/NiNode.h"
#include "RE/S/SceneGraph.h"

namespace RE
{
	PlayerCamera* PlayerCamera::GetSingleton()
	{
		static REL::Relocation<PlayerCamera**> singleton{ RELOCATION_ID(514642, 400802) };
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

	void PlayerCamera::PushCameraState(CameraState a_state)
	{
		using func_t = decltype(&PlayerCamera::PushCameraState);
		static REL::Relocation<func_t> func{ RELOCATION_ID(49947, 50880) };
		func(this, a_state);
	}

	bool PlayerCamera::QCameraEquals(CameraState a_cameraState) const
	{
		if (!REL::Module::IsVR()) {
			return currentState && currentState == GetRuntimeData().cameraStates[a_cameraState];
		}
		auto* vrData = GetVRRuntimeData();
		return vrData && currentState && currentState == vrData->cameraStates[a_cameraState];
	}

	void PlayerCamera::ToggleFreeCameraMode(bool a_freezeTime)
	{
		using func_t = decltype(&PlayerCamera::ToggleFreeCameraMode);
		static REL::Relocation<func_t> func{ RELOCATION_ID(49876, 50809) };
		func(this, a_freezeTime);
	}

	void PlayerCamera::Update()
	{
		using func_t = decltype(&PlayerCamera::Update);
		static REL::Relocation<func_t> func{ RELOCATION_ID(49852, 50784) };
		func(this);
	}

	void PlayerCamera::UpdateThirdPerson(bool a_weaponDrawn)
	{
		using func_t = decltype(&PlayerCamera::UpdateThirdPerson);
		static REL::Relocation<func_t> func{ RELOCATION_ID(49908, 50841) };
		func(this, a_weaponDrawn);
	}

	NiPoint3 PlayerCamera::GetActiveCameraPosition()
	{
		if (REL::Module::IsVR()) {
			if (auto worldRoot = RE::Main::WorldRootNode(); worldRoot && !worldRoot->GetChildren().empty()) {
				if (auto frontNode = worldRoot->GetChildren().front()) {
					return frontNode->world.translate;
				}
			}
		}
		if (auto pcCamera = PlayerCamera::GetSingleton(); pcCamera && pcCamera->cameraRoot) {
			return pcCamera->cameraRoot->world.translate;
		}
		return NiPoint3::Zero();
	}

	bool PlayerCamera::CheckCameraCollision(NiPoint3& a_pos, bool a_fadeCharacter)
	{
		using func_t = decltype(&PlayerCamera::CheckCameraCollision);
		static REL::Relocation<func_t> func{ RELOCATION_ID(49899, 50832) };
		return func(this, a_pos, a_fadeCharacter);
	}

	void PlayerCamera::UpdateYaw()
	{
		if (REL::Module::IsVR()) {
			using func_t = decltype(&PlayerCamera::UpdateYaw);
			static REL::Relocation<func_t> func{ REL::VariantID(0, 0, 0x876450) };
			func(this);
		}
	}
}
