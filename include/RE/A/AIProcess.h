#pragma once

#include "RE/A/ActorPackage.h"
#include "RE/A/ActorValues.h"
#include "RE/B/BGSDefaultObjectManager.h"
#include "RE/B/BSResourceHandle.h"
#include "RE/B/BSSimpleList.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTObjectArena.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/P/ProcessType.h"

namespace RE
{
	enum class RESET_3D_FLAGS;
	class Actor;
	class bhkCharacterController;
	class BipedAnim;
	class InventoryEntryData;
	class NiAVObject;
	class NiPoint3;
	class TESForm;
	class TESShout;
	struct HighProcessData;
	struct MiddleHighProcessData;

	class MiddleLowProcessData
	{
	public:
		// members
		std::int32_t hourPackageEvaluated;  // 0
	};
	static_assert(sizeof(MiddleLowProcessData) == 0x4);

	struct CachedValueData
	{
	public:
		// members
		float         value;    // 0
		bool          invalid;  // 4
		std::uint8_t  pad5;     // 5
		std::uint16_t pad6;     // 6
	};
	static_assert(sizeof(CachedValueData) == 0x8);

	struct CachedValues
	{
	public:
		enum class Flags
		{
			kNone = 0,
			kRadius = 1 << 0,
			kWidth = 1 << 1,
			kLength = 1 << 2,
			kDPS = 1 << 3,
			kMedicineEffectivenessMult = 1 << 4,
			kEyeLevel = 1 << 9,
			kConditionPreventsRun = 1 << 10,
			kForwardLength = 1 << 11,
			kActorIsGhost = 1 << 20,
			kHealthDamaged = 1 << 21,
			kMagickaPointsDamaged = 1 << 22,
			kStaminaDamaged = 1 << 23,
			kOwnerIsNPC = 1 << 25,
			kOwnerIsUndead = 1 << 26,
			kOwnerIsInCombatantFaction = 1 << 27
		};

		enum class BooleanValue
		{
			kNone = 0,
			kConditionPreventsRun = 1 << 0,
			kOwnerIsNPC = 1 << 1,
			kOwnerIsUndead = 1 << 2,
			kOwnerIsInCombatantFaction = 1 << 3
		};

		float                                     cachedRadius;         // 00
		float                                     cachedWidth;          // 04
		float                                     cachedLength;         // 08
		float                                     cachedForwardLength;  // 0C
		float                                     cachedDPS;            // 10
		float                                     cachedEyeLevel;       // 14
		float                                     cachedWalkSpeed;      // 18
		float                                     cachedRunSpeed;       // 1C
		float                                     cachedJogSpeed;       // 20
		float                                     cachedFastWalkSpeed;  // 24
		REX::EnumSet<BooleanValue, std::uint32_t> booleanValues;        // 28
		REX::EnumSet<Flags, std::uint32_t>        flags;                // 2C
		BSTArray<CachedValueData>                 actorValueCache;      // 30
		BSTArray<CachedValueData>                 maxActorValueCache;   // 48
	};
	static_assert(sizeof(CachedValues) == 0x60);

	struct ObjectstoAcquire
	{
	public:
		// members
		std::uint64_t unk00;  // 00
		std::uint64_t unk08;  // 08
		std::uint64_t unk10;  // 10
		std::uint64_t unk18;  // 18
		std::uint64_t unk20;  // 20
	};
	static_assert(sizeof(ObjectstoAcquire) == 0x28);

	class AIProcess
	{
	public:
		enum class LowProcessFlags : std::uint8_t
		{
			kNone = 0,
			kTargetActivated = 1 << 0,
			kCurrentActionComplete = 1 << 1,
			kIsAggressor = 1 << 2,
			kAlert = 1 << 3,
			kFollower = 1 << 4,
			kPackageDoneOnce = 1 << 5,
			kPackageIdleDone = 1 << 6
		};

		struct Hands
		{
			enum Hand : std::uint32_t
			{
				kLeft,
				kRight,
				kTotal
			};
		};
		using Hand = Hands::Hand;

		struct EquippedObject
		{
			TESForm*      object;  // 00
			BGSEquipSlot* slot;    // 08
		};
		static_assert(sizeof(EquippedObject) == 0x10);

		void                    AddToProcedureIndexRunning(Actor* a_actor, std::uint32_t a_num);
		void                    ClearActionHeadtrackTarget(bool a_defaultHold);
		void                    ClearFurniture();
		void                    ClearMuzzleFlashes();
		void                    ComputeLastTimeProcessed();
		float                   GetCachedHeight() const;
		bhkCharacterController* GetCharController();
		ActorHandle             GetCommandingActor() const;
		InventoryEntryData*     GetCurrentAmmo() const;
		TESShout*               GetCurrentShout();
		InventoryEntryData*     GetCurrentWeapon(bool a_leftHand);
		TESForm*                GetEquippedLeftHand();
		TESForm*                GetEquippedRightHand();
		ObjectRefHandle         GetHeadtrackTarget() const;
		[[nodiscard]] bool      GetIsSummonedCreature() const noexcept;
		NiAVObject*             GetMagicNode(const BSTSmartPointer<BipedAnim>& a_biped) const;
		ObjectRefHandle         GetOccupiedFurniture() const;
		float                   GetRegenDelay(ActorValue a_actorvalue) const;
		TESPackage*             GetRunningPackage() const;
		NiAVObject*             GetTorchNode(const BSTSmartPointer<BipedAnim>& a_biped) const;
		Actor*                  GetUserData() const;
		float                   GetVoiceRecoveryTime() const;
		NiAVObject*             GetWeaponNode(const BSTSmartPointer<BipedAnim>& a_biped) const;
		bool                    InHighProcess() const;
		bool                    InMiddleHighProcess() const;
		bool                    InMiddleLowProcess() const;
		bool                    InLowProcess() const;
		bool                    IsArrested() const;
		bool                    IsGhost() const;
		bool                    IsInCommandState() const;
		void                    SetActorRefraction(float a_refraction);
		void                    KnockExplosion(Actor* a_actor, const NiPoint3& a_location, float a_magnitude);
		void                    KnockParalyze(Actor* a_actor);
		bool                    PlayIdle(Actor* a_actor, TESIdleForm* a_idle, TESObjectREFR* a_target);
		void                    RandomlyPlaySpecialIdles(Actor* a_actor);
		void                    SetActorsDetectionEvent(Actor* a_actor, const NiPoint3& a_location, std::int32_t a_soundLevel, TESObjectREFR* a_ref);
		void                    SetArrested(bool a_arrested);
		void                    SetCachedHeight(float a_height);
		void                    SetRefraction(float a_refraction);
		void                    SetHeadtrackTarget(Actor* a_owner, NiPoint3& a_targetPosition);
		void                    Set3DUpdateFlag(RESET_3D_FLAGS a_flags);
		void                    SetRunOncePackage(TESPackage* a_package, Actor* a_actor);
		bool                    SetupSpecialIdle(Actor* a_actor, DEFAULT_OBJECT a_action, TESIdleForm* a_idle, bool a_arg5, bool a_arg6, TESObjectREFR* a_target);
		void                    StopCurrentIdle(Actor* a_actor, bool a_forceIdleStop);
		void                    Update3DModel(Actor* a_actor);
		void                    UpdateRegenDelay(ActorValue a_actorValue, float a_regenDelay);

		// members
		MiddleLowProcessData*                       middleLow;                      // 000
		MiddleHighProcessData*                      middleHigh;                     // 008
		HighProcessData*                            high;                           // 010
		ActorPackage                                currentPackage;                 // 018
		float                                       hourLastProcessed;              // 048
		float                                       dateLastProcessed;              // 04C
		CachedValues*                               cachedValues;                   // 050
		std::int32_t                                numberItemsActivate;            // 058
		std::uint32_t                               pad05C;                         // 05C
		BSSimpleList<ObjectstoAcquire*>             objects;                        // 060
		BSSimpleList<TESObjectREFR*>                genericLocations;               // 070
		ObjectstoAcquire*                           acquireObject;                  // 080
		ObjectstoAcquire*                           savedAcquireObject;             // 088
		float                                       essentialDownTimer;             // 090
		float                                       deathTime;                      // 094
		float                                       trackedDamage;                  // 098
		std::uint32_t                               pad09C;                         // 09C
		BSTArray<EquippedObject>                    equippedForms;                  // 0A0
		BSTHeapObjectArena<ModelDBHandle, 16>       unk0B8;                         // 0B8
		TESForm*                                    equippedObjects[Hand::kTotal];  // 0F0
		std::uint64_t                               unk100;                         // 100
		std::uint64_t                               unk108;                         // 108
		RefHandle                                   followTarget;                   // 110
		RefHandle                                   target;                         // 114
		RefHandle                                   arrestTarget;                   // 118
		std::uint64_t                               unk120;                         // 120
		std::uint64_t                               unk128;                         // 128
		std::uint32_t                               unk130;                         // 130
		std::uint16_t                               unk134;                         // 134
		REX::EnumSet<LowProcessFlags, std::uint8_t> lowProcessFlags;                // 136
		REX::EnumSet<PROCESS_TYPE, std::uint8_t>    processLevel;                   // 137
		bool                                        skippedTimeStampForPathing;     // 138
		bool                                        ignoringCombat;                 // 139
		bool                                        endAlarmOnActor;                // 13A
		bool                                        escortingPlayer;                // 13B
		std::uint32_t                               pad13C;                         // 13C

	protected:
		void Update3DModel_Impl(Actor* a_actor);
	};
	static_assert(sizeof(AIProcess) == 0x140);
}
