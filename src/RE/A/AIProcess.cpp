#include "RE/A/AIProcess.h"

#include "RE/F/FormTraits.h"
#include "RE/H/HighProcessData.h"
#include "RE/M/MiddleHighProcessData.h"
#include "RE/N/NiAVObject.h"
#include "SKSE/API.h"

namespace RE
{
	void AIProcess::ClearMuzzleFlashes()
	{
		using func_t = decltype(&AIProcess::ClearMuzzleFlashes);
		REL::Relocation<func_t> func{ RELOCATION_ID(38495, 39504) };
		return func(this);
	}

	float AIProcess::GetCachedHeight() const
	{
		return high ? high->cachedActorHeight : static_cast<float>(-1.0);
	}

	bhkCharacterController* AIProcess::GetCharController()
	{
		return middleHigh ? middleHigh->charController.get() : nullptr;
	}

	ActorHandle AIProcess::GetCommandingActor() const
	{
		return middleHigh ? middleHigh->commandingActor : ActorHandle{};
	}

	TESForm* AIProcess::GetEquippedLeftHand()
	{
		return equippedObjects[Hands::kLeft];
	}

	TESForm* AIProcess::GetEquippedRightHand()
	{
		return equippedObjects[Hands::kRight];
	}

	ObjectRefHandle AIProcess::GetHeadtrackTarget() const
	{
		using func_t = decltype(&AIProcess::GetHeadtrackTarget);
		REL::Relocation<func_t> func{ RELOCATION_ID(38483, 39484) };
		return func(this);
	}

	bool AIProcess::GetIsSummonedCreature() const noexcept
	{
		return middleHigh && middleHigh->summonedCreature;
	}

	ObjectRefHandle AIProcess::GetOccupiedFurniture() const
	{
		if (middleHigh) {
			return middleHigh->occupiedFurniture;
		} else {
			return {};
		}
	}

	TESPackage* AIProcess::GetRunningPackage() const
	{
		TESPackage* package = nullptr;
		if (middleHigh) {
			package = middleHigh->runOncePackage.package;
		}
		if (!package) {
			package = currentPackage.package;
		}
		return package;
	}

	Actor* AIProcess::GetUserData() const
	{
		const auto torsoNode = middleHigh ? middleHigh->torsoNode : nullptr;
		const auto userData = torsoNode ? torsoNode->GetUserData() : nullptr;

		return userData ? userData->As<Actor>() : nullptr;
	}

	float AIProcess::GetVoiceRecoveryTime() const
	{
		return high ? high->voiceRecoveryTime : 0.0f;
	}

	bool AIProcess::InHighProcess() const
	{
		switch (*processLevel) {
		case PROCESS_TYPE::kHigh:
			return true;
		default:
			return false;
		}
	}

	bool AIProcess::InMiddleHighProcess() const
	{
		switch (*processLevel) {
		case PROCESS_TYPE::kHigh:
		case PROCESS_TYPE::kMiddleHigh:
			return true;
		default:
			return false;
		}
	}

	bool AIProcess::InMiddleLowProcess() const
	{
		switch (*processLevel) {
		case PROCESS_TYPE::kHigh:
		case PROCESS_TYPE::kMiddleHigh:
		case PROCESS_TYPE::kMiddleLow:
			return true;
		default:
			return false;
		}
	}

	bool AIProcess::InLowProcess() const
	{
		switch (*processLevel) {
		case PROCESS_TYPE::kHigh:
		case PROCESS_TYPE::kMiddleHigh:
		case PROCESS_TYPE::kMiddleLow:
		case PROCESS_TYPE::kLow:
			return true;
		default:
			return false;
		}
	}

	bool AIProcess::IsArrested() const
	{
		return high && high->arrested;
	}

	bool AIProcess::IsGhost() const
	{
		return cachedValues && cachedValues->flags.all(CachedValues::Flags::kActorIsGhost);
	}

	void AIProcess::SetArrested(bool a_arrested)
	{
		if (high) {
			high->arrested = a_arrested;
		}
	}

	void AIProcess::SetCachedHeight(float a_height)
	{
		if (high) {
			high->cachedActorHeight = a_height;
		}
	}

	void AIProcess::SetHeadtrackTarget(Actor* a_owner, NiPoint3& a_targetPosition)
	{
		using func_t = decltype(&AIProcess::SetHeadtrackTarget);
		REL::Relocation<func_t> func{ RELOCATION_ID(38850, 39887) };
		return func(this, a_owner, a_targetPosition);
	}

	void AIProcess::Set3DUpdateFlag(RESET_3D_FLAGS a_flags)
	{
		if (middleHigh) {
			middleHigh->update3DModel.set(a_flags);
		}
	}

	void AIProcess::Update3DModel(Actor* a_actor)
	{
		Update3DModel_Impl(a_actor);
		const SKSE::NiNodeUpdateEvent event{ a_actor };
		auto                          source = SKSE::GetNiNodeUpdateEventSource();
		if (source) {
			source->SendEvent(std::addressof(event));
		}
	}

	void AIProcess::Update3DModel_Impl(Actor* a_actor)
	{
		using func_t = decltype(&AIProcess::Update3DModel_Impl);
		REL::Relocation<func_t> func{ Offset::AIProcess::Update3DModel };
		return func(this, a_actor);
	}
}
