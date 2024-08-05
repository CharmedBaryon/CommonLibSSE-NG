#include "RE/P/ProcessLists.h"

#include "RE/A/Actor.h"
#include "RE/M/ModelReferenceEffect.h"
#include "RE/S/ShaderReferenceEffect.h"
#include "RE/T/TESObjectREFR.h"
#include "RE/T/TempEffectTraits.h"

namespace RE
{
	ProcessLists* ProcessLists::GetSingleton()
	{
		REL::Relocation<ProcessLists**> singleton{ RELOCATION_ID(514167, 400315) };
		return *singleton;
	}

	void ProcessLists::ClearCachedFactionFightReactions() const
	{
		using func_t = decltype(&ProcessLists::ClearCachedFactionFightReactions);
		static REL::Relocation<func_t> func{ RELOCATION_ID(40396, 41410) };
		return func(this);
	}

	void ProcessLists::ForAllActors(std::function<BSContainer::ForEachResult(Actor*)> a_callback)
	{
		for (auto& list : allProcesses) {
			if (list) {
				for (auto& actorHandle : *list) {
					const auto& actor = actorHandle.get();
					if (actor && a_callback(actor.get()) == BSContainer::ForEachResult::kStop) {
						return;
					}
				}
			}
		}
	}

	void ProcessLists::ForEachHighActor(std::function<BSContainer::ForEachResult(Actor*)> a_callback)
	{
		for (auto& highActorHandle : highActorHandles) {
			const auto& highActor = highActorHandle.get();
			if (highActor && a_callback(highActor.get()) == BSContainer::ForEachResult::kStop) {
				break;
			}
		}
	}

	void ProcessLists::ForEachMagicTempEffect(std::function<BSContainer::ForEachResult(BSTempEffect*)> a_callback)
	{
		BSSpinLockGuard locker(magicEffectsLock);

		for (auto& tempEffectPtr : magicEffects) {
			const auto& tempEffect = tempEffectPtr.get();
			if (tempEffect && a_callback(tempEffect) == BSContainer::ForEachResult::kStop) {
				break;
			}
		}
	}

	void ProcessLists::ForEachModelEffect(std::function<BSContainer::ForEachResult(ModelReferenceEffect*)> a_callback)
	{
		ForEachMagicTempEffect([a_callback](BSTempEffect* a_tempEffect) {
			const auto modelEffect = a_tempEffect->As<ModelReferenceEffect>();
			if (modelEffect && a_callback(modelEffect) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
			return BSContainer::ForEachResult::kContinue;
		});
	}

	void ProcessLists::ForEachShaderEffect(std::function<BSContainer::ForEachResult(ShaderReferenceEffect*)> a_callback)
	{
		ForEachMagicTempEffect([a_callback](BSTempEffect* a_tempEffect) {
			const auto shaderEffect = a_tempEffect->As<ShaderReferenceEffect>();
			if (shaderEffect && a_callback(shaderEffect) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
			return BSContainer::ForEachResult::kContinue;
		});
	}

	float ProcessLists::GetSystemTimeClock()
	{
		using func_t = decltype(&ProcessLists::GetSystemTimeClock);
		static REL::Relocation<func_t> func{ RELOCATION_ID(40327, 41337) };
		return func(this);
	}

	std::int16_t ProcessLists::RequestHighestDetectionLevelAgainstActor(Actor* a_actor, std::uint32_t& a_LOSCount)
	{
		using func_t = decltype(&ProcessLists::RequestHighestDetectionLevelAgainstActor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(40394, 41408) };
		return func(this, a_actor, a_LOSCount);
	}

	void ProcessLists::StopAllMagicEffects(TESObjectREFR& a_ref)
	{
		const auto handle = a_ref.CreateRefHandle();
		ForEachMagicTempEffect([&](BSTempEffect* a_tempEffect) {
			const auto referenceEffect = a_tempEffect->As<ReferenceEffect>();
			if (referenceEffect && referenceEffect->target == handle) {
				referenceEffect->finished = true;
			}
			return BSContainer::ForEachResult::kContinue;
		});
	}

	void ProcessLists::StopCombatAndAlarmOnActor(Actor* a_actor, bool a_notAlarm)
	{
		using func_t = decltype(&ProcessLists::StopCombatAndAlarmOnActor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(40330, 41340) };
		return func(this, a_actor, a_notAlarm);
	}
}
