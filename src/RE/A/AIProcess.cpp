#include "RE/A/AIProcess.h"

#include "RE/B/BipedAnim.h"
#include "RE/F/FixedStrings.h"
#include "RE/F/FormTraits.h"
#include "RE/H/HighProcessData.h"
#include "RE/M/MiddleHighProcessData.h"
#include "RE/N/NiAVObject.h"
#include "SKSE/API.h"

namespace RE
{
	void AIProcess::ClearActionHeadtrackTarget(bool a_defaultHold)
	{
		if (high) {
			high->ClearHeadtrackTarget(HighProcessData::HEAD_TRACK_TYPE::kAction, a_defaultHold);
		}
	}

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

	TESShout* AIProcess::GetCurrentShout()
	{
		return high ? high->currentShout : nullptr;
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

	NiAVObject* AIProcess::GetMagicNode(const BSTSmartPointer<BipedAnim>& a_biped) const
	{
		if (middleHigh && a_biped) {
			return a_biped->root->GetObjectByName(FixedStrings::GetSingleton()->npcRMagicNode);
		}
		return nullptr;
	}

	NiAVObject* AIProcess::GetWeaponNode(const BSTSmartPointer<BipedAnim>& a_biped) const
	{
		if (middleHigh) {
			if (a_biped) {
				return a_biped->root->GetObjectByName(FixedStrings::GetSingleton()->weapon);
			} else {
				return middleHigh->unk148;
			}
		} else {
			return nullptr;
		}
	}

	ObjectRefHandle AIProcess::GetOccupiedFurniture() const
	{
		if (middleHigh) {
			return middleHigh->occupiedFurniture;
		} else {
			return {};
		}
	}

	float AIProcess::GetRegenDelay(ActorValue a_actorValue) const
	{
		if (high) {
			switch (a_actorValue) {
			case ActorValue::kHealth:
				return high->healthRegenDelay;
			case ActorValue::kMagicka:
				return high->magickaRegenDelay;
			case ActorValue::kStamina:
				return high->staminaRegenDelay;
			default:
				break;
			}
		}
		return 0.0f;
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
#ifdef ENABLE_SKYRIM_VR
	void AIProcess::SetActorRefraction(float a_refraction)
	{
		using func_t = decltype(&AIProcess::SetActorRefraction);
		REL::Relocation<func_t> func{ REL::ID(5375528368) };
		return func(this, a_refraction);
	}
#endif

	void AIProcess::KnockExplosion(Actor* a_actor, const NiPoint3& a_location, float a_magnitude)
	{
		using func_t = decltype(&AIProcess::KnockExplosion);
		REL::Relocation<func_t> func{ RELOCATION_ID(38858, 39895) };
		return func(this, a_actor, a_location, a_magnitude);
	}

	bool AIProcess::PlayIdle(Actor* a_actor, TESIdleForm* a_idle, TESObjectREFR* a_target)
	{
		return SetupSpecialIdle(a_actor, DEFAULT_OBJECT::kActionIdle, a_idle, true, false, a_target);
	}

	void AIProcess::SetActorsDetectionEvent(Actor* a_actor, const NiPoint3& a_location, std::int32_t a_soundLevel, TESObjectREFR* a_ref)
	{
		using func_t = decltype(&AIProcess::SetActorsDetectionEvent);
		REL::Relocation<func_t> func{ RELOCATION_ID(38311, 39286) };
		return func(this, a_actor, a_location, a_soundLevel, a_ref);
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

	void AIProcess::SetRefraction(float a_refraction)
	{
		if (middleHigh) {
			middleHigh->scriptRefractPower = a_refraction;
		}
	}

	void AIProcess::Set3DUpdateFlag(RESET_3D_FLAGS a_flags)
	{
		if (middleHigh) {
			middleHigh->update3DModel.set(a_flags);
		}
	}

	bool AIProcess::SetupSpecialIdle(Actor* a_actor, DEFAULT_OBJECT a_action, TESIdleForm* a_idle, bool a_arg5, bool a_arg6, TESObjectREFR* a_target)
	{
		using func_t = decltype(&AIProcess::SetupSpecialIdle);
		REL::Relocation<func_t> func{ RELOCATION_ID(38290, 39256) };
		return func(this, a_actor, a_action, a_idle, a_arg5, a_arg6, a_target);
	}

	void AIProcess::StopCurrentIdle(Actor* a_actor, bool a_forceIdleStop)
	{
		using func_t = decltype(&AIProcess::StopCurrentIdle);
		REL::Relocation<func_t> func{ RELOCATION_ID(38291, 39257) };
		return func(this, a_actor, a_forceIdleStop);
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

	void AIProcess::UpdateRegenDelay(ActorValue a_actorValue, float a_regenDelay)
	{
		if (high) {
			switch (a_actorValue) {
			case ActorValue::kHealth:
				high->healthRegenDelay = a_regenDelay;
				break;
			case ActorValue::kMagicka:
				high->magickaRegenDelay = a_regenDelay;
				break;
			case ActorValue::kStamina:
				high->staminaRegenDelay = a_regenDelay;
				break;
			default:
				break;
			}
		}
	}
}
