#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESCondition.h"
#include "RE/T/TESForm.h"

namespace RE
{
	class BGSIdleCollection;
	class PackageLocation;
	class TESPackageData;

	enum class PACKAGE_OBJECT_TYPE
	{
		kNone = 0,
		kACTI = 1,
		kARMO = 2,
		kBOOK = 3,
		kCONT = 4,
		kDOOR = 5,
		kINGR = 6,
		kLIGH = 7,
		kMISC = 8,
		kFLOR = 9,
		kFURN = 10,
		kWEAP = 11,
		kAMMO = 12,
		kKEYM = 13,
		kALCH = 14,
		kFOOD = 15
	};

	enum class PACKAGE_TYPE
	{
		kNone = static_cast<std::underlying_type_t<PACKAGE_TYPE>>(-1),
		kExplore = 0,
		kFollow = 1,
		kEscort = 2,
		kEat = 3,
		kSleep = 4,
		kWander = 5,
		kTravel = 6,
		kAccompany = 7,
		kUseItemAt = 8,
		kAmbush = 9,
		kFleeNotCombat = 10,
		kCastMagic = 11,
		kSandbox = 12,
		kPatrol = 13,
		kGuard = 14,
		kDialogue = 15,
		kUseWeapon = 16,
		kFind = 17,
		kPackage = 18,
		kPackageTemplate = 19,
		kActivate = 20,
		kAlarm = 21,
		kFlee = 22,
		kTrespass = 23,
		kSpectator = 24,
		kReactToDead = 25,
		kGetUpFromChairBed = 26,
		kDoNothing = 27,
		kInGameDialogue = 28,
		kSurface = 29,
		kSearchForAttacker = 30,
		kAvoidPlayer = 31,
		kReactToDestroyedObject = 32,
		kReactToGrenadeOrMine = 33,
		kStealWarning = 34,
		kPickPocketWarning = 35,
		kMovementBlocked = 36,
		kVampireFeed = 37,
		kCannibal = 38,
		kLanding = 39,
		kUnused = 40,
		kMountActor = 41,
		kDismountActor = 42,
		kClearMountPosition = 43,

		kTotal = 44
	};

	enum class PACKAGE_PROCEDURE_TYPE
	{
		kNone = static_cast<std::underlying_type_t<PACKAGE_PROCEDURE_TYPE>>(-1),
		kExploreTravel = 0,
		kExploreWander = 1,
		ExploreActivate = 2,
		kExploreAcquire = 3,
		kSleep = 4,
		kEat = 5,
		kFollowWithEscort = 6,
		kAmbushFollow = 7,
		kEscortActor = 8,
		kEscortObject = 9,
		kDialogue = 10,
		kAlarm = 11,
		kActivate = 12,
		kGreet = 13,
		kObserveCombat = 14,
		kObserveDialogue = 15,
		kTalkToDead = 16,
		kFlee = 17,
		kTrespass = 18,
		kGetUpFromChairBed = 19,
		kExploreNPC = 20,
		kMountActor = 21,
		kDismountActor = 22,
		kDoNothing = 23,
		kExploreAcquireGeneric = 24,
		kAccompany = 25,
		kUseItemAt = 26,
		kVampireFeed = 27,
		kAmbush = 28,
		kSurface = 29,
		kFleeNotCombat = 30,
		kSearchForAttacker = 31,
		kClearMountPosition = 32,
		kWaitForDialogue = 33,
		kAvoidPlayer = 34,
		kSandbox = 35,
		kPatrol = 36,
		kReactToDestroyedObject = 37,
		kReactToGrenadeOrMine = 38,
		kGuard = 39,
		kStealWarning = 40,
		kPickPocketWarning = 41,
		kUseWeapon = 42,
		kFollowWithoutEscort = 43,
		kMovementBlocked = 44,
		kCannibal = 45,
		kPackage = 46,
		kLanding = 47,
		kKeepAnEyeOn = 48
	};

	// One entry of a package's procedure sequence: the sequence for a PACKAGE_PROCEDURE_TYPE ends with kDone.
	// Named after the number GetCurrentAIProcedure reports for it (see CONDITION_AI_PROCEDURE).
	enum class AI_PROCEDURE_TYPE : std::uint32_t
	{
		kTravel = 0,
		kWander = 1,
		kActivate = 2,
		kAcquire = 3,
		kSleep = 4,
		kEat = 5,
		kFollow = 6,
		kEscort = 7,
		kAlarm = 8,
		kFlee = 9,
		kYield = 10,
		kDialogue = 11,
		kWait = 12,
		kTravelTarget = 13,
		kPursue = 14,
		kGreet = 15,
		kCreateFollow = 16,
		kObserveCombat = 17,
		kGreetDead = 19,
		kGetUp = 21,
		kMountHorse = 22,
		kDismountHorse = 23,
		kDoNothing = 24,
		kAccompany = 26,
		kUseItemAt = 27,
		kSandman = 28,
		kWaitAmbush = 29,
		kSurface = 30,
		kWaitForSpell = 31,
		kChooseCast = 32,
		kFleeNonCombat = 33,
		kRemoveWornItems = 34,
		kSearch = 35,
		kClearMountPosition = 36,
		kAvoidArea = 38,
		kUnequipArmor = 39,
		kTakeBackItem = 40,
		kSandbox = 41,
		kUseIdleMarker = 42,
		kPatrol = 43,
		kGuard = 46,
		kDialogueActivate = 48,
		kUseWeapon = 49,
		kMovementBlocked = 50,
		kCannibalFeed = 51,
		kDone = 54
	};

	// Result of the GetCurrentAIProcedure condition function. Names are the Fallout 3 names used on
	// https://ck.uesp.net/wiki/GetCurrentAIProcedure; 13, 25, 26 and 38 are never returned, and kNone is returned
	// for procedures with no number.
	enum class CONDITION_AI_PROCEDURE : std::int32_t
	{
		kNone = -1,
		kTravel = 0,
		kActivate = 1,
		kAcquire = 2,
		kWait = 3,
		kDialogue = 4,
		kGreet = 5,
		kGreetDead = 6,
		kWander = 7,
		kSleep = 8,
		kObserveCombat = 9,
		kEat = 10,
		kFollow = 11,
		kEscort = 12,
		kAlarm = 14,
		kPursue = 15,
		kFlee = 16,
		kDone = 17,
		kYield = 18,
		kTravelTarget = 19,
		kCreateFollow = 20,
		kGetUp = 21,
		kMountHorse = 22,
		kDismountHorse = 23,
		kDoNothing = 24,
		kAccompany = 27,
		kUseItemAt = 28,
		kSandman = 29,
		kWaitAmbush = 30,
		kSurface = 31,
		kWaitForSpell = 32,
		kChooseCast = 33,
		kFleeNonCombat = 34,
		kRemoveWornItems = 35,
		kSearch = 36,
		kClearMountPosition = 37,
		kAvoidArea = 39,
		kUnequipArmor = 40,
		kPatrol = 41,
		kUseWeapon = 42,
		kDialogueActivate = 43,
		kGuard = 44,
		kSandbox = 45,
		kUseIdleMarker = 46,
		kTakeBackItem = 47,
		kSitting = 48,
		kMovementBlocked = 49,
		kCannibalFeed = 50
	};

	// Result of the GetCurrentAIPackage condition function, by PACKAGE_TYPE.
	// This is not the PACKAGE_TYPE ordinal: Find, Package, Package Template and every type above kAvoidPlayer give kNone.
	enum class CONDITION_AI_PACKAGE : std::int32_t
	{
		kNone = -1,
		kExplore = 0,
		kFollow = 1,
		kEscort = 2,
		kEat = 3,
		kSleep = 4,
		kInGameDialogue = 6,
		kActivate = 7,
		kAlarm = 8,
		kSpectator = 9,
		kFlee = 10,
		kTrespass = 11,
		kReactToDead = 12,
		kWander = 13,
		kTravel = 14,
		kAccompany = 15,
		kUseItemAt = 16,
		kAmbush = 17,
		kFleeNotCombat = 18,
		kCastMagic = 19,
		kGetUpFromChairBed = 21,
		kDoNothing = 24,
		kSurface = 28,
		kSearchForAttacker = 29,
		kAvoidPlayer = 32,
		kUseWeapon = 33,
		kDialogue = 34,
		kGuard = 35,
		kSandbox = 36,
		kPatrol = 37
	};

	enum class PACK_EVENT_ACTION_TYPE
	{
		kBegin = 0,
		kEnd,
		kChange,
		kPatrol
	};

	enum class PACK_INTERRUPT_TARGET
	{
		kNone = static_cast<std::underlying_type_t<PACK_INTERRUPT_TARGET>>(-1),
		kSpectator = 0,
		kObserveDead = 0x1,
		kGuardWarn = 0x2,
		kCombat = 0x3
	};

	struct PACKAGE_DATA  // PKDT
	{
	public:
		enum class GeneralFlag
		{
			kNone = 0,
			kOffersServices = 1 << 0,
			kMustComplete = 1 << 2,
			kMaintainSpeedAtGoal = 1 << 3,
			kUnlocksDoorsAtPackageStart = 1 << 6,
			kUnlocksDoorsAtPackageEnd = 1 << 7,
			kContinueIfPCNear = 1 << 9,
			kOncePerDay = 1 << 10,
			kCreated = 1 << 11,
			kPreferredSpeed = 1 << 13,
			kAlwaysSneak = 1 << 17,
			kAllowSwimming = 1 << 18,
			kIgnoreCombat = 1 << 20,
			kWeaponsUnequipped = 1 << 21,
			kWeaponDrawn = 1 << 23,
			kNoCombatAlert = 1 << 27,
			kWearSleepOutfit = 1 << 29
		};

		enum class PreferredSpeed
		{
			kWalk = 0,
			kJog = 1,
			kRun = 2,
			kFastWalk = 3
		};

		enum class InterruptFlag
		{
			kNone = 0,
			kHellosToPlayer = 1 << 0,
			kRandomConversations = 1 << 1,
			kObserveCombatBehaviour = 1 << 2,
			kGreetCorpseBehaviour = 1 << 3,
			kReactionToPlayerActions = 1 << 4,
			kFriendlyFireComments = 1 << 5,
			kAggroRadiusBehavior = 1 << 6,
			kAllowIdleChatter = 1 << 7,
			kWorldInteractions = 1 << 9
		};

		// members
		REX::EnumSet<GeneralFlag, std::uint32_t>          packFlags;              // 0
		REX::EnumSet<PACKAGE_TYPE, std::uint8_t>          packType;               // 4
		REX::EnumSet<PACK_INTERRUPT_TARGET, std::uint8_t> interruptOverrideType;  // 5
		REX::EnumSet<PreferredSpeed, std::uint8_t>        maxSpeed;               // 6
		std::uint8_t                                      pad7;                   // 7
		REX::EnumSet<InterruptFlag, std::uint16_t>        foBehaviorFlags;        // 8
		std::uint16_t                                     packageSpecificFlags;   // A
	};
	static_assert(sizeof(PACKAGE_DATA) == 0xC);

	class PackageTarget
	{
	public:
		union Target
		{
			inline Target() :
				object(nullptr)
			{}

			~Target() {}

			// members
			ObjectRefHandle                                    handle;
			TESForm*                                           object;
			TESForm*                                           refOrObj;
			REX::EnumSet<PACKAGE_OBJECT_TYPE, std::uint32_t>   objType;
			std::uint32_t                                      aliasID;
			REX::EnumSet<PACK_INTERRUPT_TARGET, std::uint32_t> interruptTarg;
		};
		static_assert(sizeof(Target) == 0x8);

		// members
		std::int8_t   targType;  // 00
		std::uint8_t  pad01;     // 01
		std::uint16_t pad02;     // 02
		Target        target;    // 08
		std::int32_t  value;     // 10
		std::uint32_t pad14;     // 14
	};
	static_assert(sizeof(PackageTarget) == 0x18);

	struct PACK_SCHED_DATA
	{
		enum class DayOfWeek
		{
			kAny = -1,
			kSunday = 0,
			kMonday = 1,
			kTuesday = 2,
			kWednesday = 3,
			kThursday = 4,
			kFriday = 5,
			kSaturday = 6,
			kWeekdays = 7,
			kWeekends = 8,
			kMondayWednesdayFriday = 9,
			kTuesdayThursday = 10
		};

		// members
		std::int8_t                          month;      // 0
		REX::EnumSet<DayOfWeek, std::int8_t> dayOfWeek;  // 1
		std::int8_t                          date;       // 2
		std::int8_t                          hour;       // 3
		std::int8_t                          minute;     // 4
		std::uint8_t                         pad5;       // 5
		std::uint8_t                         pad6;       // 6
		std::uint8_t                         pad7;       // 7
		std::int32_t                         duration;   // 8 - minutes
	};
	static_assert(sizeof(PACK_SCHED_DATA) == 0xC);

	class PackageSchedule  // PSDT
	{
	public:
		// members
		PACK_SCHED_DATA psData;  // 0
	};
	static_assert(sizeof(PackageSchedule) == 0xC);

	class PackageEventAction
	{
	public:
		struct TopicData  // PDTO
		{
			enum class Type
			{
				kTopicRef = 0,
				kTopicSubtype = 1
			};

			// members
			REX::EnumSet<Type, std::uint32_t> type;   // 00
			std::uint32_t                     pad04;  // 04
			TESTopic*                         topic;  // 08
		};
		static_assert(sizeof(TopicData) == 0x10);

		// members
		TESIdleForm*                                        idle;   // 00 - INAM
		REX::EnumSet<PACK_EVENT_ACTION_TYPE, std::uint32_t> type;   // 08
		std::uint32_t                                       pad0C;  // 0C
		TopicData                                           topic;  // 10 - PDTO
	};
	static_assert(sizeof(PackageEventAction) == 0x20);

	class TESPackage : public TESForm
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESPackage;
		inline static constexpr auto VTABLE = VTABLE_TESPackage;
		inline static constexpr auto FORMTYPE = FormType::Package;

		struct ChangeFlags
		{
			enum ChangeFlag : std::uint32_t
			{
				kWaitingFlag = 1 << 26,
				kNeverRunFlag = (std::uint32_t)1 << 31
			};
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		~TESPackage() override;  // 00

		// override (TESForm)
		void                      InitializeData() override;                    // 04
		void                      ClearData() override;                         // 05
		bool                      Load(TESFile* a_mod) override;                // 06
		void                      SaveGame(BGSSaveFormBuffer* a_buf) override;  // 0E
		void                      LoadGame(BGSLoadFormBuffer* a_buf) override;  // 0F
		void                      Revert(BGSLoadFormBuffer* a_buf) override;    // 12
		void                      InitItemImpl() override;                      // 13
		std::uint32_t             GetRefCount() const override;                 // 2D - { return refCount; }
		[[nodiscard]] const char* GetObjectTypeName() const override;           // 39 - { return g_packageTypeStrings[packData.packType]; }

		// add
		[[nodiscard]] virtual bool IsActorAtLocation(Actor* a_actor, bool a_arg2, float a_arg3, bool a_arg4);                      // 3B
		[[nodiscard]] virtual bool IsActorAtSecondLocation(Actor* a_arg1, Actor* a_arg2, bool a_arg3, float a_arg4, bool a_arg5);  // 3C
		[[nodiscard]] virtual bool IsActorAtRefTarget(Actor* a_actor, std::int32_t a_arg2);                                        // 3D
		[[nodiscard]] virtual bool IsTargetAtLocation(Actor* a_actor, std::int32_t a_arg2);                                        // 3E
		[[nodiscard]] virtual bool IsPackageOwner(Actor* a_actor);                                                                 // 3F - { return true; }

		static TESPackage* CreatePackage(PACKAGE_TYPE a_type)
		{
			using func_t = decltype(&TESPackage::CreatePackage);
			static REL::Relocation<func_t> func{ RELOCATION_ID(28732, 29496) };
			return func(a_type);
		}

		void SetPackType(PACKAGE_TYPE a_type)
		{
			using func_t = decltype(&TESPackage::SetPackType);
			static REL::Relocation<func_t> func{ RELOCATION_ID(28751, 29525) };
			return func(this, a_type);
		}

		// members
		PACKAGE_DATA                                        packData;        // 20 - PKDT
		std::uint32_t                                       pad2C;           // 2C
		TESPackageData*                                     data;            // 30
		PackageLocation*                                    packLoc;         // 38
		PackageTarget*                                      packTarg;        // 40
		BGSIdleCollection*                                  idleCollection;  // 48
		PackageSchedule                                     packSched;       // 50 - PSDT
		std::uint32_t                                       pad5C;           // 5C
		TESCondition                                        packConditions;  // 60
		TESCombatStyle*                                     combatStyle;     // 68 - CNAM
		TESQuest*                                           ownerQuest;      // 70 - QNAM
		PackageEventAction                                  onBegin;         // 78
		PackageEventAction                                  onEnd;           // 98
		PackageEventAction                                  onChange;        // B8
		REX::EnumSet<PACKAGE_PROCEDURE_TYPE, std::uint32_t> procedureType;   // D8
		volatile std::uint32_t                              refCount;        // DC
	};
	static_assert(sizeof(TESPackage) == 0xE0);
}
