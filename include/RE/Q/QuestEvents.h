#pragma once

namespace RE
{
	enum class QuestEvent
	{
		kNone = static_cast<std::underlying_type_t<QuestEvent>>(-1),  // NONE
		kKillActor = 0,                                               // KILL
		kAssaultActor = 1,                                            // ASSU
		kChangeLocation = 2,                                          // CLOC
		kScript = 3,                                                  // SCPT
		kActorDialogue = 4,                                           // ADIA
		kActorHello = 5,                                              // AHEL
		kActivateActor = 6,                                           // AFAV
		kPlayerAddItem = 7,                                           // AIPL
		kPlayerRemoveItem = 8,                                        // REMP
		kCraftItem = 9,                                               // CRFT
		kPickLock = 10,                                               // LOCK
		kInfection = 11,                                              // INFC
		kCure = 12,                                                   // CURE
		kNewVoicePower = 13,                                          // NVPE
		kDeadBody = 14,                                               // DEAD
		kSkillIncrease = 15,                                          // SKIL
		kIncreaseLevel = 16,                                          // LEVL
		kChangeRelationshipRank = 17,                                 // CHBR
		kIntimidateNPC = 18,                                          // INTM
		kBribeNPC = 19,                                               // BRIB
		kFlatterNPC = 20,                                             // FLAT
		kPlayerGetsFavor = 21,                                        // PRFV
		kPayFine = 22,                                                // PFIN
		kJail = 23,                                                   // JAIL
		kServedTime = 24,                                             // STIJ
		kEscapeJail = 25,                                             // ESIA
		kTrespass = 26,                                               // TRES
		kCrimeGold = 27,                                              // ADCR
		kArrest = 28,                                                 // ARRT
		kCastMagic = 29                                               // CAST
	};
}
