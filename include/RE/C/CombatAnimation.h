#pragma once

#include "RE/A/AnimationSystemUtils.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/T/TESActionData.h"

namespace RE
{
	class Actor;
	class BGSAction;
	class NiPoint3;

	class CombatAnimation : public TESActionData
	{
	public:
		virtual ~CombatAnimation() override;  // 00

		enum class ANIM : std::uint32_t
		{
			kActionRightAttack = 0,
			kActionRightRelease = 1,
			kActionRightPowerAttack = 2,
			kActionLeftAttack = 3,
			kActionLeftRelease = 4,
			kActionRightAttack2 = 5,   // ranged?
			kActionRightRelease2 = 6,  // ranged?
			kActionRightInterrupt = 7,
			kActionSneak = 8,
			kActionActivate = 9
		};

		enum class LoadedStatus : std::uint32_t
		{
			kNone = 0,     // Not loaded
			kSuccess = 1,  // Loaded successfully
			kFail = 2      // Failed to load
		};

		CombatAnimation* Ctor(Actor* a_actor, ANIM a_anim);
		CombatAnimation* Ctor(Actor* a_actor, TESObjectREFR* a_target, ANIM a_anim);
		CombatAnimation* Ctor(Actor* a_actor, BGSAction* a_action);

		static CombatAnimation* Create(Actor* a_actor, ANIM a_anim);
		static CombatAnimation* Create(Actor* a_actor, BGSAction* a_action);
		static bool             Execute(Actor* a_actor, ANIM a_anim);
		static bool             Execute(Actor* a_actor, TESObjectREFR* a_target, ANIM a_anim);

		bool  Check();
		bool  Execute();  // Wrapper around inherited Process() with additional logic
		bool  GetEventData(const BSFixedString& a_eventName, float& a_eventTime);
		bool  GetEventData(const BSFixedString& a_eventName, float& a_eventTime, NiPoint3& a_translation);
		float GetEventTime(const BSFixedString& a_eventName);
		float GetLength();
		bool  GetTranslation(NiPoint3& a_translation);
		bool  LoadClipData();

		// members
		BSScrapArray<AnimationSystemUtils::UtilsClipData> clipData;      // 60
		REX::EnumSet<LoadedStatus, std::int32_t>          loadedStatus;  // 80
		std::uint32_t                                     pad84;         // 84
	};
	static_assert(sizeof(CombatAnimation) == 0x88);
}
