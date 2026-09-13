#include "RE/T/TESQuest.h"

#include "RE/B/BGSStoryTeller.h"
#include "SKSE/Logger.h"

namespace RE
{
	TESQuestStage::operator bool() const
	{
		return *reinterpret_cast<const std::uintptr_t*>(this) != 0;
	}

	ObjectRefHandle& TESQuestTarget::GetTargetRef(ObjectRefHandle& a_out, bool a_allowPickUpActor, const TESQuest* a_quest)
	{
		using func_t = decltype(&TESQuestTarget::GetTargetRef);
		static REL::Relocation<func_t> func{ RELOCATION_ID(24815, 25284) };
		return func(this, a_out, a_allowPickUpActor, a_quest);
	}

	ObjectRefHandle& TESQuestTarget::GetTrackingRef(ObjectRefHandle& a_out, const TESQuest* a_quest)
	{
		using func_t = decltype(&TESQuestTarget::GetTrackingRef);
		static REL::Relocation<func_t> func{ RELOCATION_ID(24816, 25285) };
		return func(this, a_out, a_quest);
	}

	bool TESQuest::EnsureQuestStarted(bool& a_result, bool a_startNow)
	{
		using func_t = decltype(&TESQuest::EnsureQuestStarted);
		static REL::Relocation<func_t> func{ RELOCATION_ID(24481, 25003) };
		return func(this, a_result, a_startNow);
	}

	void TESQuest::ForceRefIntoAlias(std::uint32_t a_aliasID, TESObjectREFR* a_ref)
	{
		using func_t = decltype(&TESQuest::ForceRefIntoAlias);
		static REL::Relocation<func_t> func{ RELOCATION_ID(24523, 25052) };
		return func(this, a_aliasID, a_ref);
	}

	ObjectRefHandle TESQuest::GetAliasedRef(std::uint32_t a_aliasID) const
	{
		BSReadLockGuard locker(aliasAccessLock);

		auto it = refAliasMap.find(a_aliasID);
		return it != refAliasMap.end() ? it->second : ObjectRefHandle();
	}

	std::uint16_t TESQuest::GetCurrentStageID() const
	{
		return currentStage;
	}

	void TESQuest::GetJournalTextForInstance(BSString& out, std::uint32_t instanceID)
	{
		using func_t = decltype(&TESQuest::GetJournalTextForInstance);
		static REL::Relocation<func_t> func{ RELOCATION_ID(24549, 25078) };
		return func(this, out, instanceID);
	}

	bool TESQuest::IsActive() const
	{
		return data.flags.all(QuestFlag::kActive);
	}

	bool TESQuest::IsCompleted() const
	{
		return data.flags.all(QuestFlag::kCompleted);
	}

	bool TESQuest::IsEnabled() const
	{
		return data.flags.all(QuestFlag::kEnabled);
	}

	bool TESQuest::IsRunning() const
	{
		return !IsStopping() && !promoteTask;
	}

	bool TESQuest::IsStarting() const
	{
		return IsEnabled() && (data.flags == QuestFlag::kStopStart || promoteTask);
	}

	bool TESQuest::IsStopped() const
	{
		return data.flags.none(QuestFlag::kEnabled, QuestFlag::kStageWait);
	}

	bool TESQuest::IsStopping() const
	{
		return !IsEnabled() && data.flags == QuestFlag::kStopStart;
	}

	void TESQuest::Reset()
	{
		using func_t = decltype(&TESQuest::Reset);
		static REL::Relocation<func_t> func{ RELOCATION_ID(24486, 25014) };
		return func(this);
	}

	void TESQuest::ResetAndUpdate()
	{
		Reset();

		auto enabled = IsEnabled();
		if (enabled != StartsEnabled()) {
			auto storyTeller = BGSStoryTeller::GetSingleton();
			if (storyTeller) {
				if (enabled) {
					storyTeller->BeginStartUpQuest(this);
				} else {
					storyTeller->BeginShutDownQuest(this);
				}
			}
		}
	}

	void TESQuest::SetEnabled(bool a_set)
	{
		if (a_set) {
			data.flags.set(QuestFlag::kEnabled);
		} else {
			data.flags.reset(QuestFlag::kEnabled);
		}
		AddChange(ChangeFlags::kQuestFlags);
	}

	bool TESQuest::Start()
	{
		if (eventID != QuestEvent::kNone) {
			SKSE::log::debug("Attempting to start event scoped quest outside of story manager");
			return false;
		}

		bool result;
		return EnsureQuestStarted(result, true);
	}

	bool TESQuest::StartsEnabled() const
	{
		return data.flags.all(QuestFlag::kStartsEnabled);
	}

	void TESQuest::Stop()
	{
		if (IsEnabled()) {
			SetEnabled(false);
		}
	}
}
