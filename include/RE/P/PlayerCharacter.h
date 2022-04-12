#pragma once

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
#include "RE/F/FormTypes.h"
#include "RE/H/hkRefPtr.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTMap.h"
#include "RE/P/PositionPlayerEvent.h"

namespace RE
{
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
	class TESObjectREFR;
	class TintMask;
	class UserEventEnabledEvent;
	struct BGSActorCellEvent;
	struct BGSActorDeathEvent;
	struct PerkRankData;
	struct PositionPlayerEvent;
	struct TESQuestStageItem;
	struct TESTrackedStatsEvent;

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
	NiPointer<NiNode>          unkNode570;                      /* 570 */                                                                                                     \
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
	std::uint64_t              unk5C0;                          /* 5C0 */                                                                                                     \
	NiPointer<NiNode>          BowAimNode;                      /* 5C8 */                                                                                                     \
	NiPointer<NiNode>          BowRotationNode;                 /* 5D0 */                                                                                                     \
	NiPointer<NiNode>          ArrowSnapNode;                   /* 5D8 */                                                                                                     \
	NiPointer<BSFadeNode>      ArrowNode;                       /* 5E0 */                                                                                                     \
	NiPointer<BSFadeNode>      ArrowFireNode;                   /* 5E8 */                                                                                                     \
	std::uint64_t              unk5F0;                          /* 5F0 */                                                                                                     \
	NiPointer<NiNode>          ArrowHoldOffsetNode;             /* 5F8 */                                                                                                     \
	NiPointer<NiNode>          ArrowHoldNode;                   /* 600 */                                                                                                     \
	std::uint64_t              unk608;                          /* 608 */                                                                                                     \
	float                      unkFloat610;                     /* 610 */                                                                                                     \
	std::uint32_t              unk614;                          /* 614 */                                                                                                     \
	std::uint64_t              unk618;                          /* 618 */                                                                                                     \
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

	class PLAYER_TARGET_LOC
	{
	public:
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
		public Character,                            // 000
		public BSTEventSource<BGSActorCellEvent>,    // 2D0
		public BSTEventSource<BGSActorDeathEvent>,   // 328
		public BSTEventSource<PositionPlayerEvent>,  // 380
		public BSTEventSink<MenuOpenCloseEvent>,     // 2B0
		public BSTEventSink<MenuModeChangeEvent>,    // 2B8
		public BSTEventSink<UserEventEnabledEvent>,  // 2C0
		public BSTEventSink<TESTrackedStatsEvent>    // 2C8
	{
	public:
		inline static auto           RTTI = RTTI_PlayerCharacter;
		inline static auto           VTABLE = VTABLE_PlayerCharacter;
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
			kHandsBound = 1 << 2
		};

		enum class FlagBD9
		{
			kNone = 0,
			kIsSleeping = 1 << 2,
			kGreetingPlayer = 1 << 6
		};

		enum class FlagBDB
		{
			kNone = 0,
			kIsInCombat = 1 << 5
		};

		enum class FlagBDC
		{
			kNone = 0,
			kHealthTutorialShown = 1 << 3,
			kMagickaTutorialShown = 1 << 4,
			kStaminaTutorialShown = 1 << 5,
			kGoToJailQueued = 1 << 6
		};

		enum class FlagBDD
		{
			kNone = 0,
			kSprinting = 1 << 0,
			kDragonRideTargetLocked = 1 << 2,
			kEverModded = 1 << 3,
			kServingJailTime = 1 << 4
		};

		struct Data928
		{
		public:
			// members
			BSTArray<UnkValue> unk00;  // 00
			BSTArray<UnkValue> unk18;  // 18
			std::uint64_t      unk30;  // 30
			std::uint64_t      unk38;  // 38
			std::uint64_t      unk40;  // 40
		};
		static_assert(sizeof(Data928) == 0x48);

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
#define GAME_STATE_DATA_CONTENT                                          \
	std::int32_t                                  difficulty;    /* 0 */ \
	std::uint32_t                                 unk4;          /* 4 */ \
	std::int8_t                                   murder;        /* 8 */ \
	std::int8_t                                   perkCount;     /* 9 */ \
	stl::enumeration<ByCharGenFlag, std::uint8_t> byCharGenFlag; /* A */ \
	std::uint8_t                                  padB;          /* B */

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

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                          \
	float                      grabDistance;                                /* 000 */ \
	float                      unk004;                                      /* 004 */ \
	std::uint64_t              unk008;                                      /* 008 */ \
	std::uint32_t              unk010;                                      /* 010 */ \
	std::uint32_t              sleepSeconds;                                /* 014 */ \
	BSTSmartPointer<BipedAnim> largeBiped;                                  /* 018 */ \
	NiPointer<NiNode>          firstPerson3D;                               /* 020 */ \
	float                      eyeHeight;                                   /* 028 */ \
	float                      greetTimer;                                  /* 02C */ \
	float                      encumberedTimer;                             /* 030 */ \
	float                      powerAttackTimer;                            /* 034 */ \
	std::int32_t               hoursToSleep;                                /* 038 */ \
	std::int32_t               amountStolenSold;                            /* 03C */ \
	std::uint32_t              valueStolen;                                 /* 040 */ \
	ActorHandle                lastRiddenMount;                             /* 044 */ \
	ActorHandle                lightTarget;                                 /* 048 */ \
	float                      sortActorDistanceTimer;                      /* 04C */ \
	float                      sitHeadingDelta;                             /* 050 */ \
	std::uint32_t              unk054;                                      /* 054 */ \
	Data928*                   unk058;                                      /* 058 */ \
	std::uint32_t              skillTrainingsThisLevel;                     /* 060 */ \
	std::uint32_t              unk064;                                      /* 064 */ \
	TESClass*                  defaultClass;                                /* 068 */ \
	std::uint64_t              unk070;                                      /* 070 */ \
	std::uint32_t              crimeCounts[PackageNS::CRIME_TYPES::kTotal]; /* 078 */ \
	std::uint32_t              unk094;                                      /* 094 */ \
	AlchemyItem*               pendingPoison;                               /* 098 */ \
	std::int64_t               lastPlayingTimeUpdate;                       /* 0A0 */ \
	std::int64_t               totalPlayingTime;                            /* 0A8 */ \
	std::int32_t               characterSeed;                               /* 0B0 */ \
	std::uint32_t              unk0B4;                                      /* 0B4 */ \
	TESForm*                   lastKnownGoodLocation;                       /* 0B8 */ \
	std::uint32_t              unk0C0;                                      /* 0C0 */ \
	std::uint32_t              unk0C4;                                      /* 0C4 */ \
	NiPointer<BSLight>         firstPersonLight;                            /* 0C8 */ \
	NiPointer<BSLight>         thirdPersonLight;                            /* 0D0 */ \
	float                      dropAngleMod;                                /* 0D8 */ \
	float                      lastDropAngleMod;                            /* 0DC */ \
	PlayerSkills*              skills;                                      /* 0E0 */ \
	ActorHandle                autoAimActor;                                /* 0E8 */ \
	RefHandle                  unk0EC;                                      /* 0EC */ \
	std::uint64_t              unk118;                                      /* 0F0 */ \
	NiPointer<NiAVObject>      targeted3D;                                  /* 0F8 */ \
	CombatGroup*               combatGroup;                                 /* 100 */ \
	BSTArray<ActorHandle>      actorsToDisplayOnTheHUDArray;                /* 108 */ \
	std::uint64_t              unk120;                                      /* 120 */ \
	TESBoundObject*            lastOneHandItems[2];                         /* 128 */ \
	std::uint32_t              teammateCount;                               /* 138 */ \
	float                      combatTimer;                                 /* 13C */ \
	float                      yieldTimer;                                  /* 140 */ \
	float                      chaseTimer;                                  /* 144 */ \
	float                      drawSheatheSafetyTimer;                      /* 148 */ \
	std::uint32_t              unk14C;                                      /* 14C */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x150);

		~PlayerCharacter() override;  // 000

		// add
		void          Unk_12A(void);                                                   // 12A
		std::uint32_t GetViolentCrimeGoldValue(const TESFaction* a_faction) const;     // 12B
		std::uint32_t GetNonViolentCrimeGoldValue(const TESFaction* a_faction) const;  // 12C
		void          ClearAllCrimeGold(TESFaction* a_faction);                        // 12D
		void          Unk_12E(void);                                                   // 12E - { return 0; }

		static PlayerCharacter* GetSingleton();

		void                     ActivatePickRef();
		void                     AddSkillExperience(ActorValue a_skill, float a_experience);
		bool                     AttemptPickpocket(TESObjectREFR* a_containerRef, InventoryEntryData* a_entry, std::int32_t a_number, bool a_fromContainer = true);
		bool                     CenterOnCell(const char* a_cellName);
		bool                     CenterOnCell(RE::TESObjectCELL* a_cell);
		NiPointer<Actor>         GetActorDoingPlayerCommand() const;
		float                    GetArmorValue(InventoryEntryData* a_form);
		float                    GetDamage(InventoryEntryData* a_form);
		NiPointer<TESObjectREFR> GetGrabbedRef();
		std::uint32_t            GetNumTints(std::uint32_t a_tintType);
#ifndef ENABLE_SKYRIM_VR
		TintMask*            GetOverlayTintMask(TintMask* a_original);
		BSTArray<TintMask*>& GetTintList();
		TintMask*            GetTintMask(std::uint32_t a_tintType, std::uint32_t a_index);
#endif
		bool HasActorDoingCommand() const;
		bool IsGrabbing() const;
		void PlayPickupEvent(TESForm* a_item, TESForm* a_containerOwner, TESObjectREFR* a_containerRef, EventType a_eventType);
		void StartGrabObject();

		template <class T>
		inline BSTEventSource<T>* GetEventSource()
		{
			return static_cast<BSTEventSource<T>*>(this);
		}

		template <class T>
		inline void AddEventSink(BSTEventSink<T>* a_sink)
		{
			GetEventSource<T>()->AddEventSink(a_sink);
		}

		[[nodiscard]] inline CrimeValue& GetCrimeValue() noexcept
		{
			return REL::RelocateMember<CrimeValue>(this, 0x3E0, 0x9D0);
		}

		[[nodiscard]] inline const CrimeValue& GetCrimeValue() const noexcept
		{
			return REL::RelocateMember<CrimeValue>(this, 0x3E0, 0x9D0);
		}

		[[nodiscard]] inline RaceData& GetRaceData() noexcept
		{
			return REL::RelocateMember<RaceData>(this, 0xB30, 0x1228);
		}

		[[nodiscard]] inline const RaceData& GetRaceData() const noexcept
		{
			return REL::RelocateMember<RaceData>(this, 0xB30, 0x1228);
		}

		[[nodiscard]] inline GameStateData& GetGameStatsData() noexcept
		{
			return REL::RelocateMember<GameStateData>(this, 0xAF8, 0x11F4);
		}

		[[nodiscard]] inline const GameStateData& GetGameStatsData() const noexcept
		{
			return REL::RelocateMember<GameStateData>(this, 0xAF8, 0x11F4);
		}

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x8D0, 0xFD0);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x8D0, 0xFD0);
		}

		[[nodiscard]] VR_NODE_DATA* GetVRNodeData() noexcept
		{
			if (!REL::Module::get().IsVR()) {
				return nullptr;
			}
			return &REL::RelocateMember<VR_NODE_DATA>(this, 0, 0x3F0);
		}

		[[nodiscard]] const VR_NODE_DATA* GetVRNodeData() const noexcept
		{
			if (!REL::Module::get().IsVR()) {
				return nullptr;
			}
			return &REL::RelocateMember<VR_NODE_DATA>(this, 0, 0x3F0);
		}

		// members
#ifndef ENABLE_SKYRIM_VR                                                                     // Non-VR
		std::uint32_t unk3D8;                                                                // 3D8
		std::uint32_t unk3DC;                                                                // 3DC
		CRIME_VALUE_CONTENT;                                                                 // 3E0
		ObjectRefHandle                                         commandWaitMarker;           // 440
		std::uint32_t                                           unk444;                      // 444
		BSTHashMap<const TESFaction*, FriendshipFactionsStruct> factionOwnerFriendsMap;      // 448
		NiPoint3                                                lastKnownGoodPosition;       // 478
		NiPoint3                                                bulletAutoAim;               // 484
		NiPoint3                                                cachedVelocity;              // 490
		float                                                   unk49C;                      // 49C
		std::uint64_t                                           unk4A0;                      // 4A0
		std::uint64_t                                           unk4A8;                      // 4A8
		BSTArray<PerkRankData*>                                 addedPerks;                  // 4B0
		BSTArray<BGSPerk*>                                      perks;                       // 4C8
		BSTArray<BGSPerk*>                                      standingStonePerks;          // 4E0
		BSTArray<ObjectRefHandle>                               currentMapMarkers;           // 4F8
		BSTArray<BSTTuple<NiPoint3, AITimeStamp>>               velocityArray;               // 510
		BSTArray<ProjectileHandle>                              runesCast;                   // 528
		BSTArray<void*>                                         imageSpaceModifierAnims1;    // 540
		BSTArray<void*>                                         imageSpaceModifierAnims2;    // 558
		BSSimpleList<TESQuestStageItem*>                        questLog;                    // 570
		BSTArray<BGSInstancedQuestObjective>                    objectives;                  // 580
		BSTHashMap<UnkKey, UnkValue>                            unk598;                      // 598
		BSTHashMap<UnkKey, UnkValue>                            currentSayOnceInfosMap;      // 5C8
		BSSimpleList<ObjectRefHandle>                           droppedRefList;              // 5F8
		NiTMap<std::uint32_t, std::uint8_t>                     randomDoorSpaceMap;          // 608
		TESWorldSpace*                                          cachedWorldSpace;            // 628
		NiPoint3                                                exteriorPosition;            // 630
		std::uint32_t                                           unk63C;                      // 63C
		PLAYER_TARGET_LOC                                       queuedTargetLoc;             // 640
		BSSoundHandle                                           unk688;                      // 688
		BSSoundHandle                                           magicFailureSound;           // 694
		BSSoundHandle                                           unk6A0;                      // 6A0
		std::uint32_t                                           pad6AC;                      // 6AC
		DialoguePackage*                                        closestConversation;         // 6B0
		std::uint32_t                                           unk6B8;                      // 6B8
		std::uint32_t                                           unk6BC;                      // 6BC
		DialoguePackage*                                        aiConversationRunning;       // 6C0
		std::int32_t                                            numberofStealWarnings;       // 6C8
		float                                                   stealWarningTimer;           // 6CC
		std::int32_t                                            numberofPickpocketWarnings;  // 6D0
		float                                                   pickPocketWarningTimer;      // 6D4
		AITimeStamp                                             warnToLeaveTimeStamp;        // 6D8
		std::uint32_t                                           pad6DC;                      // 6DC
		ImageSpaceModifierInstanceDOF*                          ironsightsDOFInstance;       // 6E0
		ImageSpaceModifierInstanceDOF*                          vatsDOFInstance;             // 6E8
		ImageSpaceModifierInstanceDOF*                          dynamicDOFInstance;          // 6F0
		float                                                   dynamicDOFFocusTime;         // 6F8
		bool                                                    dynamicDOFFocused;           // 6FC
		std::uint8_t                                            unk6FD;                      // 6FD
		std::uint16_t                                           unk6FE;                      // 6FE
		NiPoint3                                                dynamicDOFLastAngle;         // 700
		NiPoint3                                                dynamicDOFLastPosition;      // 70C
		TESFaction*                                             currentPrisonFaction;        // 718
		std::int32_t                                            jailSentence;                // 720
		std::uint32_t                                           pad724;                      // 724
		void*                                                   unk728;                      // 728 - smart ptr
		std::uint8_t                                            unk730[0xA0];                // 730
		std::int32_t                                            vampireFeedDetection;        // 7D0
		std::uint32_t                                           mapMarkerIterator;           // 7D4
		RefHandle                                               forceActivateRef;            // 7D8
		PlayerActionObject                                      playerActionObjects[15];     // 7DC
		PLAYER_ACTION                                           mostRecentAction;            // 890
		ActorHandle                                             actorDoingPlayerCommand;     // 894
		BSTSmallArray<hkRefPtr<bhkMouseSpringAction>, 4>        grabSpring;                  // 898
		ObjectRefHandle                                         grabbedObject;               // 8C8
		float                                                   grabObjectWeight;            // 8CC
		RUNTIME_DATA_CONTENT;                                                                // 8D0
		std::uint8_t                                  unkA20[0xA0];                          // A20
		std::uint32_t                                 unkAC0;                                // AC0
		std::uint32_t                                 unkAC4;                                // AC4
		BGSLocation*                                  currentLocation;                       // AC8
		AITimeStamp                                   cachedVelocityTimeStamp;               // AD0
		float                                         telekinesisDistance;                   // AD4
		float                                         commandTimer;                          // AD8
		std::uint32_t                                 unkADC;                                // ADC
		TESImageSpaceModifier*                        unkAE0;                                // AE0
		std::int32_t                                  unkAE8;                                // AE8
		std::uint32_t                                 unkAEC;                                // AEC
		std::uint32_t                                 unkAF0;                                // AF0
		stl::enumeration<GrabbingType, std::uint32_t> grabType;                              // AF4
		GAME_STATE_DATA_CONTENT;                                                             // AF8
		std::uint32_t        unkB04;                                                         // B04
		Crime*               resistArrestCrime;                                              // B08
		BSTArray<TintMask*>  tintMasks;                                                      // B10
		BSTArray<TintMask*>* overlayTintMasks;                                               // B28
		RACE_DATA_CONTENT;                                                                   // B30
		std::int32_t                            unkB48;                                      // B48
		std::uint32_t                           padB4C;                                      // B4C
		BSTArray<std::uint64_t>                 unkB50;                                      // B50
		std::uint64_t                           unkB68;                                      // B68
		std::uint64_t                           unkB70;                                      // B70
		std::uint64_t                           unkB78;                                      // B78
		std::uint64_t                           unkB80;                                      // B80
		std::int32_t                            unkB88;                                      // B88
		std::uint32_t                           padB8C;                                      // B8C
		std::uint64_t                           unkB90;                                      // B90
		std::uint64_t                           unkB98;                                      // B98
		BSTSmallArray<void*, 4>                 unkBA0;                                      // BA0
		std::uint64_t                           unkBD0;                                      // BD0
		std::uint8_t                            unkBD8;                                      // BD8
		stl::enumeration<FlagBD9, std::uint8_t> unkBD9;                                      // BD9
		std::uint8_t                            unkBDA;                                      // BDA
		stl::enumeration<FlagBDB, std::uint8_t> unkBDB;                                      // BDB
		stl::enumeration<FlagBDC, std::uint8_t> unkBDC;                                      // BDC
		stl::enumeration<FlagBDD, std::uint8_t> unkBDD;                                      // BDD
		std::uint16_t                           padBDE;                                      // BDE
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)                               // VR
		std::uint64_t unk3D8;        // 3D8
		std::uint64_t unk3E0;        // 3E0
		std::uint64_t unk3E8;        // 3E8
		VR_NODE_DATA_CONTENT;        // 3F0
		std::uint64_t unk680;        // 680
		std::uint64_t unk688;        // 688
		std::uint64_t unk690;        // 690
		std::uint64_t unk698;        // 698
		std::uint64_t unk6A0;        // 6A0
		std::uint64_t unk6A8[0x65];  // 6A8
		CRIME_VALUE_CONTENT;         // 9D0
		std::uint64_t unkA30[0x11];  // A30
		void*         perkArray;     // AB8
		std::uint64_t unk6C0[0x14];  // AC0
		//BSTArray<PerkRankData*>								addedPerks;									  // B60
		//BSTArray<BGSPerk*>									perks;										  // B68
		//BSTArray<BGSPerk*>									standingStonePerks;							  // B70
		std::uint64_t addedPerks;                // B60 // these 3 here gotta be fixed
		std::uint64_t perks;                     // B68
		std::uint64_t standingStonePerks;        // B70
		std::uint64_t unkB78;                    // B78
		std::uint64_t unkB80;                    // B80
		std::uint64_t unkMessageArrayPtr;        // B88
		std::uint64_t unkB90;                    // B90
		std::uint64_t unkB98;                    // B98
		std::uint64_t unkBA0;                    // BA0
		std::uint64_t unkBA8;                    // BA8
		std::uint64_t unkBB0[0x25];              // BB0
		std::uint64_t imageSpaceModifierAnims1;  // CD8 - Wrong Datatype from Below
		std::uint64_t imageSpaceModifierAnims2;  // CE0 - Wrong Datatype from below
		std::uint64_t unkCE8[0x34];              // CE8
		std::uint32_t padE90;                    // E88
		ActorHandle   actorDoingPlayerCommand;   // E8C
		std::uint64_t unkE90;                    // E90
		std::uint64_t unkE98[0x27];              // E98
												 //		BSTSmallArray<hkRefPtr<bhkMouseSpringAction>, 4>		grabSpring;                                   // F00    // not used in vr as far as i can tell   F08??????
		RUNTIME_DATA_CONTENT;                    // FD0
		std::uint64_t unk1120[0x1A];             // 1120
		std::uint32_t unk11F0;                   // 11F0
		GAME_STATE_DATA_CONTENT;                 // 11F4
		std::uint64_t unk1200;                   // 1200
		std::uint64_t unk1208;                   // 1208
		std::uint64_t unk1210;                   // 1210
		std::uint64_t unk1218;                   // 1218
		std::uint64_t unk1220;                   // 1220
		RACE_DATA_CONTENT;                       // 1228
		std::uint64_t unk1240[0x12];             // 1240
		std::uint8_t  pad12D0;                   // 12D0
		std::uint8_t  flags;                     // 12D1  -- TODO MAP THESE FLAGS OUT
		std::uint16_t pad12D2;                   // 12D2
		std::uint32_t unk12D4;                   // 12D4
#endif

	private:
		bool CenterOnCell_Impl(const char* a_cellName, RE::TESObjectCELL* a_cell);
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(PlayerCharacter) == 0xBE0);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(PlayerCharacter) == 0x12D8);
#else
	static_assert(sizeof(PlayerCharacter) == 0x3D8);
#endif
}
#undef VR_NODE_DATA_CONTENT
#undef RUNTIME_DATA_CONTENT
#undef GAME_STATE_DATA_CONTENT
#undef RACE_DATA_CONTENT
