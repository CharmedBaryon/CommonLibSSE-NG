#pragma once

#include "RE/A/AITimeStamp.h"
#include "RE/A/ActiveEffect.h"
#include "RE/A/ActorState.h"
#include "RE/A/ActorValueOwner.h"
#include "RE/A/ActorValues.h"
#include "RE/B/BGSBipedObjectForm.h"
#include "RE/B/BGSEntryPointPerkEntry.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSPointerHandleSmartPointer.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTList.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/B/BSTTuple.h"
#include "RE/D/DetectionPriorities.h"
#include "RE/E/EmotionTypes.h"
#include "RE/F/FormTypes.h"
#include "RE/I/IPostAnimationChannelUpdateFunctor.h"
#include "RE/M/MagicSystem.h"
#include "RE/M/MagicTarget.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/T/TESNPC.h"
#include "RE/T/TESObjectREFR.h"

#include "REX/W32/BASE.h"

namespace RE
{
	class ActorMagicCaster;
	class ActorMover;
	class AIProcess;
	class bhkCharacterController;
	class bhkCharacterMoveFinishEvent;
	class BipedAnim;
	class BSTransformDeltaEvent;
	class CombatController;
	class CombatGroup;
	class ExtraDataList;
	class InventoryEntryData;
	class MovementControllerNPC;
	class MovementMessageActorCollision;
	class NiRefObject;
	class PackageLocation;
	class PerkEntryVisitor;
	class TrespassPackage;
	struct ActorMotionFeedbackData;
	struct ActorMotionFeedbackOutput;
	struct HighProcessData;
	struct MiddleHighProcessData;

	enum class ACTOR_CRITICAL_STAGE
	{
		kNone = 0,
		kGooStart = 1,
		kGooEnd = 2,
		kDisintegrateStart = 3,
		kDisintegrateEnd = 4,

		kTotal
	};

	struct Modifiers
	{
	public:
		// members
		float modifiers[ACTOR_VALUE_MODIFIERS::kTotal];  // 0
	};
	static_assert(sizeof(Modifiers) == 0xC);

	struct ActorValueStorage
	{
	public:
		template <class T>
		struct LocalMap
		{
		public:
			T* operator[](ActorValue a_actorValue)
			{
				return GetAt(static_cast<char>(a_actorValue));
			}

			const T* operator[](ActorValue a_actorValue) const
			{
				return GetAt(static_cast<char>(a_actorValue));
			}

			// members
			BSFixedString actorValues;  // 00
			T*            entries;      // 08

		private:
			[[nodiscard]] T* GetAt(char a_actorValue) const
			{
				auto akVals = actorValues.data();
				if (akVals && entries) {
					std::uint32_t idx = 0;
					while (akVals[idx] != '\0') {
						if (akVals[idx] == a_actorValue) {
							break;
						}
						++idx;
					}

					if (akVals[idx] != '\0') {
						return std::addressof(entries[idx]);
					}
				}
				return 0;
			}
		};
		static_assert(sizeof(LocalMap<float>) == 0x10);

		// members
		LocalMap<float>     baseValues;  // 00
		LocalMap<Modifiers> modifiers;   // 10
	};
	static_assert(sizeof(ActorValueStorage) == 0x20);

	NiSmartPointer(Actor);

	class Actor :
#ifndef ENABLE_SKYRIM_AE
		public TESObjectREFR,                              // 000
		public MagicTarget,                                // 098, 0A0
		public ActorValueOwner,                            // 0B0, 0B8
		public ActorState,                                 // 0B8, 0C0
		public BSTEventSink<BSTransformDeltaEvent>,        // 0C8, 0D0
		public BSTEventSink<bhkCharacterMoveFinishEvent>,  // 0D0, 0D8
		public IPostAnimationChannelUpdateFunctor          // 0D8, 0E0
#else
		public TESObjectREFR  // 000
#endif
	{
	private:
		using EntryPoint = BGSEntryPointPerkEntry::EntryPoint;

	public:
		inline static constexpr auto RTTI = RTTI_Actor;
		inline static constexpr auto FORMTYPE = FormType::ActorCharacter;

		struct SlotTypes
		{
			enum
			{
				kLeftHand = 0,
				kRightHand,
				kUnknown,
				kPowerOrShout,

				kTotal
			};
		};

		enum class BOOL_BITS
		{
			kNone = 0,
			kDelayUpdateScenegraph = 1 << 0,
			kProcessMe = 1 << 1,
			kMurderAlarm = 1 << 2,
			kHasSceneExtra = 1 << 3,
			kHeadingFixed = 1 << 4,
			kSpeakingDone = 1 << 5,
			kIgnoreChangeAnimationCall = 1 << 6,
			kSoundFileDone = 1 << 7,
			kVoiceFileDone = 1 << 8,
			kInTempChangeList = 1 << 9,
			kDoNotRunSayToCallback = 1 << 10,
			kDead = 1 << 11,
			kForceGreetingPlayer = 1 << 12,
			kForceUpdateQuestTarget = 1 << 13,
			kSearchingInCombat = 1 << 14,
			kAttackOnNextTheft = 1 << 15,
			kEvpBuffered = 1 << 16,
			kResetAI = 1 << 17,
			kInWater = 1 << 18,
			kSwimming = 1 << 19,
			kVoicePausedByScript = 1 << 20,
			kWasInFrustrum = 1 << 21,
			kShouldRotateToTrack = 1 << 22,
			kSetOnDeath = 1 << 23,
			kDoNotPadVoice = 1 << 24,
			kFootIKInRange = 1 << 25,
			kPlayerTeammate = 1 << 26,
			kGivePlayerXP = 1 << 27,
			kSoundCallbackSuccess = 1 << 28,
			kUseEmotion = 1 << 29,
			kGuard = 1 << 30,
			kParalyzed = 1 << 31
		};

		enum class BOOL_FLAGS
		{
			kNone = 0,
			kScenePackage = 1 << 0,
			kIsAMount = 1 << 1,
			kMountPointClear = 1 << 2,
			kGettingOnOffMount = 1 << 3,
			kInRandomScene = 1 << 4,
			kNoBleedoutRecovery = 1 << 5,
			kInBleedoutAnimation = 1 << 6,
			kCanDoFavor = 1 << 7,
			kShouldAnimGraphUpdate = 1 << 8,
			kCanSpeakToEssentialDown = 1 << 9,
			kBribedByPlayer = 1 << 10,
			kAngryWithPlayer = 1 << 11,
			kIsTrespassing = 1 << 12,
			kCanSpeak = 1 << 13,
			kIsInKillMove = 1 << 14,
			kAttackOnSight = 1 << 15,
			kIsCommandedActor = 1 << 16,
			kForceOneAnimgraphUpdate = 1 << 17,
			kEssential = 1 << 18,
			kProtected = 1 << 19,
			kAttackingDisabled = 1 << 20,
			kCastingDisabled = 1 << 21,
			kSceneHeadTrackRotation = 1 << 22,
			kForceIncMinBoneUpdate = 1 << 23,
			kCrimeSearch = 1 << 24,
			kMovingIntoLoadedArea = 1 << 25,
			kDoNotShowOnStealthMeter = 1 << 26,
			kMovementBlocked = 1 << 27,
			kAllowInstantFurniturePopInPlayerCell = 1 << 28,
			kForceAnimGraphUpdate = 1 << 29,
			kCheckAddEffectDualCast = 1 << 30,
			kUnderwater = 1 << 31
		};

		struct ChangeFlags
		{
			enum ChangeFlag : std::uint32_t
			{
				kLifeState = 1 << 10,
				kPackageExtraData = 1 << 11,
				kMerchantContainer = 1 << 12,
				kDismemberedLimbs = 1 << 17,
				kLeveledActor = 1 << 18,
				kDispModifiers = 1 << 19,
				kTempModifiers = 1 << 20,
				kDamageModifiers = 1 << 21,
				kOverrideModifiers = 1 << 22,
				kPermanentModifiers = 1 << 23,
			};
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kStartsDead = 1 << 9,
				kPersistent = 1 << 10,
				kInitiallyDisabled = 1 << 11,
				kIgnored = 1 << 12,
				kNoAIAcquire = 1 << 25,
				kDontHavokSettle = 1 << 29
			};
		};

		class ForEachSpellVisitor
		{
		public:
			inline static constexpr auto RTTI = RTTI_Actor__ForEachSpellVisitor;

			virtual ~ForEachSpellVisitor() = default;  // 00

			// add
			virtual BSContainer::ForEachResult Visit(SpellItem* a_spell) = 0;  // 01
		};

		~Actor() override;  // 000

		// override (TESObjectREFR)
		void                                 SaveGame(BGSSaveFormBuffer* a_buf) override;                                                                                                                                                                          // 00E
		void                                 LoadGame(BGSLoadFormBuffer* a_buf) override;                                                                                                                                                                          // 00F
		void                                 InitLoadGame(BGSLoadFormBuffer* a_buf) override;                                                                                                                                                                      // 010
		void                                 FinishLoadGame(BGSLoadFormBuffer* a_buf) override;                                                                                                                                                                    // 011
		void                                 Revert(BGSLoadFormBuffer* a_buf) override;                                                                                                                                                                            // 012
		void                                 InitItemImpl() override;                                                                                                                                                                                              // 013
		void                                 SetDelete(bool a_set) override;                                                                                                                                                                                       // 023
		void                                 Predestroy() override;                                                                                                                                                                                                // 03B
		[[nodiscard]] BGSLocation*           GetEditorLocation1() const override;                                                                                                                                                                                  // 03C - { return editorLocation; }
		[[nodiscard]] bool                   GetEditorLocation2(NiPoint3& a_outPos, NiPoint3& a_outRot, TESForm*& a_outWorldOrCell, TESObjectCELL* a_fallback) override;                                                                                           // 03D
		void                                 ForceEditorLocation(BGSLocation* a_location) override;                                                                                                                                                                // 03E - { editorLocation = a_location; }
		void                                 Update3DPosition(bool a_warp) override;                                                                                                                                                                               // 03F
		void                                 UpdateSoundCallBack(bool a_endSceneAction) override;                                                                                                                                                                  // 040
		bool                                 SetDialogueWithPlayer(bool a_flag, bool a_forceGreet, TESTopicInfo* a_topic) override;                                                                                                                                // 041
		[[nodiscard]] BGSAnimationSequencer* GetSequencer(void) const override;                                                                                                                                                                                    // 045 - { return currentProcess->high->animSequencer; }
		[[nodiscard]] bool                   HasKeywordHelper(const BGSKeyword* a_keyword) const override;                                                                                                                                                         // 048
		[[nodiscard]] TESPackage*            CheckForCurrentAliasPackage() override;                                                                                                                                                                               // 049 - { return 0; }
		[[nodiscard]] BGSScene*              GetCurrentScene() const override;                                                                                                                                                                                     // 04A
		void                                 SetCurrentScene(BGSScene* a_scene) override;                                                                                                                                                                          // 04B
		bool                                 UpdateInDialogue(DialogueResponse* a_response, bool a_unused) override;                                                                                                                                               // 04C
		[[nodiscard]] BGSDialogueBranch*     GetExclusiveBranch() const override;                                                                                                                                                                                  // 04D - { return exclusiveBranch; }
		void                                 SetExclusiveBranch(BGSDialogueBranch* a_branch) override;                                                                                                                                                             // 04E - { exclusiveBranch = a_arg1; }
		void                                 PauseCurrentDialogue(void) override;                                                                                                                                                                                  // 04F
		[[nodiscard]] NiPoint3               GetStartingAngle() const override;                                                                                                                                                                                    // 052
		[[nodiscard]] NiPoint3               GetStartingLocation() const override;                                                                                                                                                                                 // 053
		ObjectRefHandle                      RemoveItem(TESBoundObject* a_item, std::int32_t a_count, ITEM_REMOVE_REASON a_reason, ExtraDataList* a_extraList, TESObjectREFR* a_moveToRef, const NiPoint3* a_dropLoc = 0, const NiPoint3* a_rotate = 0) override;  // 056
		bool                                 AddWornItem(TESBoundObject* a_item, std::int32_t a_count, bool a_forceEquip, std::uint32_t a_arg4, std::uint32_t a_arg5) override;                                                                                    // 057
		void                                 DoTrap1(TrapData& a_data) override;                                                                                                                                                                                   // 058
		void                                 DoTrap2(TrapEntry* a_trap, TargetEntry* a_target) override;                                                                                                                                                           // 059
		void                                 AddObjectToContainer(TESBoundObject* a_object, ExtraDataList* a_extraList, std::int32_t a_count, TESObjectREFR* a_fromRefr) override;                                                                                 // 05A
		[[nodiscard]] NiPoint3               GetLookingAtLocation() const override;                                                                                                                                                                                // 05B
		[[nodiscard]] MagicCaster*           GetMagicCaster(MagicSystem::CastingSource a_source) override;                                                                                                                                                         // 05C
		[[nodiscard]] MagicTarget*           GetMagicTarget() override;                                                                                                                                                                                            // 05D - { return static_cast<MagicTarget*>(this); }
		[[nodiscard]] bool                   IsChild() const override;                                                                                                                                                                                             // 05E - { return false; }
		BSFaceGenAnimationData*              GetFaceGenAnimationData() override;                                                                                                                                                                                   // 063
		bool                                 DetachHavok(NiAVObject* a_obj3D) override;                                                                                                                                                                            // 065
		void                                 InitHavok() override;                                                                                                                                                                                                 // 066
		void                                 Unk_67(void) override;                                                                                                                                                                                                // 067 - related to vampire lord cape
		void                                 Unk_68(void) override;                                                                                                                                                                                                // 068
		void                                 Unk_69(void) override;                                                                                                                                                                                                // 069
		NiAVObject*                          Load3D(bool a_arg1) override;                                                                                                                                                                                         // 06A
		void                                 Set3D(NiAVObject* a_object, bool a_queue3DTasks = true) override;                                                                                                                                                     // 06C
		bool                                 PopulateGraphProjectsToLoad(void) const override;                                                                                                                                                                     // 072
		[[nodiscard]] NiPoint3               GetBoundMin() const override;                                                                                                                                                                                         // 073
		[[nodiscard]] NiPoint3               GetBoundMax() const override;                                                                                                                                                                                         // 074
		void                                 Unk_75(void) override;                                                                                                                                                                                                // 075 - "ActorValue GetWeaponSkill()"? really weird call, only works for right hand, and defaults to 1
		void                                 Unk_78(void) override;                                                                                                                                                                                                // 078
		void                                 ModifyAnimationUpdateData(BSAnimationUpdateData& a_data) override;                                                                                                                                                    // 079
		bool                                 ShouldSaveAnimationOnUnloading() const override;                                                                                                                                                                      // 07A - { return false; }
		bool                                 ShouldSaveAnimationOnSaving() const override;                                                                                                                                                                         // 07B
		bool                                 ShouldPerformRevert() const override;                                                                                                                                                                                 // 07C
		void                                 UpdateAnimation(float a_delta) override;                                                                                                                                                                              // 07D
#ifndef SKYRIM_CROSS_VR
		// Override functions past where Skyrim VR breaks compatibility.
		void                   RemoveWeapon(BIPED_OBJECT equipIndex) override;                                                // 082
		void                   SetObjectReference(TESBoundObject* a_object) override;                                         // 084
		void                   MoveHavok(bool a_forceRec) override;                                                           // 085
		void                   GetLinearVelocity(NiPoint3& a_velocity) const override;                                        // 086
		void                   SetActionComplete(bool a_set) override;                                                        // 087
		void                   Disable() override;                                                                            // 089
		void                   ResetInventory(bool a_leveledOnly) override;                                                   // 08A
		NiNode*                GetFireNode() override;                                                                        // 08B
		void                   SetFireNode(NiNode* a_fireNode) override;                                                      // 08C
		bool                   OnAddCellPerformQueueReference(TESObjectCELL& a_cell) const override;                          // 090
		void                   DoMoveToHigh() override;                                                                       // 091
		void                   TryMoveToMiddleLow() override;                                                                 // 092
		bool                   TryChangeSkyCellActorsProcessLevel() override;                                                 // 093
		void                   TryUpdateActorLastSeenTime() override;                                                         // 095
		void                   Unk_96(void) override;                                                                         // 096
		void                   SetParentCell(TESObjectCELL* a_cell) override;                                                 // 098
		[[nodiscard]] bool     IsDead(bool a_notEssential = true) const override;                                             // 099
		bool                   ProcessInWater(hkpCollidable* a_collidable, float a_waterHeight, float a_deltaTime) override;  // 09C
		bool                   ApplyCurrent(float a_velocityTime, const hkVector4& a_velocity) override;                      // 09D
		[[nodiscard]] TESAmmo* GetCurrentAmmo() const override;                                                               // 09E
		void                   UnequipItem(std::uint64_t a_arg1, TESBoundObject* a_object) override;                          // 0A1
#endif

		// override (MagicTarget)
#ifndef ENABLE_SKYRIM_AE
		[[nodiscard]] Actor*                       GetTargetStatsObject() override;      // 002 - { return this; }
		[[nodiscard]] bool                         MagicTargetIsActor() const override;  // 003 - { return true; }
		[[nodiscard]] BSSimpleList<ActiveEffect*>* GetActiveEffectList() override;       // 007
#endif

		// add
		SKYRIM_REL_VR_VIRTUAL void                Unk_A2(void);                                                                                                                                                                           // 0A2
		SKYRIM_REL_VR_VIRTUAL void                PlayPickUpSound(TESBoundObject* a_object, bool a_pickup, bool a_use);                                                                                                                   // 0A3
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL float GetHeading(bool a_ignoreRaceSettings) const;                                                                                                                                            // 0A4
		SKYRIM_REL_VR_VIRTUAL void                SetAvoidanceDisabled(bool a_set);                                                                                                                                                       // 0A5 - { return; }
		SKYRIM_REL_VR_VIRTUAL void                DrawWeaponMagicHands(bool a_draw);                                                                                                                                                      // 0A6
		SKYRIM_REL_VR_VIRTUAL void                DetachCharController();                                                                                                                                                                 // 0A7
		SKYRIM_REL_VR_VIRTUAL void                RemoveCharController();                                                                                                                                                                 // 0A8
		SKYRIM_REL_VR_VIRTUAL void                SetPosition(const NiPoint3& a_pos, bool a_updateCharController);                                                                                                                        // 0A9
		SKYRIM_REL_VR_VIRTUAL void                KillDying();                                                                                                                                                                            // 0AA
		SKYRIM_REL_VR_VIRTUAL void                Resurrect(bool a_resetInventory, bool a_attach3D);                                                                                                                                      // 0AB
		SKYRIM_REL_VR_VIRTUAL bool                PutActorOnMountQuick();                                                                                                                                                                 // 0AC
		SKYRIM_REL_VR_VIRTUAL void                Update(float a_delta);                                                                                                                                                                  // 0AD
		SKYRIM_REL_VR_VIRTUAL void                UpdateNoAI(float a_delta);                                                                                                                                                              // 0AE - { return UpdateActor3DPosition(); }
		SKYRIM_REL_VR_VIRTUAL void                UpdateCharacterControllerSimulationSettings(bhkCharacterController& a_controller);                                                                                                      // 0AF
		SKYRIM_REL_VR_VIRTUAL void                PotentiallyFixRagdollState();                                                                                                                                                           // 0B0
		SKYRIM_REL_VR_VIRTUAL void                UpdateNonRenderSafe(float a_delta);                                                                                                                                                     // 0B1
		SKYRIM_REL_VR_VIRTUAL void                OnItemEquipped(bool a_playAnim);                                                                                                                                                        // 0B2
		SKYRIM_REL_VR_VIRTUAL void                Unk_B3(void);                                                                                                                                                                           // 0B3 - { return 1; }
		SKYRIM_REL_VR_VIRTUAL void                Unk_B4(void);                                                                                                                                                                           // 0B4
		SKYRIM_REL_VR_VIRTUAL void                SetCrimeGoldValue(TESFaction* a_faction, bool a_violent, std::uint32_t a_amount);                                                                                                       // 0B5
		SKYRIM_REL_VR_VIRTUAL void                ModCrimeGoldValue(TESFaction* a_faction, bool a_violent, std::int32_t a_amount);                                                                                                        // 0B6
		SKYRIM_REL_VR_VIRTUAL void                RemoveCrimeGoldValue(TESFaction* a_faction, bool a_violent, std::int32_t a_amount);                                                                                                     // 0B7
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL std::uint32_t GetCrimeGoldValue(const TESFaction* a_faction) const;                                                                                                                           // 0B8
		SKYRIM_REL_VR_VIRTUAL void                        GoToPrison(TESFaction* a_faction, bool a_removeInventory, bool a_realJail);                                                                                                     // 0B9 - { return; }
		SKYRIM_REL_VR_VIRTUAL void                        ServePrisonTime();                                                                                                                                                              // 0BA - { return; }
		SKYRIM_REL_VR_VIRTUAL void                        PayFine(TESFaction* a_faction, bool a_goToJail, bool a_removeStolenItems);                                                                                                      // 0BB - { return; }
		SKYRIM_REL_VR_VIRTUAL bool                        GetCannibal();                                                                                                                                                                  // 0BC - { return false; }
		SKYRIM_REL_VR_VIRTUAL void                        SetCannibal(bool a_set);                                                                                                                                                        // 0BD - { return; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool          GetVampireFeed();                                                                                                                                                               // 0BE - { return false; }
		SKYRIM_REL_VR_VIRTUAL void                        SetVampireFeed(bool a_set);                                                                                                                                                     // 0BF - { return; }
		SKYRIM_REL_VR_VIRTUAL void                        InitiateVampireFeedPackage(Actor* a_target, TESObjectREFR* a_furniture);                                                                                                        // 0C0 - { return; }
		SKYRIM_REL_VR_VIRTUAL void                        InitiateCannibalPackage(Actor* a_target);                                                                                                                                       // 0C1 - { return; }
		SKYRIM_REL_VR_VIRTUAL void                        GetEyeVector(NiPoint3& a_origin, NiPoint3& a_direction, bool a_includeCameraOffset);                                                                                            // 0C2
		SKYRIM_REL_VR_VIRTUAL void                        SetRefraction(bool a_enable, float a_refraction);                                                                                                                               // 0C3
		SKYRIM_REL_VR_VIRTUAL void                        Unk_C4(void);                                                                                                                                                                   // 0C4 - { return; }
		SKYRIM_REL_VR_VIRTUAL void                        Unk_C5(void);                                                                                                                                                                   // 0C5 - { return 1; }
		SKYRIM_REL_VR_VIRTUAL void                        Unk_C6(void);                                                                                                                                                                   // 0C6
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL float         GetAcrobatics() const;                                                                                                                                                          // 0C7 - { return 1.0; }
		SKYRIM_REL_VR_VIRTUAL bhkCharacterController*     Move(float a_arg2, const NiPoint3& a_position);                                                                                                                                 // 0C8
		SKYRIM_REL_VR_VIRTUAL void                        Unk_C9(void);                                                                                                                                                                   // 0C9
		SKYRIM_REL_VR_VIRTUAL void                        OnArmorActorValueChanged();                                                                                                                                                     // 0CA - { return; }
		SKYRIM_REL_VR_VIRTUAL ObjectRefHandle             DropObject(const TESBoundObject* a_object, ExtraDataList* a_extraList, std::int32_t a_count, const NiPoint3* a_dropLoc = 0, const NiPoint3* a_rotate = 0);                      // 0CB
		SKYRIM_REL_VR_VIRTUAL void                        PickUpObject(TESObjectREFR* a_object, std::int32_t a_count, bool a_arg3 = false, bool a_playSound = true);                                                                      // 0CC
		SKYRIM_REL_VR_VIRTUAL void                        AttachArrow(const BSTSmartPointer<BipedAnim>& a_biped);                                                                                                                         // 0CD
		SKYRIM_REL_VR_VIRTUAL void                        DetachArrow(const BSTSmartPointer<BipedAnim>& a_biped);                                                                                                                         // 0CE
		SKYRIM_REL_VR_VIRTUAL bool                        AddShout(TESShout* a_shout);                                                                                                                                                    // 0CF
		SKYRIM_REL_VR_VIRTUAL void                        UnlockWord(TESWordOfPower* a_power);                                                                                                                                            // 0D0 - { return; }
		SKYRIM_REL_VR_VIRTUAL void                        Unk_D1(void);                                                                                                                                                                   // 0D1
		SKYRIM_REL_VR_VIRTUAL std::uint32_t              UseAmmo(std::uint32_t a_shotCount);                                                                                                                                              // 0D2
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool         CalculateCachedOwnerIsInCombatantFaction() const;                                                                                                                                // 0D3
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL CombatGroup* GetCombatGroup() const;                                                                                                                                                          // 0D4
		SKYRIM_REL_VR_VIRTUAL void                       SetCombatGroup(CombatGroup* a_group);                                                                                                                                            // 0D5
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool         CheckValidTarget(TESObjectREFR& a_target);                                                                                                                                       // 0D6
		SKYRIM_REL_VR_VIRTUAL bool                       InitiateTresPassPackage(TrespassPackage* a_trespassPackage);                                                                                                                     // 0D7 - { return 0; }
		SKYRIM_REL_VR_VIRTUAL void                       InitiateDialogue(Actor* a_target, PackageLocation* a_loc1, PackageLocation* a_loc2);                                                                                             // 0D8
		SKYRIM_REL_VR_VIRTUAL void                       SetSize(float a_size);                                                                                                                                                           // 0D9
		SKYRIM_REL_VR_VIRTUAL void                       EndDialogue();                                                                                                                                                                   // 0DA
		SKYRIM_REL_VR_VIRTUAL Actor*                     SetUpTalkingActivatorActor(Actor* a_target, Actor*& a_activator);                                                                                                                // 0DB
		SKYRIM_REL_VR_VIRTUAL void                       InitiateSpectator(Actor* a_target);                                                                                                                                              // 0DC - { return; }
		SKYRIM_REL_VR_VIRTUAL void                       InitiateFlee(TESObjectREFR* a_fleeRef, bool a_runOnce, bool a_knows, bool a_combatMode, TESObjectCELL* a_cell, TESObjectREFR* a_ref, float a_fleeFromDist, float a_fleeToDist);  // 0DD
		SKYRIM_REL_VR_VIRTUAL void                       InitiateGetUpPackage();                                                                                                                                                          // 0DE
		SKYRIM_REL_VR_VIRTUAL void                       PutCreatedPackage(TESPackage* a_package, bool a_tempPackage, bool a_createdPackage, bool a_allowFromFurniture);                                                                  // 0DF
		SKYRIM_REL_VR_VIRTUAL void                       UpdateAlpha();                                                                                                                                                                   // 0E0
		SKYRIM_REL_VR_VIRTUAL void                       SetAlpha(float a_alpha = 1.0);                                                                                                                                                   // 0E1
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL float        GetAlpha();                                                                                                                                                                      // 0E2
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool         IsInCombat() const;                                                                                                                                                              // 0E3
		SKYRIM_REL_VR_VIRTUAL void                       UpdateCombat();                                                                                                                                                                  // 0E4
		SKYRIM_REL_VR_VIRTUAL void                       StopCombat();                                                                                                                                                                    // 0E5
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL float        CalcArmorRating();                                                                                                                                                               // 0E6 - { return 0.0; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL float        GetArmorBaseFactorSum();                                                                                                                                                         // 0E7 - { return 0.0; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL float        CalcUnarmedDamage();                                                                                                                                                             // 0E8 - { return 0; }
		SKYRIM_REL_VR_VIRTUAL void                       Unk_E9(void);                                                                                                                                                                    // 0E9 - { return 0; }
		SKYRIM_REL_VR_VIRTUAL void                       Unk_EA(void);                                                                                                                                                                    // 0EA - { return 0; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL float        GetRunSpeed();                                                                                                                                                                   // 0EB
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL float        GetJogSpeed();                                                                                                                                                                   // 0EC
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL float        GetFastWalkSpeed();                                                                                                                                                              // 0ED
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL float        GetWalkSpeed();                                                                                                                                                                  // 0EE
		SKYRIM_REL_VR_VIRTUAL void                       WeaponSwingCallBack();                                                                                                                                                           // 0EF
		SKYRIM_REL_VR_VIRTUAL void                       SetActorStartingPosition();                                                                                                                                                      // 0F0
		SKYRIM_REL_VR_VIRTUAL bool                       MoveToHigh();                                                                                                                                                                    // 0F1
		SKYRIM_REL_VR_VIRTUAL bool                       MovetoLow();                                                                                                                                                                     // 0F2
		SKYRIM_REL_VR_VIRTUAL bool                       MovetoMiddleLow();                                                                                                                                                               // 0F3
		SKYRIM_REL_VR_VIRTUAL bool                       MoveToMiddleHigh();                                                                                                                                                              // 0F4
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool         HasBeenAttacked() const;                                                                                                                                                         // 0F5
		SKYRIM_REL_VR_VIRTUAL void                       SetBeenAttacked(bool a_set);                                                                                                                                                     // 0F6
		SKYRIM_REL_VR_VIRTUAL void                       UseSkill(ActorValue a_av, float a_points, TESForm* a_arg3);                                                                                                                      // 0F7 - { return; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool         IsAtPoint(const NiPoint3& a_point, float a_radius, bool a_expandRadius, bool a_alwaysTestHeight);                                                                                // 0F8
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool         IsInFaction(const TESFaction* faction) const;                                                                                                                                    // 0F9
		SKYRIM_REL_VR_VIRTUAL void                       ForEachPerk(PerkEntryVisitor& a_visitor) const;                                                                                                                                  // 0FA
		SKYRIM_REL_VR_VIRTUAL void                       AddPerk(BGSPerk* a_perk, std::uint32_t a_rank = 0);                                                                                                                              // 0FB - { return; }
		SKYRIM_REL_VR_VIRTUAL void                       RemovePerk(BGSPerk* a_perk);                                                                                                                                                     // 0FC - { return; }
		SKYRIM_REL_VR_VIRTUAL void                       ApplyTemporaryPerk(BGSPerk* a_perk);                                                                                                                                             // 0FD - { return; }
		SKYRIM_REL_VR_VIRTUAL void                       RemoveTemporaryPerk(BGSPerk* a_perk);                                                                                                                                            // 0FE - { return; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool         HasPerkEntries(EntryPoint a_entryType) const;                                                                                                                                    // 0FF
		SKYRIM_REL_VR_VIRTUAL void                       ForEachPerkEntry(EntryPoint a_entryType, PerkEntryVisitor& a_visitor) const;                                                                                                     // 100
		SKYRIM_REL_VR_VIRTUAL void                       ApplyPerksFromBase();                                                                                                                                                            // 101
		SKYRIM_REL_VR_VIRTUAL void                       StartPowerAttackCoolDown();                                                                                                                                                      // 102 - { return; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool         IsPowerAttackCoolingDown() const;                                                                                                                                                // 103 - { return false; }
		SKYRIM_REL_VR_VIRTUAL void                       HandleHealthDamage(Actor* a_attacker, float a_damage);                                                                                                                           // 104
		SKYRIM_REL_VR_VIRTUAL void                       Unk_105(void);                                                                                                                                                                   // 105
		SKYRIM_REL_VR_VIRTUAL void                       Unk_106(void);                                                                                                                                                                   // 106 - { return; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool         QSpeakingDone() const;                                                                                                                                                           // 107 - { return ~(unk0E0 >> 5) & 1; }
		SKYRIM_REL_VR_VIRTUAL void                       SetSpeakingDone(bool a_set);                                                                                                                                                     // 108
		SKYRIM_REL_VR_VIRTUAL void                       CreateMovementController();                                                                                                                                                      // 109
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL EmotionType  GetEmotionType();                                                                                                                                                                // 10A - { return unk16C; }
		SKYRIM_REL_VR_VIRTUAL void                       SetEmotionType(EmotionType a_emotionType);                                                                                                                                       // 10B - { unk16C = a_arg1; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL std::uint32_t GetEmotionValue();                                                                                                                                                              // 10C - { return unk170; }
		SKYRIM_REL_VR_VIRTUAL void                        SetEmotionValue(std::uint32_t a_emotionValue);                                                                                                                                  // 10D - { unk170 = a_arg1; }
		SKYRIM_REL_VR_VIRTUAL void                        KillImpl(Actor* a_attacker, float a_damage, bool a_sendEvent, bool a_ragdollInstant);                                                                                           // 10E
		SKYRIM_REL_VR_VIRTUAL bool                        DrinkPotion(AlchemyItem* a_potion, ExtraDataList* a_extralist);                                                                                                                 // 10F
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool          CheckCast(MagicItem* a_spell, bool a_dualCast, MagicSystem::CannotCastReason* a_reason);                                                                                        // 110
		SKYRIM_REL_VR_VIRTUAL void                        CheckTempModifiers();                                                                                                                                                           // 111 - { return; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL std::int32_t         GetCurrentShoutLevel();                                                                                                                                                  // 112 - return -1 on error
		SKYRIM_REL_VR_VIRTUAL void                               SetLastRiddenMount(ActorHandle a_mount);                                                                                                                                 // 113 - { return; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL ActorHandle          QLastRiddenMount() const;                                                                                                                                                // 114 - { return {}; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool                 CalculateCachedOwnerIsUndead() const;                                                                                                                                    // 115
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool                 CalculateCachedOwnerIsNPC() const;                                                                                                                                       // 116
		SKYRIM_REL_VR_VIRTUAL void                               Unk_117(void);                                                                                                                                                           // 117 - { return; }
		SKYRIM_REL_VR_VIRTUAL void                               InitValues();                                                                                                                                                            // 118
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL const BSFixedString& GetResponseString() const;                                                                                                                                               // 119 - { return "ActorResponse"; }
		SKYRIM_REL_VR_VIRTUAL void                               ModifyMovementData(float a_delta, NiPoint3& a_arg3, NiPoint3& a_arg4);                                                                                                   // 11A
		SKYRIM_REL_VR_VIRTUAL void                               UpdateCombatControllerSettings();                                                                                                                                        // 11B
		SKYRIM_REL_VR_VIRTUAL void                               UpdateFadeSettings(bhkCharacterController* a_controller);                                                                                                                // 11C
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool                 ComputeMotionFeedbackSpeedAndDirection(const ActorMotionFeedbackData& a_data, float a_delta, ActorMotionFeedbackOutput& a_output);                                       // 11D
		SKYRIM_REL_VR_VIRTUAL bool                               UpdateFeedbackGraphSpeedAndDirection(const ActorMotionFeedbackOutput& a_output);                                                                                         // 11E
		SKYRIM_REL_VR_VIRTUAL void                               UpdateActor3DPosition();                                                                                                                                                 // 11F
		SKYRIM_REL_VR_VIRTUAL void                               PrecacheData();                                                                                                                                                          // 120
		SKYRIM_REL_VR_VIRTUAL void                               WornArmorChanged(void);                                                                                                                                                  // 121
		SKYRIM_REL_VR_VIRTUAL void                               ProcessTracking(float a_delta, NiAVObject* a_obj3D);                                                                                                                     // 122
		SKYRIM_REL_VR_VIRTUAL void                               Unk_123(void);                                                                                                                                                           // 123
		SKYRIM_REL_VR_VIRTUAL void                               CreateActorMover();                                                                                                                                                      // 124
		SKYRIM_REL_VR_VIRTUAL void                               DestroyActorMover();                                                                                                                                                     // 125
		SKYRIM_REL_VR_VIRTUAL bool                               ShouldRespondToActorCollision(const MovementMessageActorCollision& a_msg, const ActorHandlePtr& a_target);                                                               // 126
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL float                CheckClampDamageModifier(ActorValue a_av, float a_delta);                                                                                                                // 127

		static NiPointer<Actor> LookupByHandle(RefHandle a_refHandle);
		static bool             LookupByHandle(RefHandle a_refHandle, NiPointer<Actor>& a_refrOut);

		bool                                    AddAnimationGraphEventSink(BSTEventSink<BSAnimationGraphEvent>* a_sink) const;
		void                                    AddCastPower(SpellItem* a_power);
		bool                                    AddSpell(SpellItem* a_spell);
		void                                    AddToFaction(TESFaction* a_faction, std::int8_t a_rank);
		void                                    AddWornOutfit(BGSOutfit* a_outfit, bool a_forceUpdate);
		void                                    AllowBleedoutDialogue(bool a_canTalk);
		void                                    AllowPCDialogue(bool a_talk);
		void                                    CastPermanentMagic(bool a_wornItemEnchantments, bool a_baseSpells, bool a_raceSpells, bool a_everyActorAbility);
		[[nodiscard]] bool                      CanAttackActor(Actor* a_actor);
		[[nodiscard]] bool                      CanFlyHere() const;
		[[nodiscard]] bool                      CanOfferServices() const;
		[[nodiscard]] bool                      CanPickpocket() const;
		[[nodiscard]] bool                      CanTalkToPlayer() const;
		[[nodiscard]] bool                      CanUseIdle(TESIdleForm* a_idle) const;
		void                                    ClearArrested();
		void                                    ClearExpressionOverride();
		inline void                             ClearExtraArrows() { RemoveExtraArrows3D(); }
		[[nodiscard]] ActorHandle               CreateRefHandle();
		bool                                    Decapitate();
		void                                    DeselectSpell(SpellItem* a_spell);
		void                                    DispelAlteredStates(RE::EffectArchetype a_exception);
		void                                    DispelWornItemEnchantments();
		void                                    DoReset3D(bool a_updateWeight);
		void                                    EnableAI(bool a_enable);
		void                                    EndInterruptPackage(bool a_skipDialogue);
		void                                    EvaluatePackage(bool a_immediate = false, bool a_resetAI = false);
		[[nodiscard]] TESNPC*                   GetActorBase();
		[[nodiscard]] const TESNPC*             GetActorBase() const;
		[[nodiscard]] float                     GetActorValueModifier(ACTOR_VALUE_MODIFIER a_modifier, ActorValue a_value) const;
		[[nodiscard]] float                     GetAimAngle() const;
		[[nodiscard]] float                     GetAimHeading() const;
		[[nodiscard]] InventoryEntryData*       GetAttackingWeapon();
		[[nodiscard]] const InventoryEntryData* GetAttackingWeapon() const;
		[[nodiscard]] bhkCharacterController*   GetCharController() const;
		std::uint32_t                           GetCollisionFilterInfo(std::uint32_t& a_outCollisionFilterInfo);
		[[nodiscard]] NiPointer<Actor>          GetCommandingActor() const;
		[[nodiscard]] TESFaction*               GetCrimeFaction();
		[[nodiscard]] const TESFaction*         GetCrimeFaction() const;
		[[nodiscard]] TESPackage*               GetCurrentPackage();
		[[nodiscard]] const TESPackage*         GetCurrentPackage() const;
		[[nodiscard]] TESShout*                 GetCurrentShout();
		[[nodiscard]] const TESShout*           GetCurrentShout() const;
		[[nodiscard]] InventoryEntryData*       GetEquippedEntryData(bool a_leftHand) const;
		[[nodiscard]] TESForm*                  GetEquippedObject(bool a_leftHand) const;
		[[nodiscard]] TESForm*                  GetEquippedObjectInSlot(const BGSEquipSlot* slot) const;
		[[nodiscard]] float                     GetEquippedWeight();
		[[nodiscard]] std::int32_t              GetFactionRank(TESFaction* a_faction, bool a_isPlayer);
		[[nodiscard]] std::int32_t              GetGoldAmount(bool a_noInit = false);
		[[nodiscard]] ActorHandle               GetHandle();
		[[nodiscard]] NiAVObject*               GetHeadPartObject(BGSHeadPart::HeadPartType a_type);
		[[nodiscard]] float                     GetHeight();
		[[nodiscard]] HighProcessData*          GetHighProcess() const;
		[[nodiscard]] Actor*                    GetKiller() const;
		[[nodiscard]] std::uint16_t             GetLevel() const;
		[[nodiscard]] MiddleHighProcessData*    GetMiddleHighProcess() const;
		[[nodiscard]] bool                      GetMount(NiPointer<Actor>& a_outMount);
		[[nodiscard]] bool                      GetMountedBy(NiPointer<Actor>& a_outRider);
		[[nodiscard]] double                    GetMoveDirectionRelativeToFacing();
		[[nodiscard]] ObjectRefHandle           GetOccupiedFurniture() const;
		[[nodiscard]] TESRace*                  GetRace() const;
		[[nodiscard]] float                     GetRegenDelay(ActorValue a_actorValue) const;
		[[nodiscard]] bool                      GetRider(NiPointer<Actor>& a_outRider);
		[[nodiscard]] TESObjectARMO*            GetSkin() const;
		[[nodiscard]] TESObjectARMO*            GetSkin(BGSBipedObjectForm::BipedObjectSlot a_slot, bool a_noInit = false);
		[[nodiscard]] SOUL_LEVEL                GetSoulSize() const;
		[[nodiscard]] float                     GetTotalCarryWeight();
		[[nodiscard]] TESFaction*               GetVendorFaction();
		[[nodiscard]] const TESFaction*         GetVendorFaction() const;
		[[nodiscard]] float                     GetVoiceRecoveryTime();
		[[nodiscard]] float                     GetWarmthRating() const;
		[[nodiscard]] TESObjectARMO*            GetWornArmor(BGSBipedObjectForm::BipedObjectSlot a_slot, bool a_noInit = false);
		[[nodiscard]] TESObjectARMO*            GetWornArmor(FormID a_formID, bool a_noInit = false);
		[[nodiscard]] bool                      HasKeyword(const BGSKeyword* a_keyword) const;
		[[nodiscard]] bool                      HasKeywordString(std::string_view a_formEditorID);
		[[nodiscard]] bool                      HasLineOfSight(TESObjectREFR* a_ref, bool& a_arg2);
		[[nodiscard]] bool                      HasOutfitItems(BGSOutfit* a_outfit);
		[[nodiscard]] bool                      HasPerk(BGSPerk* a_perk) const;
		[[nodiscard]] bool                      HasShout(TESShout* a_shout) const;
		[[nodiscard]] bool                      HasSpell(SpellItem* a_spell) const;
		void                                    InitiateDoNothingPackage();
		void                                    InterruptCast(bool a_restoreMagicka) const;
		[[nodiscard]] bool                      IsAttacking() const;
		[[nodiscard]] bool                      IsAIEnabled() const;
		[[nodiscard]] bool                      IsAlarmed() const;
		[[nodiscard]] bool                      IsAMount() const;
		[[nodiscard]] bool                      IsAnimationDriven() const;
		[[nodiscard]] bool                      IsBeingRidden() const;
		[[nodiscard]] bool                      IsBlocking() const;
		[[nodiscard]] bool                      IsCasting(MagicItem* a_spell) const;
		[[nodiscard]] bool                      IsCommandedActor() const;
		[[nodiscard]] bool                      IsCurrentShout(SpellItem* a_power);
		[[nodiscard]] bool                      IsDualCasting() const;
		[[nodiscard]] bool                      IsEssential() const;
		[[nodiscard]] bool                      IsFactionInCrimeGroup(const TESFaction* a_faction) const;
		[[nodiscard]] bool                      IsGhost() const;
		[[nodiscard]] bool                      IsGuard() const;
		[[nodiscard]] bool                      IsHostileToActor(Actor* a_actor);
		[[nodiscard]] bool                      IsInCastPowerList(SpellItem* a_power);
		[[nodiscard]] constexpr bool            IsInKillMove() const noexcept { return GetActorRuntimeData().boolFlags.all(BOOL_FLAGS::kIsInKillMove); }
		[[nodiscard]] bool                      IsInMidair() const;
		[[nodiscard]] bool                      IsInRagdollState() const;
		[[nodiscard]] bool                      IsLeveled() const;
		[[nodiscard]] bool                      IsLimbGone(std::uint32_t a_limb);
		[[nodiscard]] bool                      IsMoving() const;
		[[nodiscard]] bool                      IsOnMount() const;
		[[nodiscard]] bool                      IsOverEncumbered() const;
		[[nodiscard]] bool                      IsPlayerTeammate() const;
		[[nodiscard]] bool                      IsProtected() const;
		[[nodiscard]] bool                      IsRunning() const;
		[[nodiscard]] bool                      IsSneaking() const;
		[[nodiscard]] bool                      IsPointSubmergedMoreThan(const NiPoint3& a_pos, TESObjectCELL* a_cell, float a_waterLevel);
		[[nodiscard]] bool                      IsSummoned() const noexcept;
		[[nodiscard]] bool                      IsTrespassing() const;
		void                                    KillImmediate();
		void                                    PlayASound(BSSoundHandle& a_result, FormID a_formID, bool a_unk03, std::uint32_t a_flags);
		void                                    ProcessVATSAttack(MagicCaster* a_caster, bool a_hasTargetAnim, TESObjectREFR* a_target, bool a_leftHand);
		void                                    RemoveAnimationGraphEventSink(BSTEventSink<BSAnimationGraphEvent>* a_sink) const;
		void                                    RemoveCastScroll(SpellItem* a_spell, MagicSystem::CastingSource a_source);
		void                                    RemoveExtraArrows3D();
		void                                    RemoveFromFaction(TESFaction* a_faction);
		void                                    RemoveOutfitItems(BGSOutfit* a_outfit);
		bool                                    RemoveSpell(SpellItem* a_spell);
		[[nodiscard]] std::int32_t              RequestDetectionLevel(Actor* a_target, DETECTION_PRIORITY a_priority = DETECTION_PRIORITY::kNormal);
		bool                                    SetDefaultOutfit(BGSOutfit* a_outfit, bool a_update3D);
		void                                    SetLifeState(ACTOR_LIFE_STATE a_lifeState);
		bool                                    SetSleepOutfit(BGSOutfit* a_outfit, bool a_update3D);
		void                                    SetRotationX(float a_angle);
		void                                    SetRotationZ(float a_angle);
		void                                    StealAlarm(TESObjectREFR* a_ref, TESForm* a_object, std::int32_t a_num, std::int32_t a_total, TESForm* a_owner, bool a_allowWarning);
		void                                    StopAlarmOnActor();
		void                                    StopInteractingQuick(bool a_unk02);
		void                                    StopMoving(float a_delta);
		void                                    SwitchRace(TESRace* a_race, bool a_player);
		void                                    TrespassAlarm(TESObjectREFR* a_ref, TESForm* a_ownership, std::int32_t a_crime);
		void                                    UpdateArmorAbility(TESForm* a_armor, ExtraDataList* a_extraData);
		void                                    UpdateAwakeSound(NiAVObject* a_obj3D);
		void                                    Update3DModel();
		void                                    UpdateHairColor();
		void                                    UpdateRegenDelay(ActorValue a_actorValue, float a_regenDelay);
		void                                    UpdateSkinColor();
		void                                    UpdateWeaponAbility(TESForm* a_weapon, ExtraDataList* a_extraData, bool a_leftHand);
		void                                    VisitArmorAddon(TESObjectARMO* a_armor, TESObjectARMA* a_arma, std::function<void(bool a_firstPerson, NiAVObject& a_obj)> a_visitor);
		bool                                    VisitFactions(std::function<bool(TESFaction* a_faction, std::int8_t a_rank)> a_visitor);
		void                                    VisitSpells(ForEachSpellVisitor& a_visitor);
		[[nodiscard]] std::uint8_t              WhoIsCasting();
		bool                                    WouldBeStealing(const TESObjectREFR* a_target) const;

		struct ACTOR_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                           \
	stl::enumeration<BOOL_BITS, std::uint32_t>            boolBits;                          /* 0E0 */ \
	float                                                 updateTargetTimer;                 /* 0E4 */ \
	stl::enumeration<ACTOR_CRITICAL_STAGE, std::uint32_t> criticalStage;                     /* 0E8 */ \
	std::uint32_t                                         pad0EC;                            /* 0EC */ \
	AIProcess*                                            currentProcess;                    /* 0F0 */ \
	ObjectRefHandle                                       dialogueItemTarget;                /* 0F8 */ \
	ActorHandle                                           currentCombatTarget;               /* 0FC */ \
	ActorHandle                                           myKiller;                          /* 100 */ \
	float                                                 checkMyDeadBodyTimer;              /* 104 */ \
	float                                                 voiceTimer;                        /* 108 */ \
	float                                                 underWaterTimer;                   /* 10C */ \
	std::int32_t                                          thiefCrimeStamp;                   /* 110 */ \
	std::int32_t                                          actionValue;                       /* 114 */ \
	float                                                 timerOnAction;                     /* 118 */ \
	std::uint32_t                                         unk11C;                            /* 11C */ \
	NiPoint3                                              editorLocCoord;                    /* 120 */ \
	float                                                 editorLocRot;                      /* 12C */ \
	TESForm*                                              editorLocForm;                     /* 130 */ \
	BGSLocation*                                          editorLocation;                    /* 138 */ \
	ActorMover*                                           actorMover;                        /* 140 */ \
	BSTSmartPointer<MovementControllerNPC>                movementController;                /* 148 */ \
	TESPackage*                                           unk150;                            /* 150 */ \
	CombatController*                                     combatController;                  /* 158 */ \
	TESFaction*                                           vendorFaction;                     /* 160 */ \
	AITimeStamp                                           calculateVendorFactionTimer;       /* 168 */ \
	EmotionType                                           emotionType;                       /* 16C */ \
	std::uint32_t                                         emotionValue;                      /* 170 */ \
	std::uint32_t                                         unk174;                            /* 174 */ \
	std::uint32_t                                         unk178;                            /* 178 */ \
	std::uint32_t                                         intimidateBribeDayStamp;           /* 17C */ \
	std::uint64_t                                         unk180;                            /* 180 */ \
	BSTSmallArray<SpellItem*>                             addedSpells;                       /* 188 */ \
	ActorMagicCaster*                                     magicCasters[SlotTypes::kTotal];   /* 1A0 */ \
	MagicItem*                                            selectedSpells[SlotTypes::kTotal]; /* 1C0 */ \
	TESForm*                                              selectedPower;                     /* 1E0 */ \
	std::uint32_t                                         unk1E8;                            /* 1E8 */ \
	std::uint32_t                                         pad1EC;                            /* 1EC */ \
	TESRace*                                              race;                              /* 1F0 */ \
	float                                                 equippedWeight;                    /* 1F8 */ \
	stl::enumeration<BOOL_FLAGS, std::uint32_t>           boolFlags;                         /* 1FC */ \
	ActorValueStorage                                     avStorage;                         /* 200 */ \
	BGSDialogueBranch*                                    exclusiveBranch;                   /* 220 */ \
	Modifiers                                             healthModifiers;                   /* 228 */ \
	Modifiers                                             magickaModifiers;                  /* 234 */ \
	Modifiers                                             staminaModifiers;                  /* 240 */ \
	Modifiers                                             voicePointsModifiers;              /* 24C */ \
	float                                                 lastUpdate;                        /* 258 */ \
	std::uint32_t                                         lastSeenTime;                      /* 25C */ \
	BSTSmartPointer<BipedAnim>                            biped;                             /* 260 */ \
	float                                                 armorRating;                       /* 268 */ \
	float                                                 armorBaseFactorSum;                /* 26C */ \
	std::int8_t                                           soundCallBackSet;                  /* 271 */ \
	std::uint8_t                                          unk271;                            /* 270 */ \
	std::uint8_t                                          unk272;                            /* 272 */ \
	std::uint8_t                                          unk273;                            /* 273 */ \
	std::uint32_t                                         unk274;                            /* 274 */ \
	std::uint64_t                                         unk278;                            /* 278 */ \
	std::uint64_t                                         unk280;                            /* 280 */ \
	REX::W32::CRITICAL_SECTION                            unk288;                            /* 288 - havok related */

			RUNTIME_DATA_CONTENT
		};

		[[nodiscard]] inline ACTOR_RUNTIME_DATA& GetActorRuntimeData() noexcept
		{
			return REL::RelocateMemberIfNewer<ACTOR_RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0xE0, 0xE8);
		}

		[[nodiscard]] inline const ACTOR_RUNTIME_DATA& GetActorRuntimeData() const noexcept
		{
			return REL::RelocateMemberIfNewer<ACTOR_RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0xE0, 0xE8);
		}

		[[nodiscard]] inline MagicTarget* AsMagicTarget() noexcept
		{
			return &REL::RelocateMemberIfNewer<MagicTarget>(SKSE::RUNTIME_SSE_1_6_629, this, 0x98, 0xA0);
		}

		[[nodiscard]] inline const MagicTarget* AsMagicTarget() const noexcept
		{
			return &REL::RelocateMemberIfNewer<MagicTarget>(SKSE::RUNTIME_SSE_1_6_629, this, 0x98, 0xA0);
		}

		[[nodiscard]] inline ActorValueOwner* AsActorValueOwner() noexcept
		{
			return &REL::RelocateMemberIfNewer<ActorValueOwner>(SKSE::RUNTIME_SSE_1_6_629, this, 0xB0, 0xB8);
		}

		[[nodiscard]] inline const ActorValueOwner* AsActorValueOwner() const noexcept
		{
			return &REL::RelocateMemberIfNewer<ActorValueOwner>(SKSE::RUNTIME_SSE_1_6_629, this, 0xB0, 0xB8);
		}

		[[nodiscard]] inline ActorState* AsActorState() noexcept
		{
			return &REL::RelocateMemberIfNewer<ActorState>(SKSE::RUNTIME_SSE_1_6_629, this, 0xB8, 0xC0);
		}

		[[nodiscard]] inline const ActorState* AsActorState() const noexcept
		{
			return &REL::RelocateMemberIfNewer<ActorState>(SKSE::RUNTIME_SSE_1_6_629, this, 0xB8, 0xC0);
		}

		[[nodiscard]] inline BSTEventSink<BSTransformDeltaEvent>* AsBSTransformDeltaEventSink() noexcept
		{
			return &REL::RelocateMemberIfNewer<BSTEventSink<BSTransformDeltaEvent>>(SKSE::RUNTIME_SSE_1_6_629, this, 0xC8, 0xD0);
		}

		[[nodiscard]] inline const BSTEventSink<BSTransformDeltaEvent>* AsBSTransformDeltaEventSink() const noexcept
		{
			return &REL::RelocateMemberIfNewer<BSTEventSink<BSTransformDeltaEvent>>(SKSE::RUNTIME_SSE_1_6_629, this, 0xC8, 0xD0);
		}

		[[nodiscard]] inline BSTEventSink<bhkCharacterMoveFinishEvent>* AsCharacterMoveFinishEventSink() noexcept
		{
			return &REL::RelocateMemberIfNewer<BSTEventSink<bhkCharacterMoveFinishEvent>>(SKSE::RUNTIME_SSE_1_6_629, this, 0xD0, 0xD8);
		}

		[[nodiscard]] inline const BSTEventSink<bhkCharacterMoveFinishEvent>* AsCharacterMoveFinishEventSink() const noexcept
		{
			return &REL::RelocateMemberIfNewer<BSTEventSink<bhkCharacterMoveFinishEvent>>(SKSE::RUNTIME_SSE_1_6_629, this, 0xD0, 0xD8);
		}

		[[nodiscard]] inline IPostAnimationChannelUpdateFunctor* AsIPostAnimationChannelUpdateFunctor() noexcept
		{
			return &REL::RelocateMemberIfNewer<IPostAnimationChannelUpdateFunctor>(SKSE::RUNTIME_SSE_1_6_629, this, 0xD8, 0xE0);
		}

		[[nodiscard]] inline const IPostAnimationChannelUpdateFunctor* AsIPostAnimationChannelUpdateFunctor() const noexcept
		{
			return &REL::RelocateMemberIfNewer<IPostAnimationChannelUpdateFunctor>(SKSE::RUNTIME_SSE_1_6_629, this, 0xD8, 0xE0);
		}

		// members
#ifndef ENABLE_SKYRIM_AE
		RUNTIME_DATA_CONTENT
#endif

	private:
		void        CalculateCurrentVendorFaction() const;
		float       CalcEquippedWeight();
		TESFaction* GetCrimeFactionImpl() const;
		KEEP_FOR_RE()
	};
#ifndef ENABLE_SKYRIM_AE
	static_assert(sizeof(Actor) == 0x2B0);
#endif
}
#undef RUNTIME_DATA_CONTENT
