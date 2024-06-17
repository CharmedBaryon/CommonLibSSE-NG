#pragma once

#include "RE/B/BGSDefaultObjectManager.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSSoundHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTList.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/B/BSTTuple.h"
#include "RE/C/Character.h"
#include "RE/C/Crime.h"
#include "RE/C/CrosshairPickData.h"
#include "RE/F/FormTypes.h"
#include "RE/H/hkRefPtr.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTMap.h"
#include "RE/P/PositionPlayerEvent.h"
#include "RE/T/TESObjectWEAP.h"
#include "RE/T/TESQuest.h"
#include "RE/T/TintMask.h"
#include <RE/B/BSCoreTypes.h>
#include <RE/N/NiPoint3.h>


namespace RE
{
	enum class AQUIRE_TYPE;

	class Actor;
	class BGSInstancedQuestObjective;
	class BGSLocation;
	class bhkMouseSpringAction;
	class BipedAnim;
	class BSFadeNode;
	class BSLight;
	class BSTriShape;
	class CombatGroup;
	class ImageSpaceModifierInstanceDOF;
	class InventoryEntryData;
	class MenuModeChangeEvent;
	class MenuOpenCloseEvent;
	class NiAVObject;
	class NiBillboardNode;
	class NiNode;
	class ObjectListItem;
	class TESObject;
	class TESObjectREFR;
	class UserEventEnabledEvent;
	struct BGSActorCellEvent;
	struct BGSActorDeathEvent;
	struct PerkRankData;
	struct PositionPlayerEvent;
	struct TESQuestStageItem;
	struct TESTrackedStatsEvent;
#ifdef ENABLE_SKYRIM_VR
	struct VRDeviceConnectionChange;
	struct VROverlayChange;
	struct VRResetHMDHeight;
#endif

	enum class PLAYER_ACTION
	{
		kNone = 0,
		kSwingMeleeWeapon,
		kCastProjectileSpell,
		kShootBow,
		kZKeyObject,
		kJumping,
		kKnockingOverObjects,
		kStandOnTableChair,
		kIronSights,
		kDestroyObject,
		kLockedObject,
		kPickpocket,
		kCastSelfSpell,
		kShout,
		kActorCollision,

		kTotal,
		kInvalidMarker
	};

	enum VR_Bow_State : std::uint32_t
	{
		kNone,
		kNoAmmo,
		kIdle,
		kArrowKnocked,
	};

	struct VR_NODE_DATA
	{
#define VR_NODE_DATA_CONTENT                                                                                                                                                  \
	NiPointer<NiNode>          PlayerWorldNode;                 /* 3F0 */                                                                                                     \
	NiPointer<NiNode>          FollowNode;                      /* 3F8 */                                                                                                     \
	NiPointer<NiNode>          FollowOffset;                    /* 400 */                                                                                                     \
	NiPointer<NiNode>          HeightOffsetNode;                /* 408 */                                                                                                     \
	NiPointer<NiNode>          SnapWalkOffsetNode;              /* 410 */                                                                                                     \
	NiPointer<NiNode>          RoomNode;                        /* 418 */                                                                                                     \
	NiPointer<NiNode>          BlackSphere;                     /* 420 */                                                                                                     \
	NiPointer<NiNode>          uiNode;                          /* 428 */                                                                                                     \
	NiPointer<BSTriShape>      InWorldUIQuadGeo;                /* 430 */                                                                                                     \
	NiPointer<NiNode>          UIPointerNode;                   /* 438 */                                                                                                     \
	NiPointer<BSTriShape>      UIPointerGeo;                    /* 440 */                                                                                                     \
	NiPointer<NiNode>          DialogueUINode;                  /* 448 */                                                                                                     \
	NiPointer<NiNode>          TeleportDestinationPreview;      /* 450 */                                                                                                     \
	NiPointer<NiNode>          TeleportDestinationFail;         /* 458 */                                                                                                     \
	NiPointer<NiNode>          TeleportSprintPreview;           /* 460 */                                                                                                     \
	NiPointer<NiNode>          SpellOrigin;                     /* 468 */                                                                                                     \
	NiPointer<NiNode>          SpellDestination;                /* 470 */                                                                                                     \
	NiPointer<NiNode>          ArrowOrigin;                     /* 478 */                                                                                                     \
	NiPointer<NiNode>          ArrowDestination;                /* 480 */                                                                                                     \
	NiPointer<NiNode>          QuestMarker;                     /* 488 */                                                                                                     \
	NiPointer<NiNode>          LeftWandNode;                    /* 490 */                                                                                                     \
	NiPointer<NiNode>          LeftWandShakeNode;               /* 498 */                                                                                                     \
	NiPointer<NiNode>          LeftValveIndexControllerNode;    /* 4A0 */                                                                                                     \
	NiPointer<NiNode>          unkNode4A8;                      /* 4A8 */                                                                                                     \
	NiPointer<NiNode>          LeftWeaponOffsetNode;            /* 4B0 */                                                                                                     \
	NiPointer<NiNode>          LeftCrossbowOffsetNode;          /* 4B8 */                                                                                                     \
	NiPointer<NiNode>          LeftMeleeWeaponOffsetNode;       /* 4C0 */                                                                                                     \
	NiPointer<NiNode>          LeftStaffWeaponOffsetNode;       /* 4C8 */                                                                                                     \
	NiPointer<NiNode>          LeftShieldOffsetNode;            /* 4D0 */                                                                                                     \
	NiPointer<NiNode>          RightShieldOffsetNode;           /* 4D8 */                                                                                                     \
	NiPointer<NiNode>          SecondaryMagicOffsetNode;        /* 4E0 */                                                                                                     \
	NiPointer<NiNode>          SecondaryMagicAimNode;           /* 4E8 */                                                                                                     \
	NiPointer<NiNode>          SecondaryStaffMagicOffsetNode;   /* 4F0 */                                                                                                     \
	NiPointer<NiNode>          RightWandNode;                   /* 4F8 */                                                                                                     \
	NiPointer<NiNode>          RightWandShakeNode;              /* 500 */                                                                                                     \
	NiPointer<NiNode>          RightValveIndexControllerNode;   /* 508 */                                                                                                     \
	NiPointer<NiNode>          unkNode510;                      /* 510 */                                                                                                     \
	NiPointer<NiNode>          RightWeaponOffsetNode;           /* 518 */                                                                                                     \
	NiPointer<NiNode>          RightCrossbowOffsetNode;         /* 520 */                                                                                                     \
	NiPointer<NiNode>          RightMeleeWeaponOffsetNode;      /* 528 */                                                                                                     \
	NiPointer<NiNode>          RightStaffWeaponOffsetNode;      /* 530 */                                                                                                     \
	NiPointer<NiNode>          PrimaryMagicOffsetNode;          /* 538 */                                                                                                     \
	NiPointer<NiNode>          PrimaryMagicAimNode;             /* 540 */                                                                                                     \
	NiPointer<NiNode>          PrimaryStaffMagicOffsetNode;     /* 548 */                                                                                                     \
	std::uint64_t              unk550;                          /* 550 */                                                                                                     \
	NiPointer<NiBillboardNode> CrosshairParent;                 /* 558 */                                                                                                     \
	NiPointer<NiBillboardNode> CrosshairSecondaryParent;        /* 560 */                                                                                                     \
	NiPointer<NiBillboardNode> TargetLockParent;                /* 568 */                                                                                                     \
	NiPointer<NiNode>          GamepadNode;                     /* 570 */                                                                                                     \
	NiPointer<NiNode>          LastSyncPos;                     /* 578 */                                                                                                     \
	NiPointer<NiNode>          UprightHmdNode;                  /* 580 */                                                                                                     \
	NiPointer<NiNode>          MapMarkers3D;                    /* 588 */                                                                                                     \
	NiPointer<NiNode>          NPCLHnd;                         /* 590 */                                                                                                     \
	NiPointer<NiNode>          NPCRHnd;                         /* 598 */                                                                                                     \
	NiPointer<NiNode>          NPCLClv;                         /* 5A0 */                                                                                                     \
	NiPointer<NiNode>          NPCRClv;                         /* 5A8 */                                                                                                     \
	std::uint32_t              unk5B0;                          /* 5B0 */                                                                                                     \
	std::uint32_t              unk5B4;                          /* 5B4 */                                                                                                     \
	std::uint64_t              unk5B8;                          /* 5B8 */                                                                                                     \
	VR_Bow_State               bowState;                        /* 5C0 */                                                                                                     \
	std::uint32_t              unk5C4;                          /* 5C4 */                                                                                                     \
	NiPointer<NiNode>          BowAimNode;                      /* 5C8 */                                                                                                     \
	NiPointer<NiNode>          BowRotationNode;                 /* 5D0 */                                                                                                     \
	NiPointer<NiNode>          ArrowSnapNode;                   /* 5D8 */                                                                                                     \
	NiPointer<BSFadeNode>      ArrowNode;                       /* 5E0 */                                                                                                     \
	NiPointer<BSFadeNode>      ArrowFireNode;                   /* 5E8 */                                                                                                     \
	std::uint64_t              unk5F0;                          /* 5F0 */                                                                                                     \
	NiPointer<NiNode>          ArrowHoldOffsetNode;             /* 5F8 */                                                                                                     \
	NiPointer<NiNode>          ArrowHoldNode;                   /* 600 */                                                                                                     \
	std::uint64_t              unk608;                          /* 608 */                                                                                                     \
	float                      currentArrowSnapDistance;        /* 610 */                                                                                                     \
	std::uint32_t              unk614;                          /* 614 */                                                                                                     \
	float                      currentBowDrawAmount;            /* 618 - 0 to 1 */                                                                                            \
	float                      lastRumbleBowDrawAmount;         /* 61C - 0 to 1 */                                                                                            \
	std::uint64_t              unk620;                          /* 620 */                                                                                                     \
	std::uint64_t              unk628;                          /* 628 */                                                                                                     \
	std::uint64_t              unk630;                          /* 630 */                                                                                                     \
	void*                      QuestMarkerBillBoardsNodeArray;  /* 638    TODO - Make into proper data structure */                                                           \
	void*                      TeleportNodeArray;               /* 640    TODO - Make into proper data structure */                                                           \
	void*                      QuestMarkerBillBoardsNodeArray2; /* 648    TODO - Make into proper data structure -> points to same place as QuestMarkerBillBoardsNodeArray */ \
	std::uint64_t              unk650;                          /* 650 */                                                                                                     \
	void*                      TeleportNodeArray2;              /* 658    TODO - Make into proper data structure -> points to same place as TeleportNodeArray */              \
	void*                      QuestMarkerBillBoardsNodeArray3; /* 660    TODO - Make into proper data structure -> points to same place as QuestMarkerBillBoardsNodeArray */ \
	std::uint64_t              unk668;                          /* 668 */                                                                                                     \
	float                      unkFloat670;                     /* 670 */                                                                                                     \
	std::uint32_t              unk674;                          /* 674 */                                                                                                     \
	void*                      TeleportNodeArray3;              /* 678    TODO - Make into proper data structure */
        VR_NODE_DATA_CONTENT
	};
	static_assert(sizeof(VR_NODE_DATA) == 0x290);

	struct CrimeGoldStruct
	{
	public:
		// members
		float violentCur;        // 00
		float nonViolentCur;     // 04
		float nonViolentInfamy;  // 08
		float violentInfamy;     // 0C
	};
	static_assert(sizeof(CrimeGoldStruct) == 0x10);

	struct StolenItemValueStruct
	{
	public:
		// members
		std::int32_t unwitnessed;  // 0
		std::int32_t witnessed;    // 4
	};
	static_assert(sizeof(StolenItemValueStruct) == 0x8);

	struct FriendshipFactionsStruct
	{
	public:
		// members
		std::uint16_t friendCounts[4];  // 0
	};
	static_assert(sizeof(FriendshipFactionsStruct) == 0x8);

	struct PLAYER_TARGET_LOC
	{
		using ArrivalFunc_t = void(std::int64_t);

		// members
		TESWorldSpace* world;             // 00
		TESObjectCELL* interior;          // 08
		NiPoint3       location;          // 10
		NiPoint3       angle;             // 1C
		ArrivalFunc_t* arrivalFunc;       // 28
		std::int64_t   arrivalFuncData;   // 30
		RefHandle      furnitureRef;      // 38
		RefHandle      fastTravelMarker;  // 3C
		bool           resetWeather;      // 40
		bool           allowAutoSave;     // 41
		bool           isValid;           // 42
		std::uint8_t   pad43;             // 43
		std::uint32_t  pad44;             // 44
	};
	static_assert(sizeof(PLAYER_TARGET_LOC) == 0x48);

	struct VR_PLAYER_TARGET_LOC
	{
		using ArrivalFunc_t = void(std::int64_t);

		// members
		TESWorldSpace* world;             // 00
		TESObjectCELL* interior;          // 08
		NiPoint3       location;          // 10
		NiPoint3       angle;             // 1C
		ArrivalFunc_t* arrivalFunc;       // 28
		std::int64_t   arrivalFuncData;   // 30
		RefHandle      furnitureRef;      // 38
		RefHandle      fastTravelMarker;  // 3C
		float          unk_40;            // 40 - New in VR, always 0.0 in vanilla
		std::uint8_t   unk44;             // 44
		bool           resetWeather;      // 45
		std::uint8_t   allowAutoSave;     // 46
		bool           isValid;           // 47
		std::uint8_t   unk48;             // 48
		std::uint8_t   unk49;             // 49
		std::uint8_t   unk4A;             // 4A
		std::uint8_t   unk4B;             // 4B
		std::uint32_t  unk4C;             // 4C
	};
	static_assert(sizeof(VR_PLAYER_TARGET_LOC) == 0x50);

	struct PlayerActionObject
	{
	public:
		// members
		float                                          timer;   // 0
		RefHandle                                      refObj;  // 4
		stl::enumeration<PLAYER_ACTION, std::uint32_t> next;    // 8
	};
	static_assert(sizeof(PlayerActionObject) == 0xC);

	class PlayerCharacter :
#ifndef ENABLE_SKYRIM_AE
		public Character,                            // 000
		public BSTEventSource<BGSActorCellEvent>,    // 2D0
		public BSTEventSource<BGSActorDeathEvent>,   // 328
		public BSTEventSource<PositionPlayerEvent>,  // 380
		public BSTEventSink<MenuOpenCloseEvent>,     // 2B0
		public BSTEventSink<MenuModeChangeEvent>,    // 2B8
		public BSTEventSink<UserEventEnabledEvent>,  // 2C0
		public BSTEventSink<TESTrackedStatsEvent>    // 2C8
#else
		public Character  // 000
#endif
	{
	public:
		inline static constexpr auto RTTI = RTTI_PlayerCharacter;
		inline static constexpr auto VTABLE = VTABLE_PlayerCharacter;
		inline static constexpr auto FORMTYPE = FormType::ActorCharacter;

		enum class EventType
		{
			kThief = 3,
			kContainer = 5,
			kDeadBody = 6
		};

		enum class GrabbingType
		{
			kNone = 0,
			kNormal,
			kTelekinesis,
		};

		enum class ByCharGenFlag
		{
			kNone = 0,
			kDisableSaving = 1 << 0,
			kHandsBound = 1 << 2
		};

		struct GrabData
		{
#define GRAB_DATA_CONTENT                                                        \
	BSTSmallArray<hkRefPtr<bhkMouseSpringAction>, 4> grabSpring;       /* 898 */ \
	ObjectRefHandle                                  grabbedObject;    /* 8C8 */ \
	float                                            grabObjectWeight; /* 8CC */ \
	float                                            grabDistance;     /* 8d0 */ \
	float                                            unk004;           /* 8d4 */ \
	std::uint64_t                                    unk008;           /* 8d8 */

			GRAB_DATA_CONTENT
		};
		static_assert(sizeof(GrabData) == 0x48);

		struct VRGrabData
		{
		public:
			// members
			BSTSmallArray<hkRefPtr<bhkMouseSpringAction>, 4> grabSpring;        // 00
			ObjectRefHandle                                  grabbedObject;     // 30
			float                                            grabObjectWeight;  // 34
			GrabbingType                                     grabType;          // 38
			float                                            grabDistance;      // 3C
			std::double_t                                    unk40;             // 40 - 0x40 and below for havok stuff
			std::uint64_t                                    unk48;             // 48
			std::double_t                                    unk50;             // 50
			std::uint64_t                                    unk58;             // 58
			std::uint32_t                                    unk60;             // 60
			std::uint32_t                                    unk64Flags;        // 64
		};
		static_assert(sizeof(VRGrabData) == 0x68);

		struct PlayerFlags
		{
			// members
			bool travelUseDoor: 1;                  // 0:0 - Guess from FO4 given matching logic for Character::WarpFollowers
			bool fastTraveling: 1;                  // 0:1 - Set and cleared in the same fast travel function
			bool overAutoAimTarget: 1;              // 0:2 - Crosshair over hostile actor AND equipped WEAPON_TYPE bow, staff, or crossbow, must have weapon out to be accurate
			bool showQuestItems: 1;                 // 0:3 - Not used by game, confirmed with console command `SetShowQuestItems`
			bool unk0_4: 1;                         // 0:4 - Unused?
			bool hasQueuedEquipAnim: 1;             // 0:5 - Set true in `OnItemEquipped` if a_playAnim && isPaused, false once out of menu
			bool escaping: 1;                       // 0:6 - Is Escaping from jail
			bool forceQuestTargetRepath: 1;         // 0:7 - Updates quest target in compass
			bool unk1_0: 1;                         // 1:0
			bool unk1_1: 1;                         // 1:1
			bool sleeping: 1;                       // 1:2
			bool unk1_3: 1;                         // 1:3
			bool unk1_4: 1;                         // 1:4
			bool unk1_5: 1;                         // 1:5
			bool greetingPlayer: 1;                 // 1:6 - NPC greeting player
			bool unk1_7: 1;                         // 1:7
			bool unk2_0: 1;                         // 2:0
			bool aiControlledToPos: 1;              // 2:1 - Guess from FO4, confirmed aiControlled related
			bool aiControlledFromPos: 1;            // 2:2 - Guess from FO4, confirmed aiControlled related
			bool aiControlledPackage: 1;            // 2:3 - Guess from FO4, confirmed aiControlled related
			bool returnToLastKnownGoodPosition: 1;  // 2:4 - return to lastKnownGoodPosition on next Update
			bool isBeingChased: 1;                  // 2:5 - unused along with chaseTimer
			bool unk2_6: 1;                         // 2:6
			bool unk2_7: 1;                         // 2:7
			bool isInThirdPersonMode: 1;            // 3:0
			bool unk3_1: 1;                         // 3:1
			bool unk3_2: 1;                         // 3:2
			bool unk3_3: 1;                         // 3:3
			bool target3DDistant: 1;                // 3:4 - Distance from object in crosshair > 1000
			bool isInCombat: 1;                     // 3:5
			bool attemptedYieldInCurrentCombat: 1;  // 3:6 - Set when yielding to guard for arrest dialogue, prevents multiple arrest dialogues
			bool unk3_7: 1;                         // 3:7
			bool isLoading: 1;                      // 4:0 - Is player loading a new area
			bool shouldUpdateCrosshair: 1;          // 4:1 - If forced off without letting Skyrim update this, crosshair UI won't update,
			bool unk4_2: 1;                         // 4:2
			bool healthTutorialShown: 1;            // 4:3
			bool magickaTutorialShown: 1;           // 4:4
			bool staminaTutorialShown: 1;           // 4:5
			bool goToJailQueued: 1;                 // 4:6 - Briefly set
			bool unk4_7: 1;                         // 4:7
			bool isSprinting: 1;                    // 5:0
			bool isSungazing: 1;                    // 5:1 - Is staring at the sun
			bool dragonRideTargetLocked: 1;         // 5:2
			bool everModded: 1;                     // 5:3
			bool servingJailTime: 1;                // 5:4 - Briefly set
#if !defined(ENABLE_SKYRIM_VR)
			bool          pad5_5: 3;  // 5:5
			std::uint16_t pad6;       // 6
#else
			bool unk5_5: 1;  // 5:5
			bool unk5_6: 1;  // 5:6
			bool unk5_7: 1;  // 5:7
			bool unk6_0: 1;  // 6:0
			bool unk6_1: 1;  // 6:1
			bool unk6_2: 1;  // 6:2
			bool unk6_3: 1;  // 6:3
			bool unk6_4: 1;  // 6:4
			bool unk6_5: 1;  // 6:5
			bool unk6_6: 1;  // 6:6
			bool unk6_7: 1;  // 6:7
			bool unk7_0: 1;  // 7:0
			bool unk7_1: 1;  // 7:1
			bool unk7_2: 1;  // 7:2
			bool unk7_3: 1;  // 7:3
			bool unk7_4: 1;  // 7:4
			bool unk7_5: 1;  // 7:5
			bool unk7_6: 1;  // 7:6
			bool unk7_7: 1;  // 7:7
#endif
		};
		static_assert(sizeof(PlayerFlags) == 0x8);

		struct QueuedWeapon
		{
		public:
			// members
			TESObjectWEAP* rightHandWeapon;  // 00 - These may be main/off hand weapon for VR?
			TESObjectWEAP* leftHandWeapon;   // 08
		};
		static_assert(sizeof(QueuedWeapon) == 0x10);

		struct TeleportPath  // TODO: Should not be in Player class. Gets used in Pathing and other non-player areas
		{
		public:
			struct Unk00Data
			{
			public:
				// members
				bool           unk00;         // 00 - Determines whether to use worldspace or cell?
				char           pad01[7];      // 01
				TESWorldSpace* worldspace;    // 08
				TESObjectCELL* interiorCell;  // 10
			};
			static_assert(sizeof(Unk00Data) == 0x18);

			struct Unk18Data
			{
			public:
				// members
				RE::TESObjectREFR* unk00;  // 00
				std::uint64_t      unk08;  // 08
				std::uint64_t      unk10;  // 10
			};
			static_assert(sizeof(Unk18Data) == 0x18);

			// members
			BSTArray<Unk00Data> unk00;  // 00
			BSTArray<Unk18Data> unk18;  // 18
			std::uint64_t       unk30;  // 30
			std::uint64_t       unk38;  // 38
			std::uint64_t       unk40;  // 40
		};
		static_assert(sizeof(TeleportPath) == 0x48);

		struct PreTransformationData
		{
		public:
			// members
			MagicItem*      storedSelectedSpells[4];    // 00
			TESRace*        storedRace;                 // 20
			TESForm*        storedSelectedPower;        // 28
			TESBoundObject* storedLastOneHandItems[2];  // 30
		};
		static_assert(sizeof(PreTransformationData) == 0x40);

		struct CrimeValue
		{
#define CRIME_VALUE_CONTENT                                                           \
	BSTHashMap<const TESFaction*, CrimeGoldStruct>       crimeGoldMap;       /* 00 */ \
	BSTHashMap<const TESFaction*, StolenItemValueStruct> stolenItemValueMap; /* 30 */

			CRIME_VALUE_CONTENT
		};
		static_assert(sizeof(CrimeValue) == 0x60);

		struct RaceData
		{
#define RACE_DATA_CONTENT                \
	BGSTextureSet* complexion;  /* 00 */ \
	TESRace*       charGenRace; /* 08 */ \
	TESRace*       race2;       /* 10 */

			RACE_DATA_CONTENT
		};
		static_assert(sizeof(RaceData) == 0x18);

		struct GameStateData
		{
#define GAME_STATE_DATA_CONTENT                                            \
	std::int32_t                                  difficulty;      /* 0 */ \
	ActorHandle                                   assumedIdentity; /* 4 */ \
	std::int8_t                                   murder;          /* 8 */ \
	std::int8_t                                   perkCount;       /* 9 */ \
	stl::enumeration<ByCharGenFlag, std::uint8_t> byCharGenFlag;   /* A */ \
	std::uint8_t                                  padB;            /* B */

			GAME_STATE_DATA_CONTENT
		};
		static_assert(sizeof(GameStateData) == 0xC);

		struct PlayerSkills
		{
		public:
			struct Data
			{
			public:
				struct Skills
				{
					enum Skill : std::uint32_t
					{
						kOneHanded = 0,
						kTwoHanded = 1,
						kArchery = 2,
						kBlock = 3,
						kSmithing = 4,
						kHeavyArmor = 5,
						kLightArmor = 6,
						kPickpocket = 7,
						kLockpicking = 8,
						kSneak = 9,
						kAlchemy = 10,
						kSpeech = 11,
						kAlteration = 12,
						kConjuration = 13,
						kDestruction = 14,
						kIllusion = 15,
						kRestoration = 16,
						kEnchanting = 17,
						kTotal
					};
				};
				using Skill = Skills::Skill;

				struct SkillData
				{
				public:
					// members
					float level;           // 0
					float xp;              // 4
					float levelThreshold;  // 8
				};
				static_assert(sizeof(SkillData) == 0xC);

				// members
				float         xp;                              // 000
				float         levelThreshold;                  // 004
				SkillData     skills[Skill::kTotal];           // 008
				std::uint32_t legendaryLevels[Skill::kTotal];  // 0E0
			};
			static_assert(sizeof(Data) == 0x128);

			void AdvanceLevel(bool a_addThreshold);

			// members
			Data* data;  // 0
		};
		static_assert(sizeof(PlayerSkills) == 0x8);

		struct INFO_RUNTIME_DATA
		{
#define INFO_RUNTIME_DATA_CONTENT                                                                                     \
	std::uint32_t              sleepSeconds;                                /* 014 */                                 \
	BSTSmartPointer<BipedAnim> largeBiped;                                  /* 018 */                                 \
	NiPointer<NiNode>          firstPerson3D;                               /* 020 */                                 \
	float                      eyeHeight;                                   /* 028 */                                 \
	float                      greetTimer;                                  /* 02C */                                 \
	float                      encumberedTimer;                             /* 030 */                                 \
	float                      powerAttackTimer;                            /* 034 */                                 \
	std::int32_t               hoursToSleep;                                /* 038 */                                 \
	std::int32_t               amountStolenSold;                            /* 03C */                                 \
	std::uint32_t              valueStolen;                                 /* 040 */                                 \
	ActorHandle                lastRiddenMount;                             /* 044 */                                 \
	ActorHandle                lightTarget;                                 /* 048 */                                 \
	float                      sortActorDistanceTimer;                      /* 04C */                                 \
	float                      sitHeadingDelta;                             /* 050 only in SSE, VR needs adjustment*/ \
	ObjectRefHandle            playerMapMarker;                             /* 054 */                                 \
	TeleportPath*              playerMarkerPath;                            /* 058 */                                 \
	std::uint32_t              skillTrainingsThisLevel;                     /* 060 */                                 \
	std::uint32_t              unk064;                                      /* 064 */                                 \
	TESClass*                  defaultClass;                                /* 068 */                                 \
	std::uint64_t              unk070;                                      /* 070 */                                 \
	std::uint32_t              crimeCounts[PackageNS::CRIME_TYPES::kTotal]; /* 078 */                                 \
	std::uint32_t              unk094;                                      /* 094 */                                 \
	AlchemyItem*               pendingPoison;                               /* 098 */                                 \
	std::int64_t               lastPlayingTimeUpdate;                       /* 0A0 */                                 \
	std::int64_t               totalPlayingTime;                            /* 0A8 */                                 \
	std::int32_t               characterSeed;                               /* 0B0 */                                 \
	std::uint32_t              unk0B4;                                      /* 0B4 */                                 \
	TESForm*                   lastKnownGoodLocation;                       /* 0B8 */                                 \
	std::uint32_t              unk0C0;                                      /* 0C0 */                                 \
	std::uint32_t              unk0C4;                                      /* 0C4 */                                 \
	NiPointer<BSLight>         firstPersonLight;                            /* 0C8 */                                 \
	NiPointer<BSLight>         thirdPersonLight;                            /* 0D0 */                                 \
	float                      dropAngleMod;                                /* 0D8 */                                 \
	float                      lastDropAngleMod;                            /* 0DC */                                 \
	PlayerSkills*              skills;                                      /* 0E0 */                                 \
	ActorHandle                autoAimActor;                                /* 0E8 */                                 \
	RefHandle                  unk0EC;                                      /* 0EC */                                 \
	std::uint64_t              unk118;                                      /* 0F0 */                                 \
	NiPointer<NiAVObject>      targeted3D;                                  /* 0F8 */                                 \
	CombatGroup*               combatGroup;                                 /* 100 */                                 \
	BSTArray<ActorHandle>      actorsToDisplayOnTheHUDArray;                /* 108 */                                 \
	TESForm*                   advanceObject;                               /* 120 */                                 \
	TESBoundObject*            lastOneHandItems[2];                         /* 128 */                                 \
	std::uint32_t              teammateCount;                               /* 138 */                                 \
	float                      combatTimer;                                 /* 13C */                                 \
	float                      yieldTimer;                                  /* 140 */                                 \
	float                      chaseTimer;                                  /* 144 */                                 \
	float                      drawSheatheSafetyTimer;                      /* 148 */                                 \
	std::uint32_t              unk14C;                                      /* 14C */

			INFO_RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(INFO_RUNTIME_DATA) == 0x140);

		struct VR_INFO_RUNTIME_DATA
		{
#define VR_INFO_RUNTIME_DATA_CONTENT                                                                                                                                                       \
	std::uint32_t              sleepSeconds;                                /* FE0 */                                                                                                      \
	std::uint32_t              unkFE4;                                      /* FE4 */                                                                                                      \
	BSTSmartPointer<BipedAnim> largeBiped;                                  /* FE8 */                                                                                                      \
	NiPointer<NiNode>          firstPerson3D;                               /* FF0 */                                                                                                      \
	float                      eyeHeight;                                   /* FF8 */                                                                                                      \
	float                      greetTimer;                                  /* FFC */                                                                                                      \
	float                      encumberedTimer;                             /* 1000 */                                                                                                     \
	float                      powerAttackTimer;                            /* 1004 */                                                                                                     \
	std::int32_t               hoursToSleep;                                /* 1008 */                                                                                                     \
	std::int32_t               amountStolenSold;                            /* 100C */                                                                                                     \
	std::uint32_t              valueStolen;                                 /* 1010 */                                                                                                     \
	ActorHandle                lastRiddenMount;                             /* 1014 */                                                                                                     \
	ActorHandle                lightTarget;                                 /* 1018 */                                                                                                     \
	float                      sortActorDistanceTimer;                      /* 101C */                                                                                                     \
	ObjectRefHandle            playerMapMarker;                             /* 1020 - Custom marker placed by player in map */                                                             \
	std::uint32_t              pad1024;                                     /* 1024 */                                                                                                     \
	TeleportPath*              playerMarkerPath;                            /* 1028 - Educated guess from FO4 */                                                                           \
	std::uint32_t              skillTrainingsThisLevel;                     /* 1030 */                                                                                                     \
	std::uint32_t              unk1034;                                     /* 1034 */                                                                                                     \
	TESClass*                  defaultClass;                                /* 1038 */                                                                                                     \
	std::uint64_t              unk1040;                                     /* 1040 */                                                                                                     \
	std::uint32_t              crimeCounts[PackageNS::CRIME_TYPES::kTotal]; /* 1048 */                                                                                                     \
	std::uint32_t              unk964;                                      /* 1064 */                                                                                                     \
	AlchemyItem*               pendingPoison;                               /* 1068 */                                                                                                     \
	std::int64_t               lastPlayingTimeUpdate;                       /* 1070 */                                                                                                     \
	std::int64_t               totalPlayingTime;                            /* 1078 */                                                                                                     \
	std::int32_t               characterSeed;                               /* 1080 */                                                                                                     \
	std::uint32_t              unk984;                                      /* 1084 */                                                                                                     \
	TESForm*                   lastKnownGoodLocation;                       /* 1088 */                                                                                                     \
	std::uint32_t              unk990;                                      /* 1090 */                                                                                                     \
	std::uint32_t              unk994;                                      /* 1094 */                                                                                                     \
	NiPointer<BSLight>         firstPersonLight;                            /* 1098 */                                                                                                     \
	NiPointer<BSLight>         thirdPersonLight;                            /* 10A0 */                                                                                                     \
	float                      dropAngleMod;                                /* 10A8 */                                                                                                     \
	float                      lastDropAngleMod;                            /* 10AC */                                                                                                     \
	PlayerSkills*              skills;                                      /* 10B0 */                                                                                                     \
	ActorHandle                autoAimActor;                                /* 10B8 */                                                                                                     \
	RefHandle                  unk9BC;                                      /* 10BC */                                                                                                     \
	std::uint64_t              unk9C0;                                      /* 10C0 */                                                                                                     \
	NiPointer<NiAVObject>      targeted3D;                                  /* 10C8 */                                                                                                     \
	CombatGroup*               combatGroup;                                 /* 10D0 */                                                                                                     \
	BSTArray<ActorHandle>      actorsToDisplayOnTheHUDArray;                /* 10D8 */                                                                                                     \
	TESForm*                   advanceObject;                               /* 10F0 - Part of 11E8 and 11EC, the object advancing the skill (eg telekinesis spell for alteration skill) */ \
	TESBoundObject*            lastOneHandItems[2];                         /* 10F8 */                                                                                                     \
	std::uint32_t              teammateCount;                               /* 1108 */                                                                                                     \
	float                      combatTimer;                                 /* 110C */                                                                                                     \
	float                      yieldTimer;                                  /* 1110 */                                                                                                     \
	float                      chaseTimer;                                  /* 1114 */                                                                                                     \
	float                      drawSheatheSafetyTimer;                      /* 1118 */                                                                                                     \
	std::uint32_t              unk111C;                                     /* 111C */
            VR_INFO_RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(VR_INFO_RUNTIME_DATA) == 0x140);

		~PlayerCharacter() override;  // 000

		// override
#if !defined(ENABLE_SKYRIM_VR)
		void RemoveWeapon(BIPED_OBJECT equipIndex) override;  // 82
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		void AttachWeapon(RE::TESObjectWEAP* a_weapon, bool attachToShieldHand) override;  // 82
		void RemoveWeapon(BIPED_OBJECT equipIndex) override;                               // 83
#else
#endif

		// add
		SKYRIM_REL_VR_VIRTUAL void          Unk_12A(void);                                                                 // 12A
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL std::uint32_t GetViolentCrimeGoldValue(const TESFaction* a_faction) const;     // 12B
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL std::uint32_t GetNonViolentCrimeGoldValue(const TESFaction* a_faction) const;  // 12C
		SKYRIM_REL_VR_VIRTUAL void                        ClearAllCrimeGold(TESFaction* a_faction);                        // 12D
		SKYRIM_REL_VR_VIRTUAL void                        Unk_12E(void);                                                   // 12E - { return 0; }

		static PlayerCharacter* GetSingleton();
		static bool             IsGodMode();

		void                                   ActivatePickRef();
		void                                   ActivatePickRefVR(VR_DEVICE a_device = VR_DEVICE::kHeadset);
		void                                   AddPlayerAddItemEvent(TESObject* a_object, TESForm* a_owner, TESObjectREFR* a_container, AQUIRE_TYPE a_type);
		void                                   AddSkillExperience(ActorValue a_skill, float a_experience);
		bool                                   AttemptPickpocket(TESObjectREFR* a_containerRef, InventoryEntryData* a_entry, std::int32_t a_number, bool a_fromContainer = true);
		bool                                   CenterOnCell(const char* a_cellName);
		bool                                   CenterOnCell(TESObjectCELL* a_cell);
		bool                                   CheckCast(MagicItem* a_spell, Effect* a_effect, MagicSystem::CannotCastReason& a_reason);
		void                                   DestroyMouseSprings();
		void                                   EndGrabObject();
		[[nodiscard]] NiPointer<Actor>         GetActorDoingPlayerCommand() const;
		[[nodiscard]] float                    GetArmorValue(InventoryEntryData* a_form);
		[[nodiscard]] float                    GetDamage(InventoryEntryData* a_form);
		[[nodiscard]] NiPointer<TESObjectREFR> GetGrabbedRef(VR_DEVICE a_device = VR_DEVICE::kLeftController);
		[[nodiscard]] std::int32_t             GetItemCount(TESBoundObject* a_object);
		[[nodiscard]] std::uint32_t            GetNumTints(std::uint32_t a_tintType);
		[[nodiscard]] TintMask*                GetOverlayTintMask(TintMask* a_original);
		[[nodiscard]] BSTArray<TintMask*>*     GetTintList();
		[[nodiscard]] TintMask*                GetTintMask(std::uint32_t a_tintType, std::uint32_t a_index);
		[[nodiscard]] bool                     HasActorDoingCommand() const;
		[[nodiscard]] bool                     IsGrabbing() const;
		bool                                   IsGrabbingWithDevice(VR_DEVICE a_device) const;
		void                                   PlayMagicFailureSound(MagicSystem::SpellType a_spellType);
		void                                   PlayPickupEvent(TESForm* a_item, TESForm* a_containerOwner, TESObjectREFR* a_containerRef, EventType a_eventType);
		void                                   SetAIDriven(bool a_enable);
		void                                   SetEscaping(bool a_flag, bool a_escaped);
		void                                   StartGrabObject(VR_DEVICE a_device = VR_DEVICE::kLeftController);
		void                                   UpdateCrosshairs();

		[[nodiscard]] inline BSTEventSource<BGSActorCellEvent>* AsBGSActorCellEventSource() noexcept
		{
			return &REL::RelocateMemberIfNewer<BSTEventSource<BGSActorCellEvent>>(SKSE::RUNTIME_SSE_1_6_629, this, 0x2D0, 0x2D8);
		}

		[[nodiscard]] inline const BSTEventSource<BGSActorCellEvent>* AsBGSActorCellEventSource() const noexcept
		{
			return &REL::RelocateMemberIfNewer<BSTEventSource<BGSActorCellEvent>>(SKSE::RUNTIME_SSE_1_6_629, this, 0x2D0, 0x2D8);
		}

		[[nodiscard]] inline BSTEventSource<BGSActorDeathEvent>* AsBGSActorDeathEventSource() noexcept
		{
			return &REL::RelocateMemberIfNewer<BSTEventSource<BGSActorDeathEvent>>(SKSE::RUNTIME_SSE_1_6_629, this, 0x328, 0x330);
		}

		[[nodiscard]] inline const BSTEventSource<BGSActorDeathEvent>* AsBGSActorDeathEventSource() const noexcept
		{
			return &REL::RelocateMemberIfNewer<BSTEventSource<BGSActorDeathEvent>>(SKSE::RUNTIME_SSE_1_6_629, this, 0x2D0, 0x330);
		}

		[[nodiscard]] inline BSTEventSource<PositionPlayerEvent>* AsPositionPlayerEventSource() noexcept
		{
			return &REL::RelocateMemberIfNewer<BSTEventSource<PositionPlayerEvent>>(SKSE::RUNTIME_SSE_1_6_629, this, 0x380, 0x388);
		}

		[[nodiscard]] inline const BSTEventSource<PositionPlayerEvent>* AsPositionPlayerEventSource() const noexcept
		{
			return &REL::RelocateMemberIfNewer<BSTEventSource<PositionPlayerEvent>>(SKSE::RUNTIME_SSE_1_6_629, this, 0x380, 0x388);
		}

		[[nodiscard]] inline BSTEventSink<MenuOpenCloseEvent>* AsMenuOpenCloseEventSink() noexcept
		{
			return &REL::RelocateMemberIfNewer<BSTEventSink<MenuOpenCloseEvent>>(SKSE::RUNTIME_SSE_1_6_629, this, 0x2B0, 0x2B8);
		}

		[[nodiscard]] inline const BSTEventSink<MenuOpenCloseEvent>* AsMenuOpenCloseEventSink() const noexcept
		{
			return &REL::RelocateMemberIfNewer<BSTEventSink<MenuOpenCloseEvent>>(SKSE::RUNTIME_SSE_1_6_629, this, 0x2B0, 0x2B8);
		}

		[[nodiscard]] inline BSTEventSink<MenuModeChangeEvent>* AsMenuModeChangeEventSink() noexcept
		{
			return &REL::RelocateMemberIfNewer<BSTEventSink<MenuModeChangeEvent>>(SKSE::RUNTIME_SSE_1_6_629, this, 0x2B8, 0x2C0);
		}

		[[nodiscard]] inline const BSTEventSink<MenuModeChangeEvent>* AsMenuModeChangeEventSink() const noexcept
		{
			return &REL::RelocateMemberIfNewer<BSTEventSink<MenuModeChangeEvent>>(SKSE::RUNTIME_SSE_1_6_629, this, 0x2B8, 0x2C0);
		}

		[[nodiscard]] inline BSTEventSink<UserEventEnabledEvent>* AsUserEventEnabledEventSink() noexcept
		{
			return &REL::RelocateMemberIfNewer<BSTEventSink<UserEventEnabledEvent>>(SKSE::RUNTIME_SSE_1_6_629, this, 0x2C0, 0x2C8);
		}

		[[nodiscard]] inline const BSTEventSink<UserEventEnabledEvent>* AsUserEventEnabledEventSink() const noexcept
		{
			return &REL::RelocateMemberIfNewer<BSTEventSink<UserEventEnabledEvent>>(SKSE::RUNTIME_SSE_1_6_629, this, 0x2C0, 0x2C8);
		}

		[[nodiscard]] inline BSTEventSink<TESTrackedStatsEvent>* AsTESTrackedStatsEventSink() noexcept
		{
			return &REL::RelocateMemberIfNewer<BSTEventSink<TESTrackedStatsEvent>>(SKSE::RUNTIME_SSE_1_6_629, this, 0x2C8, 0x2D0);
		}

		[[nodiscard]] inline const BSTEventSink<TESTrackedStatsEvent>* AsTESTrackedStatsEventSink() const noexcept
		{
			return &REL::RelocateMemberIfNewer<BSTEventSink<TESTrackedStatsEvent>>(SKSE::RUNTIME_SSE_1_6_629, this, 0x2C8, 0x2D0);
		}

		struct PLAYER_RUNTIME_DATA
		{
#define PLAYER_RUNTIME_DATA_CONTENT                                                                                         \
	mutable BSSpinLock questTargetsLock;                                                              /* 3D8, 3E0 */        \
	CRIME_VALUE_CONTENT;                                                                              /* 3E0 */             \
	ObjectRefHandle                                         commandWaitMarker;                        /* 440 */             \
	std::uint32_t                                           pad444;                                   /* 444 */             \
	BSTHashMap<const TESFaction*, FriendshipFactionsStruct> factionOwnerFriendsMap;                   /* 448 */             \
	NiPoint3                                                lastKnownGoodPosition;                    /* 478 */             \
	NiPoint3                                                bulletAutoAim;                            /* 484 */             \
	NiPoint3                                                cachedVelocity;                           /* 490 */             \
	float                                                   pad49C;                                   /* 49C */             \
	BGSNote*                                                unusedNote;                               /* 4A0 */             \
	BGSNote*                                                unusedNote2;                              /* 4A8 */             \
	BSTArray<PerkRankData*>                                 addedPerks;                               /* 4B0 */             \
	BSTArray<BGSPerk*>                                      perks;                                    /* 4C8 */             \
	BSTArray<BGSPerk*>                                      standingStonePerks;                       /* 4E0 */             \
	BSTArray<ObjectRefHandle>                               currentMapMarkers;                        /* 4F8 */             \
	BSTArray<BSTTuple<NiPoint3, AITimeStamp>>               velocityArray;                            /* 510 */             \
	BSTArray<ProjectileHandle>                              runesCast;                                /* 528 */             \
	BSTArray<void*>                                         imageSpaceModifierAnims1;                 /* 540 */             \
	BSTArray<void*>                                         imageSpaceModifierAnims2;                 /* 558 */             \
	BSSimpleList<TESQuestStageItem*>                        questLog;                                 /* 570 */             \
	BSTArray<BGSInstancedQuestObjective>                    objectives;                               /* 580 */             \
	BSTHashMap<TESQuest*, BSTArray<TESQuestTarget*>*>       questTargets;                             /* 598 */             \
	BSTHashMap<UnkKey, UnkValue>                            currentSayOnceInfosMap;                   /* 5C8 */             \
	BSSimpleList<ObjectRefHandle>                           droppedRefList;                           /* 5F8 */             \
	NiTMap<std::uint32_t, std::uint8_t>                     randomDoorSpaceMap;                       /* 608 */             \
	TESWorldSpace*                                          cachedWorldSpace;                         /* 628 */             \
	NiPoint3                                                exteriorPosition;                         /* 630 */             \
	std::uint32_t                                           pad63C;                                   /* 63C */             \
	PLAYER_TARGET_LOC                                       queuedTargetLoc;                          /* 640 */             \
	BSSoundHandle                                           unusedSound;                              /* 688 */             \
	BSSoundHandle                                           magicFailureSound;                        /* 694 */             \
	BSSoundHandle                                           shoutFailureSound;                        /* 6A0 */             \
	std::uint32_t                                           pad6AC;                                   /* 6AC */             \
	DialoguePackage*                                        closestConversation;                      /* 6B0 */             \
	std::uint32_t                                           unk6B8;                                   /* 6B8 */             \
	std::uint32_t                                           unk6BC;                                   /* 6BC */             \
	DialoguePackage*                                        aiConversationRunning;                    /* 6C0 */             \
	std::int32_t                                            numberofStealWarnings;                    /* 6C8 */             \
	float                                                   stealWarningTimer;                        /* 6CC */             \
	std::int32_t                                            numberofPickpocketWarnings;               /* 6D0 */             \
	float                                                   pickPocketWarningTimer;                   /* 6D4 */             \
	AITimeStamp                                             warnToLeaveTimeStamp;                     /* 6D8 */             \
	std::uint32_t                                           pad6DC;                                   /* 6DC */             \
	ImageSpaceModifierInstanceDOF*                          ironsightsDOFInstance;                    /* 6E0 */             \
	ImageSpaceModifierInstanceDOF*                          vatsDOFInstance;                          /* 6E8 */             \
	ImageSpaceModifierInstanceDOF*                          dynamicDOFInstance;                       /* 6F0 */             \
	float                                                   dynamicDOFFocusTime;                      /* 6F8 */             \
	bool                                                    dynamicDOFFocused;                        /* 6FC */             \
	std::uint8_t                                            unk6FD;                                   /* 6FD */             \
	std::uint16_t                                           unk6FE;                                   /* 6FE */             \
	NiPoint3                                                dynamicDOFLastAngle;                      /* 700 */             \
	NiPoint3                                                dynamicDOFLastPosition;                   /* 70C */             \
	TESFaction*                                             currentPrisonFaction;                     /* 718 */             \
	std::int32_t                                            jailSentence;                             /* 720 */             \
	std::uint32_t                                           pad724;                                   /* 724 */             \
	void*                                                   unk728;                                   /* 728 - smart ptr */ \
	QueuedWeapon                                            queuedWeaponAttachs[WEAPON_TYPE::kTotal]; /* 730 */             \
	std::int32_t                                            vampireFeedDetection;                     /* 7D0 */             \
	std::uint32_t                                           mapMarkerIterator;                        /* 7D4 */             \
	RefHandle                                               forceActivateRef;                         /* 7D8 */             \
	PlayerActionObject                                      playerActionObjects[15];                  /* 7DC */             \
	PLAYER_ACTION                                           mostRecentAction;                         /* 890 */             \
	ActorHandle                                             actorDoingPlayerCommand;                  /* 894 */             \
	GrabData                                                grabData;                                 /* 898 */             \
	std::uint32_t                                           unk8e0;                                   /* 8e0 */             \
	INFO_RUNTIME_DATA_CONTENT;                                                                        /* 8E4 */             \
	std::uint8_t                                   unkA20[0xA0];                                      /* A20 */             \
	std::uint32_t                                  unkAC0;                                            /* AC0 */             \
	std::uint32_t                                  unkAC4;                                            /* AC4 */             \
	BGSLocation*                                   currentLocation;                                   /* AC8 */             \
	AITimeStamp                                    cachedVelocityTimeStamp;                           /* AD0 */             \
	float                                          telekinesisDistance;                               /* AD4 */             \
	float                                          commandTimer;                                      /* AD8 */             \
	float                                          sunGazeTimer;                                      /* ADC */             \
	TESImageSpaceModifier*                         sunGazeImageModifierSpace;                         /* AE0 */             \
	ActorValue                                     advanceSkill;                                      /* AE8 */             \
	std::uint32_t                                  advanceAction;                                     /* AEC */             \
	stl::enumeration<DEFAULT_OBJECT, std::int32_t> animationObjectAction;                             /* AF0 */             \
	stl::enumeration<GrabbingType, std::uint32_t>  grabType;                                          /* AF4 */             \
	GAME_STATE_DATA_CONTENT;                                                                          /* AF8 */             \
	std::uint32_t        unkB04;                                                                      /* B04 */             \
	Crime*               resistArrestCrime;                                                           /* B08 */             \
	BSTArray<TintMask*>  tintMasks;                                                                   /* B10 */             \
	BSTArray<TintMask*>* overlayTintMasks;                                                            /* B28 */             \
	RACE_DATA_CONTENT;                                                                                /* B30 */             \
	std::int32_t            unkB48;                                                                   /* B48 */             \
	std::uint32_t           padB4C;                                                                   /* B4C */             \
	BSTArray<std::uint64_t> unkB50;                                                                   /* B50 */             \
	std::uint64_t           unkB68;                                                                   /* B68 */             \
	std::uint64_t           unkB70;                                                                   /* B70 */             \
	std::uint64_t           unkB78;                                                                   /* B78 */             \
	std::uint64_t           unkB80;                                                                   /* B80 */             \
	std::int32_t            unkB88;                                                                   /* B88 */             \
	std::uint32_t           padB8C;                                                                   /* B8C */             \
	std::uint64_t           unkB90;                                                                   /* B90 */             \
	TESBoundObject*         unkB98;                                                                   /* B98 */             \
	BSTSmallArray<void*, 4> unkBA0;                                                                   /* BA0 */             \
	PreTransformationData*  preTransformationData;                                                    /* BD0 */             \
	PlayerFlags             playerFlags;                                                              /* BD8 */
            PLAYER_RUNTIME_DATA_CONTENT
		};

		struct VR_PLAYER_RUNTIME_DATA
		{
#define VR_PLAYER_RUNTIME_DATA_CONTENT                                                                                                                                                                                 \
	std::uint64_t unk3D8;                                                                             /* 3D8 */                                                                                                        \
	std::uint64_t unk3E0;                                                                             /* 3E0 */                                                                                                        \
	std::uint64_t unk3E8;                                                                             /* 3E8 */                                                                                                        \
	VR_NODE_DATA_CONTENT;                                                                             /* 3F0 */                                                                                                        \
	std::uint64_t      unk680;                                                                        /* 680 */                                                                                                        \
	std::uint64_t      unk688;                                                                        /* 688 */                                                                                                        \
	std::uint64_t      unk690;                                                                        /* 690 */                                                                                                        \
	std::uint64_t      unk698;                                                                        /* 698 */                                                                                                        \
	std::uint64_t      unk6A0;                                                                        /* 6A0 */                                                                                                        \
	std::uint64_t      unk6A8[0x5];                                                                   /* 6A8 */                                                                                                        \
	std::uint32_t      unk6D0;                                                                        /* 6D0 */                                                                                                        \
	std::uint32_t      isRightHandMainHand;                                                           /* 6D4 - Determined from Settings->VR->MainHand setting */                                                       \
	std::uint32_t      isLeftHandMainHand;                                                            /* 6D8 - Determined from Settings->VR->MainHand setting  */                                                      \
	std::uint32_t      unk6DC;                                                                        /* 6DC */                                                                                                        \
	std::uint64_t      unk6F0[0x5D];                                                                  /* 6F0 */                                                                                                        \
	mutable BSSpinLock questTargetsLock;                                                              /* 9C8 - Confirmed in ConsoleFunc__Handler::ShowQuestTargets_14032A200*/                                         \
	CRIME_VALUE_CONTENT;                                                                              /* 9D0 */                                                                                                        \
	ObjectRefHandle                                         commandWaitMarker;                        /* A30 */                                                                                                        \
	std::uint32_t                                           padA34;                                   /* A34 */                                                                                                        \
	BSTHashMap<const TESFaction*, FriendshipFactionsStruct> factionOwnerFriendsMap;                   /* A38 */                                                                                                        \
	NiPoint3                                                lastKnownGoodPosition;                    /* A68 */                                                                                                        \
	NiPoint3                                                bulletAutoAim;                            /* A74 - Guessed from 12D3, confirmed is NiPoint3 */                                                             \
	NiPoint3                                                cachedVelocity;                           /* A80 */                                                                                                        \
	std::uint32_t                                           padA8C;                                   /* A8C */                                                                                                        \
	BGSNote*                                                unusedNote;                               /* A90 - Used for unimplemented formtype BGSNote */                                                              \
	BGSNote*                                                unusedNote2;                              /* A98 - Used for unimplemented formtype BGSNote */                                                              \
	BSTArray<PerkRankData*>                                 addedPerks;                               /* AA0 these 3 here gotta be fixed - guessed based on ae8 */                                                     \
	BSTArray<BGSPerk*>                                      perks;                                    /* AB8 guess */                                                                                                  \
	BSTArray<BGSPerk*>                                      standingStonePerks;                       /* AD0 guess */                                                                                                  \
	BSTArray<ObjectRefHandle>                               currentMapMarkers;                        /* AE8 confirmed */                                                                                              \
	BSTArray<BSTTuple<NiPoint3, AITimeStamp>>               velocityArray;                            /* B00 */                                                                                                        \
	BSTArray<ProjectileHandle>                              runesCast;                                /* B18 */                                                                                                        \
	BSTArray<void*>                                         imageSpaceModifierAnims1;                 /* B30 */                                                                                                        \
	BSTArray<void*>                                         imageSpaceModifierAnims2;                 /* B48 */                                                                                                        \
	BSSimpleList<TESQuestStageItem*>                        questLog;                                 /* B60 */                                                                                                        \
	BSTArray<BGSInstancedQuestObjective>                    objectives;                               /* B70 */                                                                                                        \
	BSTHashMap<TESQuest*, BSTArray<TESQuestTarget*>*>       questTargets;                             /* B88 */                                                                                                        \
	BSTHashMap<UnkKey, UnkValue>                            currentSayOnceInfosMap;                   /* BB8 */                                                                                                        \
	BSSimpleList<ObjectRefHandle>                           droppedRefList;                           /* BE8 */                                                                                                        \
	NiTMap<std::uint32_t, std::uint8_t>                     randomDoorSpaceMap;                       /* BF8 */                                                                                                        \
	TESWorldSpace*                                          cachedWorldSpace;                         /* C18 */                                                                                                        \
	NiPoint3                                                exteriorPosition;                         /* C20 */                                                                                                        \
	std::uint32_t                                           padC2C;                                   /* C2C */                                                                                                        \
	VR_PLAYER_TARGET_LOC                                    queuedTargetLoc;                          /* C30 */                                                                                                        \
	BSSoundHandle                                           unusedSound;                              /* C80 - Only place it is set is an unused function */                                                           \
	BSSoundHandle                                           magicFailureSound;                        /* C8C */                                                                                                        \
	BSSoundHandle                                           shoutFailureSound;                        /* C98 */                                                                                                        \
	std::uint32_t                                           unkCA4;                                   /* CA4 */                                                                                                        \
	DialoguePackage*                                        closestConversation;                      /* CA8 */                                                                                                        \
	std::uint64_t                                           unkCB0;                                   /* CB0 */                                                                                                        \
	DialoguePackage*                                        aiConversationRunning;                    /* CB8 */                                                                                                        \
	std::int32_t                                            numberofStealWarnings;                    /* CC0 */                                                                                                        \
	float                                                   stealWarningTimer;                        /* CC4 */                                                                                                        \
	std::uint32_t                                           numberofPickpocketWarnings;               /* CC8 - Guess */                                                                                                \
	float                                                   pickPocketWarningTimer;                   /* CCC */                                                                                                        \
	AITimeStamp                                             warnToLeaveTimeStamp;                     /* CD0 */                                                                                                        \
	std::uint32_t                                           unkCD4;                                   /* CD4 */                                                                                                        \
	ImageSpaceModifierInstanceDOF*                          ironsightsDOFInstance;                    /* CD8 */                                                                                                        \
	ImageSpaceModifierInstanceDOF*                          vatsDOFInstance;                          /* CE0 */                                                                                                        \
	ImageSpaceModifierInstanceDOF*                          dynamicDOFInstance;                       /* CE8 */                                                                                                        \
	float                                                   dynamicDOFFocusTime;                      /* CF0 */                                                                                                        \
	bool                                                    dynamicDOFFocused;                        /* CF4 */                                                                                                        \
	NiPoint3                                                dynamicDOFLastAngle;                      /* CF8 */                                                                                                        \
	NiPoint3                                                dynamicDOFLastPosition;                   /* D04 */                                                                                                        \
	TESFaction*                                             currentPrisonFaction;                     /* D10 */                                                                                                        \
	std::int32_t                                            jailSentence;                             /* D18 */                                                                                                        \
	std::int32_t                                            unkD1C;                                   /* D18 */                                                                                                        \
	std::uint64_t                                           unkD20;                                   /* D20 */                                                                                                        \
	QueuedWeapon                                            queuedWeaponAttachs[WEAPON_TYPE::kTotal]; /* D28 - Weapons attach to PlayerCharacter on next frame */                                                      \
	std::uint32_t                                           vampireFeedDetection;                     /* DC8 */                                                                                                        \
	std::uint32_t                                           mapMarkerIterator;                        /* DCC */                                                                                                        \
	RefHandle                                               forceActivateRef;                         /* DD0 */                                                                                                        \
	PlayerActionObject                                      playerActionObjects[0xF];                 /* DD4 */                                                                                                        \
	PLAYER_ACTION                                           mostRecentAction;                         /* E88 */                                                                                                        \
	ActorHandle                                             actorDoingPlayerCommand;                  /* E8C */                                                                                                        \
	std::uint64_t                                           unkE90;                                   /* E90 */                                                                                                        \
	VRGrabData                                              grabbedObjectData[VR_DEVICE::kTotal];     /* E98 - */                                                                                                      \
	float                                                   unkFD0;                                   /* FD0 - Not grabDistance as expected in SE */                                                                   \
	float                                                   unkFloatFD4;                              /* FD4 */                                                                                                        \
	std::uint64_t                                           unkFD8;                                   /* FD8 */                                                                                                        \
	VR_INFO_RUNTIME_DATA_CONTENT;                                                                     /* FE0 */                                                                                                        \
	std::uint8_t                                   unk1120[0xA0];                                     /* 1120 - Unused? */                                                                                             \
	std::uint32_t                                  unkAC0;                                            /* 11C0 */                                                                                                       \
	std::uint32_t                                  unkAC4;                                            /* 11C4 */                                                                                                       \
	BGSLocation*                                   currentLocation;                                   /* 11C8 */                                                                                                       \
	AITimeStamp                                    cachedVelocityTimeStamp;                           /* 11D0 */                                                                                                       \
	float                                          telekinesisDistance;                               /* 11D4 */                                                                                                       \
	float                                          commandTimer;                                      /* 11D8 */                                                                                                       \
	float                                          sunGazeTimer;                                      /* 11DC - Upon sungazing, counts down from 0.5 seconds. When 0, applies imagespace modifier */                   \
	TESImageSpaceModifier*                         sunGazeImageSpaceModifier;                         /* 11E0 */                                                                                                       \
	ActorValue                                     advanceSkill;                                      /* 11E8 - advance values set, then cleared in PlayerSkills::ModSkillPoints surronding ApplyPerkEntry */          \
	std::uint32_t                                  advanceAction;                                     /* 11EC - Part of 10F0 and 11E8 */                                                                               \
	stl::enumeration<DEFAULT_OBJECT, std::int32_t> animationObjectAction;                             /* 11F0 */                                                                                                       \
	GAME_STATE_DATA_CONTENT;                                                                          /* 11F4 */                                                                                                       \
	Crime*               resistArrestCrime;                                                           /* 1200 */                                                                                                       \
	BSTArray<TintMask*>  tintMasks;                                                                   /* 1208 */                                                                                                       \
	BSTArray<TintMask*>* overlayTintMasks;                                                            /* 1220 */                                                                                                       \
	RACE_DATA_CONTENT;                                                                                /* 1228 */                                                                                                       \
	std::uint64_t          unk1240[0x11];                                                             /* 1240 */                                                                                                       \
	PreTransformationData* preTransformationData;                                                     /* 12C8 - Stores equipped data when transforming to vampire/werewolf, cleared when transforming back to human */ \
	PlayerFlags            playerFlags;                                                               /* 12D0 */
            VR_PLAYER_RUNTIME_DATA_CONTENT
		};

		[[nodiscard]] inline PLAYER_RUNTIME_DATA& GetPlayerRuntimeData() noexcept
		{
			return REL::RelocateMemberIfNewer<PLAYER_RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x3D8, 0x3E0);
		}

		[[nodiscard]] inline const PLAYER_RUNTIME_DATA& GetPlayerRuntimeData() const noexcept
		{
			return REL::RelocateMemberIfNewer<PLAYER_RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x3D8, 0x3E0);
		}

		[[nodiscard]] inline VR_PLAYER_RUNTIME_DATA& GetVRPlayerRuntimeData() noexcept
		{
			return REL::RelocateMember<VR_PLAYER_RUNTIME_DATA>(this, 0, 0x3E0);
		}

		[[nodiscard]] inline const VR_PLAYER_RUNTIME_DATA& GetVRPlayerRuntimeData() const noexcept
		{
			return REL::RelocateMember<VR_PLAYER_RUNTIME_DATA>(this, 0, 0x3E0);
		}

		[[nodiscard]] inline CrimeValue& GetCrimeValue() noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
				if (REL::Module::get().version().compare(SKSE::RUNTIME_SSE_1_6_629) != std::strong_ordering::less) {
					return REL::RelocateMember<CrimeValue>(this, 0x3E8);
				}
			}
			return REL::RelocateMember<CrimeValue>(this, 0x3E0, 0x9D0);
		}

		[[nodiscard]] inline const CrimeValue& GetCrimeValue() const noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
				if (REL::Module::get().version().compare(SKSE::RUNTIME_SSE_1_6_629) != std::strong_ordering::less) {
					return REL::RelocateMember<CrimeValue>(this, 0x3E8);
				}
			}
			return REL::RelocateMember<CrimeValue>(this, 0x3E0, 0x9D0);
		}

		[[nodiscard]] inline RaceData& GetRaceData() noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
				if (REL::Module::get().version().compare(SKSE::RUNTIME_SSE_1_6_629) != std::strong_ordering::less) {
					return REL::RelocateMember<RaceData>(this, 0xB38);
				}
			}
			return REL::RelocateMember<RaceData>(this, 0xB30, 0x1228);
		}

		[[nodiscard]] inline const RaceData& GetRaceData() const noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
				if (REL::Module::get().version().compare(SKSE::RUNTIME_SSE_1_6_629) != std::strong_ordering::less) {
					return REL::RelocateMember<RaceData>(this, 0xB38);
				}
			}
			return REL::RelocateMember<RaceData>(this, 0xB30, 0x1228);
		}

		[[nodiscard]] inline GameStateData& GetGameStatsData() noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
				if (REL::Module::get().version().compare(SKSE::RUNTIME_SSE_1_6_629) != std::strong_ordering::less) {
					return REL::RelocateMember<GameStateData>(this, 0xB00);
				}
			}
			return REL::RelocateMember<GameStateData>(this, 0xAF8, 0x11F4);
		}

		[[nodiscard]] inline const GameStateData& GetGameStatsData() const noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
				if (REL::Module::get().version().compare(SKSE::RUNTIME_SSE_1_6_629) != std::strong_ordering::less) {
					return REL::RelocateMember<GameStateData>(this, 0xB00);
				}
			}
			return REL::RelocateMember<GameStateData>(this, 0xAF8, 0x11F4);
		}

		[[nodiscard]] inline INFO_RUNTIME_DATA& GetInfoRuntimeData() noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
				if (REL::Module::get().version().compare(SKSE::RUNTIME_SSE_1_6_629) != std::strong_ordering::less) {
					return REL::RelocateMember<INFO_RUNTIME_DATA>(this, 0x8D8);
				}
			}
			return REL::RelocateMember<INFO_RUNTIME_DATA>(this, 0x8E4, 0);
		}

		[[nodiscard]] inline const INFO_RUNTIME_DATA& GetInfoRuntimeData() const noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
				if (REL::Module::get().version().compare(SKSE::RUNTIME_SSE_1_6_629) != std::strong_ordering::less) {
					return REL::RelocateMember<INFO_RUNTIME_DATA>(this, 0x8DC);
				}
			}
			return REL::RelocateMember<INFO_RUNTIME_DATA>(this, 0x8E4, 0);
		}

		[[nodiscard]] VR_INFO_RUNTIME_DATA* GetVRInfoRuntimeData() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return &REL::RelocateMember<VR_INFO_RUNTIME_DATA>(this, 0, 0xFE0);
			}
		}

		[[nodiscard]] const VR_INFO_RUNTIME_DATA* GetVRInfoRuntimeData() const noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return &REL::RelocateMember<VR_INFO_RUNTIME_DATA>(this, 0, 0xFE0);
			}
		}
		[[nodiscard]] VR_NODE_DATA* GetVRNodeData() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return &REL::RelocateMember<VR_NODE_DATA>(this, 0, 0x3F0);
			}
		}

		[[nodiscard]] const VR_NODE_DATA* GetVRNodeData() const noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return &REL::RelocateMember<VR_NODE_DATA>(this, 0, 0x3F0);
			}
		}

		// members
#if !defined(ENABLE_SKYRIM_VR)
		PLAYER_RUNTIME_DATA_CONTENT
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		VR_PLAYER_RUNTIME_DATA_CONTENT
#elif (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_VR))
#endif

	private:
		bool CenterOnCell_Impl(const char* a_cellName, RE::TESObjectCELL* a_cell);
	};
#if !defined(ENABLE_SKYRIM_VR)
	static_assert(sizeof(PlayerCharacter) == 0x880);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(PlayerCharacter) == 0x12D8);
#else
	static_assert(sizeof(PlayerCharacter) == 0x78);
#endif
}
#undef PLAYER_RUNTIME_DATA_CONTENT
#undef VR_PLAYER_RUNTIME_DATA_CONTENT
#undef VR_NODE_DATA_CONTENT
#undef GRAB_DATA_CONTENT
#undef INFO_RUNTIME_DATA_CONTENT
#undef VR_INFO_RUNTIME_DATA_CONTENT
#undef GAME_STATE_DATA_CONTENT
#undef RACE_DATA_CONTENT
