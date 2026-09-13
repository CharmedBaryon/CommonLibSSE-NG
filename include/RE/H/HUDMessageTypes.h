#pragma once

namespace RE
{
	enum class HUD_MESSAGE_TYPE
	{
		kNone = 0,
		kNotification = 1,
		kSetCrosshairTarget = 2,
		kSetCrosshairTargetTextOnly = 3,
		kSetLoadDoorInfo = 4,
#ifdef ENABLE_SKYRIM_VR
		// VR-only message types
		kSetCrosshairTargetGamepad = 5,
		kSetCrosshairTargetLeft = 6,
		kSetCrosshairTargetRight = 7,
#endif
		// Canonical SE/AE values (do not shift)
		kShowSubtitle = 5,
		kHideSubtitle = 6,
		kShowArrowCount = 7,
		kHeartBeat = 8,
		kSetSubtitlesEnabled = 9,
		kSetBlinking = 11,
		kSetFadeOut = 12,
		kSetPct = 13,
		kQuestStarted = 14,
		kQuestComplete = 15,
		kQuestFailed = 16,
		kObjectiveStarted = 17,
		kObjectiveComplete = 18,
		kObjectiveFailed = 19,
		kSkillIncrease = 20,
		kWordOfPowerLearned = 21,
		kDragonSoulAbsorbed = 22,
		kSetMode = 23,
		kCrosshairSneak = 24,
		kUnk25 = 25,
		kLocationDiscovery = 26,
		kFavor = 27,
		kValidateCrosshair = 28,
		kShowLocationName = 29,
		kShowHintText = 30,
		kSetCrosshairEnabled = 31,
		kSetDisplayInfo = 32,
		kRefreshActivateButtonArt = 33,
		kRefreshAll = 34,
		kSurvival = 35,
	};

#ifdef ENABLE_SKYRIM_VR
	// Runtime accessor for shifted values (SE/AE/VR)
	// For values >= kShowSubtitle, this will return the correct value for VR or SE/AE
	inline HUD_MESSAGE_TYPE GetHUDMessageType(HUD_MESSAGE_TYPE seValue)
	{
		if (REL::Module::IsVR()) {
			// VR: values after kSetLoadDoorInfo are shifted by 3
			int val = static_cast<int>(seValue);
			if (val >= static_cast<int>(HUD_MESSAGE_TYPE::kShowSubtitle)) {
				val += 3;
			}
			return static_cast<HUD_MESSAGE_TYPE>(val);
		}
		// SE/AE: no shift
		return seValue;
	}
#endif
}
