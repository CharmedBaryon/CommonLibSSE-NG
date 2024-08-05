#pragma once

#include "RE/A/AITimeStamp.h"
#include "RE/A/AITimer.h"
#include "RE/B/BGSWorldLocation.h"
#include "RE/B/BSAtomic.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/C/CombatGroupDetectionListener.h"

namespace RE
{
	class BSPathingLOSGridMap;
	class CombatSearchLocation;

	class CombatTarget
	{
	public:
		enum class Flags
		{
			kNone = 0,
			kTargetKnown = 1 << 0,
			kTargetLost = 1 << 1
		};

		// members
		ActorHandle                            targetHandle;        // 00
		std::int32_t                           detectLevel;         // 04
		float                                  stealthPoints;       // 08
		float                                  unk0C;               // 0C
		BGSWorldLocation                       lastKnownLoc;        // 10
		BGSWorldLocation                       unk28;               // 28
		BGSWorldLocation                       unk40;               // 40
		BGSWorldLocation                       searchLoc;           // 58
		BGSWorldLocation                       unk70;               // 70
		AITimeStamp                            unk88;               // 88 - unk40
		AITimeStamp                            unk8C;               // 8C - unk28
		AITimeStamp                            lastKnownTimeStamp;  // 90 - lastKnownLoc
		AITimeStamp                            unk94;               // 94 - ??
		AITimeStamp                            unk98;               // 98 - unk58
		AITimeStamp                            unk9C;               // 9C - unk70
		ActorHandle                            attackedMember;      // A0
		std::uint16_t                          attackerCount;       // A4
		stl::enumeration<Flags, std::uint16_t> flags;               // A6
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatTarget) == 0xA8);

	class CombatMember
	{
	public:
		// members
		ActorHandle memberHandle;              // 00
		float       groupStrengthUpdateTimer;  // 04
		float       threatValue;               // 08
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatMember) == 0x0C);

	struct CombatSearchDoor
	{
	public:
		// members
		ObjectRefHandle doorHandle;        // 00
		ObjectRefHandle linkedDoorHandle;  // 04
		std::uint8_t    unk08;             // 08
		std::uint8_t    unk09;             // 09
		std::uint8_t    unk0A;             // 0A
	};
	static_assert(sizeof(CombatSearchDoor) == 0xC);

	class CombatGroup
	{
	public:
		// members
		std::uint32_t                  groupID;                      // 000
		std::uint32_t                  groupIndex;                   // 004
		BSTArray<CombatTarget>         targets;                      // 008
		BSTArray<CombatMember>         members;                      // 020
		CombatGroupDetectionListener*  detectionListener;            // 038
		AITimer                        allyKilledTimer;              // 040
		AITimer                        avoidThreathTimer;            // 048
		AITimer                        unk50;                        // 050
		AITimer                        detectionDialogueTimers[11];  // 058
		AITimer                        updateTimer;                  // 0B0
		AITimer                        musicThreatRatioTimer;        // 0B8
		AITimer                        unkC0;                        // 0C0
		float                          unkC8;                        // 0C8
		float                          unkCC;                        // 0CC
		float                          unkD0;                        // 0D0
		float                          unkD4;                        // 0D4
		std::uint32_t                  searchState;                  // 0D8
		std::uint32_t                  padDC;                        // 0DC
		BSPathingLOSGridMap*           gridMap;                      // 0E0
		AITimer                        searchUpdateTimer;            // 0E8
		AITimer                        searchAreaUpdateTimer;        // 0F0
		AITimeStamp                    searchStartedTimeStamp;       // 0F8
		ActorHandle                    targetToSearchFor;            // 0FC
		BGSWorldLocation               searchTargetLoc;              // 100
		float                          searchRadius;                 // 118
		std::uint32_t                  pad11C;                       // 11C
		BSTArray<CombatSearchLocation> searchLocations;              // 120
		BSTArray<CombatSearchDoor>     searchDoors;                  // 138
		std::uint32_t                  initializedMemberCount;       // 150 - count
		std::uint32_t                  fleeCount;                    // 154
		std::uint32_t                  fightCount;                   // 158
		std::uint8_t                   musicState;                   // 15C
		std::uint8_t                   unk15D;                       // 15D
		std::uint8_t                   unk15E;                       // 15E
		std::uint8_t                   unk15F;                       // 15F
		mutable BSReadWriteLock        lock;                         // 160
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatGroup) == 0x168);
}
