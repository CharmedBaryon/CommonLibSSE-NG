#pragma once

#include "RE/B/BGSDefaultObjectManager.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSHandleRefObject.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTList.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/B/BipedObjects.h"
#include "RE/E/ExtraDataList.h"
#include "RE/F/FormTypes.h"
#include "RE/H/hkVector4.h"
#include "RE/I/IAnimationGraphManagerHolder.h"
#include "RE/M/MagicSystem.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTransform.h"
#include "RE/T/TESForm.h"
#include "SKSE/Version.h"

namespace RE
{
	enum class LOCK_LEVEL;
	class hkpCollidable;
	class Actor;
	class ActorCause;
	class BGSAnimationSequencer;
	class BGSArtObject;
	class BGSDialogueBranch;
	class BipedAnim;
	class BSAnimNoteReceiver;
	class BSFaceGenAnimationData;
	class BSFaceGenNiNode;
	class BSFlattenedBoneTree;
	class DialogueResponse;
	class Explosion;
	class InventoryChanges;
	class InventoryEntryData;
	class MagicCaster;
	class MagicTarget;
	class ModelReferenceEffect;
	class NiAVObject;
	class NiControllerManager;
	class NiControllerSequence;
	class NiNode;
	class NiObject;
	class Projectile;
	class ShaderReferenceEffect;
	class TargetEntry;
	class TESActorBase;
	class TESBoundObject;
	class TESContainer;
	class TESEffectShader;
	class TrapData;
	class TrapEntry;
	struct BGSDecalGroup;
	struct BSAnimationGraphEvent;
	struct BSAnimationUpdateData;
	struct REFR_LOCK;

	enum class ITEM_REMOVE_REASON
	{
		kRemove,
		kSteal,
		kSelling,
		kDropping,
		kStoreInContainer,
		kStoreInTeammate
	};

	struct OBJ_REFR
	{
	public:
		// members
		TESBoundObject* objectReference;  // 00
		NiPoint3        angle;            // 08
		NiPoint3        location;         // 14
	};
	static_assert(sizeof(OBJ_REFR) == 0x20);

	struct LOADED_REF_DATA
	{
	public:
		// members
		BSTSmallArray<void*>  unk00;                // 00 - handleList?
		TESWaterForm*         currentWaterType;     // 18
		float                 relevantWaterHeight;  // 20
		float                 cachedRadius;         // 24
		std::uint16_t         flags;                // 28
		std::int16_t          underwaterCount;      // 2A
		std::uint32_t         pad2C;                // 2C
		std::uint64_t         unk30;                // 30 - AIProcess::Data0B8
		std::uint64_t         unk38;                // 38
		std::uint64_t         unk40;                // 40
		std::uint64_t         unk48;                // 48
		std::uint64_t         unk50;                // 50
		std::uint64_t         unk58;                // 58
		std::uint64_t         unk60;                // 60
		NiPointer<NiAVObject> data3D;               // 68
		void*                 unk70;                // 70 - smart ptr
	};
	static_assert(sizeof(LOADED_REF_DATA) == 0x78);

	NiSmartPointer(TESObjectREFR);

	class TESObjectREFR :
		public TESForm,                              // 00
		public BSHandleRefObject,                    // 20
		public BSTEventSink<BSAnimationGraphEvent>,  // 30
		public IAnimationGraphManagerHolder          // 38
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESObjectREFR;
		inline static constexpr auto VTABLE = VTABLE_TESObjectREFR;
		inline static constexpr auto FORMTYPE = FormType::Reference;

		using Count = std::int32_t;
		using InventoryCountMap = std::map<TESBoundObject*, Count>;
		using InventoryItemMap = std::map<TESBoundObject*, std::pair<Count, std::unique_ptr<InventoryEntryData>>>;
		using InventoryDropMap = std::map<TESBoundObject*, std::pair<Count, std::vector<ObjectRefHandle>>>;

		static inline constexpr auto DEFAULT_INVENTORY_FILTER = [](TESBoundObject&) { return true; };

		enum class MotionType  // hkpMotion::MotionType
		{
			kDynamic = 1,
			kSphereInertia = 2,
			kBoxInertia = 3,
			kKeyframed = 4,
			kFixed = 5,
			kThinBoxInertia = 6,
			kCharacter = 7
		};

		struct ChangeFlags
		{
			enum ChangeFlag : std::uint32_t
			{
				kMoved = 1 << 1,
				kHavokMoved = 1 << 2,
				kCellChanged = 1 << 3,
				kScale = 1 << 4,
				kInventory = 1 << 5,
				kOwnershipExtra = 1 << 6,
				kBaseObject = 1 << 7,
				kItemExtraData = 1 << 10,
				kAmmoExtra = 1 << 11,
				kLockExtra = 1 << 12,
				kEmpty = 1 << 21,
				kOpenDefaultState = 1 << 22,
				kOpenState = 1 << 23,
				kPromoted = 1 << 25,
				kActivatingChildren = 1 << 26,
				kLeveledInventory = 1 << 27,
				kAnimation = 1 << 28,
				kEncZoneExtra = 1 << 29,
				kCreatedOnlyExtra = 1 << 30,
				kGameOnlyExtra = (std::uint32_t)1 << 31
			};
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kIsGroundPiece = 1 << 4,
				kCollisionsDisabled = 1 << 4,  // ?

				kDeleted = 1 << 5,
				kHiddenFromLocalMap = 1 << 6,  // TESObjectSTAT
				kTurnOffFire = 1 << 7,

				kInaccessible = 1 << 8,            // TESObjectDOOR
				kLODRespectsEnableState = 1 << 8,  // TESObjectSTAT
				kStartsDead = 1 << 8,              // TESNPC
				kDoesntLightWater = 1 << 8,

				kMotionBlur = 1 << 9,  // TESObjectSTAT
				kPersistent = 1 << 10,
				kInitiallyDisabled = 1 << 11,
				kIgnored = 1 << 12,

				kStartUnconscious = 1 << 13,  // TESNPC
				kSkyMarker = 1 << 13,
				kHarvested = 1 << 13,  // TESObjectTREE

				kIsFullLOD = 1 << 16,   // Actor
				kNeverFades = 1 << 16,  // TESObjectLIGH

				kDoesntLightLandscape = 1 << 17,

				kIgnoreFriendlyHits = 1 << 20,  // Actor

				kNoAIAcquire = 1 << 25,
				kCollisionGeometry_Filter = 1 << 26,
				kCollisionGeometry_BoundingBox = 1 << 27,
				kReflectedByAutoWater = 1 << 28,

				kDontHavokSettle = 1 << 29,

				kGround = 1 << 30,
				kRespawns = 1 << 30,

				kMultibound = (std::uint32_t)1 << 31
			};
		};

		~TESObjectREFR() override;  // 00

		// override (TESForm)
		void                 InitializeData() override;                                                            // 04
		void                 ClearData() override;                                                                 // 05
		bool                 Load(TESFile* a_mod) override;                                                        // 06
		TESForm*             CreateDuplicateForm(bool a_createEditorID, void* a_arg2) override;                    // 09
		bool                 CheckSaveGame(BGSSaveFormBuffer* a_buf) override;                                     // 0D
		void                 SaveGame(BGSSaveFormBuffer* a_buf) override;                                          // 0E
		void                 LoadGame(BGSLoadFormBuffer* a_buf) override;                                          // 0F
		void                 InitLoadGame(BGSLoadFormBuffer* a_buf) override;                                      // 10
		void                 FinishLoadGame(BGSLoadFormBuffer* a_buf) override;                                    // 11
		void                 Revert(BGSLoadFormBuffer* a_buf) override;                                            // 12
		void                 InitItemImpl() override;                                                              // 13
		FormType             GetSavedFormType() const override;                                                    // 15
		void                 GetFormDetailedString(char* a_buf, std::uint32_t a_bufLen) override;                  // 16
		bool                 GetRandomAnim() const override;                                                       // 18 - { return data.objectReference->GetRandomAnim(); }
		bool                 IsHeadingMarker() const override;                                                     // 1A - { return data.objectReference->formType == FormType::Light ? (flags & RecordFlags::kNeverFades) != 0 : false; }
		bool                 GetDangerous() const override;                                                        // 1B - { return data.objectReference->GetDangerous(); }
		bool                 GetObstacle() const override;                                                         // 1D - { return data.objectReference ? data.objectReference->GetObstacle() : false; }
		bool                 GetOnLocalMap() const override;                                                       // 1F - { return (flags >> 9) & 1 && data.objectReference->GetOnLocalMap(); }
		bool                 GetMustUpdate() const override;                                                       // 20 - { return data.objectReference->GetMustUpdate(); }
		void                 SetOnLocalMap(bool a_set) override;                                                   // 21
		bool                 GetIgnoredBySandbox() const override;                                                 // 22
		void                 SetDelete(bool a_set) override;                                                       // 23
		void                 SetAltered(bool a_set) override;                                                      // 24
		bool                 IsWater() const override;                                                             // 2A - { return data.objectReference ? data.objectReference->IsWater() : false; }
		TESObjectREFR*       AsReference1() override;                                                              // 2B - { return this; }
		const TESObjectREFR* AsReference2() const override;                                                        // 2C - { return this; }
		bool                 BelongsInGroup(FORM* a_form, bool a_allowParentGroups, bool a_currentOnly) override;  // 30
		void                 CreateGroupData(FORM* a_form, FORM_GROUP* a_group) override;                          // 31
		const char*          GetFormEditorID() const override;                                                     // 32

		// override (BSTEventSink<BSAnimationGraphEvent>)
		BSEventNotifyControl ProcessEvent(const BSAnimationGraphEvent* a_event, BSTEventSource<BSAnimationGraphEvent>* a_dispatcher) override;  // 01

		// override (IAnimationGraphManagerHolder)
		bool GetAnimationGraphManagerImpl(BSTSmartPointer<BSAnimationGraphManager>& a_out) const override;                                                 // 02
		bool SetAnimationGraphManagerImpl(BSTSmartPointer<BSAnimationGraphManager>& a_in) override;                                                        // 03
		bool PopulateGraphNodesToTarget(BSScrapArray<NiAVObject*>& a_nodes) override;                                                                      // 04
		bool ConstructAnimationGraph(BSTSmartPointer<BShkbAnimationGraph>& a_out) override;                                                                // 05
		bool SetupAnimEventSinks(const BSTSmartPointer<BShkbAnimationGraph>& a_animGraph) override;                                                        // 08
		void PostChangeAnimationManager(const BSTSmartPointer<BShkbAnimationGraph>& a_arg1, const BSTSmartPointer<BShkbAnimationGraph>& a_arg2) override;  // 0D

		// add
		virtual void                                            Predestroy();                                                                                                                                                                                                // 3B
		[[nodiscard]] virtual BGSLocation*                      GetEditorLocation1() const;                                                                                                                                                                                  // 3C
		virtual bool                                            GetEditorLocation2(NiPoint3& a_outPos, NiPoint3& a_outRot, TESForm*& a_outWorldOrCell, TESObjectCELL* a_fallback);                                                                                           // 3D
		virtual void                                            ForceEditorLocation(BGSLocation* a_location);                                                                                                                                                                // 3E
		virtual void                                            Update3DPosition(bool a_warp);                                                                                                                                                                               // 3F
		virtual void                                            UpdateSoundCallBack(bool a_endSceneAction);                                                                                                                                                                  // 40
		virtual bool                                            SetDialogueWithPlayer(bool a_flag, bool a_forceGreet, TESTopicInfo* a_topic);                                                                                                                                // 41
		virtual void                                            DamageObject(float a_objectHealth, bool a_arg3);                                                                                                                                                             // 42
		[[nodiscard]] virtual bool                              GetFullLODRef() const;                                                                                                                                                                                       // 43
		virtual void                                            SetFullLODRef(bool a_set);                                                                                                                                                                                   // 44
		[[nodiscard]] virtual BGSAnimationSequencer*            GetSequencer() const;                                                                                                                                                                                        // 45
		[[nodiscard]] virtual bool                              QCanUpdateSync() const;                                                                                                                                                                                      // 46 - { return true; }
		[[nodiscard]] virtual bool                              GetAllowPromoteToPersistent() const;                                                                                                                                                                         // 47 - { return true; }
		[[nodiscard]] virtual bool                              HasKeywordHelper(const BGSKeyword* a_keyword) const;                                                                                                                                                         // 48
		[[nodiscard]] virtual TESPackage*                       CheckForCurrentAliasPackage();                                                                                                                                                                               // 49 - { return 0; }
		[[nodiscard]] virtual BGSScene*                         GetCurrentScene() const;                                                                                                                                                                                     // 4A
		virtual void                                            SetCurrentScene(BGSScene* a_scene);                                                                                                                                                                          // 4B
		virtual bool                                            UpdateInDialogue(DialogueResponse* a_response, bool a_unused);                                                                                                                                               // 4C
		[[nodiscard]] virtual BGSDialogueBranch*                GetExclusiveBranch() const;                                                                                                                                                                                  // 4D
		virtual void                                            SetExclusiveBranch(BGSDialogueBranch* a_branch);                                                                                                                                                             // 4E
		virtual void                                            PauseCurrentDialogue();                                                                                                                                                                                      // 4F
		virtual void                                            SetActorCause(ActorCause* a_cause);                                                                                                                                                                          // 50
		[[nodiscard]] virtual ActorCause*                       GetActorCause() const;                                                                                                                                                                                       // 51
		[[nodiscard]] virtual NiPoint3                          GetStartingAngle() const;                                                                                                                                                                                    // 52
		[[nodiscard]] virtual NiPoint3                          GetStartingLocation() const;                                                                                                                                                                                 // 53
		virtual void                                            SetStartingPosition(const NiPoint3& a_pos);                                                                                                                                                                  // 54
		virtual void                                            UpdateRefLight();                                                                                                                                                                                            // 55
		virtual ObjectRefHandle                                 RemoveItem(TESBoundObject* a_item, std::int32_t a_count, ITEM_REMOVE_REASON a_reason, ExtraDataList* a_extraList, TESObjectREFR* a_moveToRef, const NiPoint3* a_dropLoc = 0, const NiPoint3* a_rotate = 0);  // 56
		virtual bool                                            AddWornItem(TESBoundObject* a_item, std::int32_t a_count, bool a_forceEquip, std::uint32_t a_arg4, std::uint32_t a_arg5);                                                                                    // 57
		virtual void                                            DoTrap1(TrapData& a_data);                                                                                                                                                                                   // 58 - { return; }
		virtual void                                            DoTrap2(TrapEntry* a_trap, TargetEntry* a_target);                                                                                                                                                           // 59 - { return; }
		virtual void                                            AddObjectToContainer(TESBoundObject* a_object, ExtraDataList* a_extraList, std::int32_t a_count, TESObjectREFR* a_fromRefr);                                                                                 // 5A
		[[nodiscard]] virtual NiPoint3                          GetLookingAtLocation() const;                                                                                                                                                                                // 5B
		[[nodiscard]] virtual MagicCaster*                      GetMagicCaster(MagicSystem::CastingSource a_source);                                                                                                                                                         // 5C
		[[nodiscard]] virtual MagicTarget*                      GetMagicTarget();                                                                                                                                                                                            // 5D
		[[nodiscard]] virtual bool                              IsChild() const;                                                                                                                                                                                             // 5E - { return false; }
		virtual TESActorBase*                                   GetTemplateActorBase();                                                                                                                                                                                      // 5F - { return 0; }
		virtual void                                            SetTemplateActorBase(TESActorBase* a_template);                                                                                                                                                              // 60 - { return; }
		[[nodiscard]] virtual BSFaceGenNiNode*                  GetFaceNodeSkinned();                                                                                                                                                                                        // 61 - { return 0; }
		[[nodiscard]] virtual BSFaceGenNiNode*                  GetFaceNode();                                                                                                                                                                                               // 62 - { return GetFaceNodeSkinned(); }
		[[nodiscard]] virtual BSFaceGenAnimationData*           GetFaceGenAnimationData();                                                                                                                                                                                   // 63 - { return 0; }
		virtual bool                                            ClampToGround();                                                                                                                                                                                             // 64
		virtual bool                                            DetachHavok(NiAVObject* a_obj3D);                                                                                                                                                                            // 65
		virtual void                                            InitHavok();                                                                                                                                                                                                 // 66
		virtual void                                            Unk_67(void);                                                                                                                                                                                                // 67 - { return; }
		virtual void                                            Unk_68(void);                                                                                                                                                                                                // 68 - { return; }
		virtual void                                            Unk_69(void);                                                                                                                                                                                                // 69 - { return; }
		virtual NiAVObject*                                     Load3D(bool a_backgroundLoading);                                                                                                                                                                            // 6A
		virtual void                                            Release3DRelatedData();                                                                                                                                                                                      // 6B
		virtual void                                            Set3D(NiAVObject* a_object, bool a_queue3DTasks = true);                                                                                                                                                     // 6C
		virtual bool                                            ShouldBackgroundClone() const;                                                                                                                                                                               // 6D
		virtual void                                            Unk_6E(void);                                                                                                                                                                                                // 6E - { return; }
		[[nodiscard]] virtual NiAVObject*                       Get3D1(bool a_firstPerson) const;                                                                                                                                                                            // 6F - { return Get3D2(); }
		[[nodiscard]] virtual NiAVObject*                       Get3D2() const;                                                                                                                                                                                              // 70
		[[nodiscard]] virtual bool                              Is3rdPersonVisible() const;                                                                                                                                                                                  // 71 - { return true; }
		virtual bool                                            PopulateGraphProjectsToLoad(void) const;                                                                                                                                                                     // 72
		[[nodiscard]] virtual NiPoint3                          GetBoundMin() const;                                                                                                                                                                                         // 73
		[[nodiscard]] virtual NiPoint3                          GetBoundMax() const;                                                                                                                                                                                         // 74
		virtual void                                            Unk_75(void);                                                                                                                                                                                                // 75 - { return 0; }
		virtual bool                                            InitNonNPCAnimation(NiNode& a_nodeForAnim);                                                                                                                                                                  // 76
		virtual bool                                            CheckAndFixSkinAndBoneOrder(NiNode& a_nodeToTest);                                                                                                                                                           // 77
		virtual void                                            Unk_78(void);                                                                                                                                                                                                // 78
		virtual void                                            ModifyAnimationUpdateData(BSAnimationUpdateData& a_data);                                                                                                                                                    // 79 - { return; }
		[[nodiscard]] virtual bool                              ShouldSaveAnimationOnUnloading() const;                                                                                                                                                                      // 7A
		[[nodiscard]] virtual bool                              ShouldSaveAnimationOnSaving() const;                                                                                                                                                                         // 7B
		[[nodiscard]] virtual bool                              ShouldPerformRevert() const;                                                                                                                                                                                 // 7C - { return true; }
		virtual void                                            UpdateAnimation(float a_delta);                                                                                                                                                                              // 7D
		[[nodiscard]] virtual const BSTSmartPointer<BipedAnim>& GetBiped1(bool a_firstPerson) const;                                                                                                                                                                         // 7E - { return GetBiped2(); }
		[[nodiscard]] virtual const BSTSmartPointer<BipedAnim>& GetBiped2() const;                                                                                                                                                                                           // 7F
		[[nodiscard]] virtual const BSTSmartPointer<BipedAnim>& GetCurrentBiped() const;                                                                                                                                                                                     // 80 - { return GetBiped2(); }
		virtual void                                            SetBiped(const BSTSmartPointer<BipedAnim>& a_biped);                                                                                                                                                         // 81 - { return; }																																																																			 // Virtual functions defined in TESObjectREFR after the vtable structure becomes different in VR.
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		SKYRIM_REL_VR_VIRTUAL void AttachWeapon(RE::TESObjectWEAP* a_weapon, bool attachToShieldHand);  // 82 - Virtual in VR, non-virtual in SE/AE. Shield hand may be just left hand?
#endif
		SKYRIM_REL_VR_VIRTUAL void RemoveWeapon(BIPED_OBJECT equipIndex);  // 82 - { return; }
		SKYRIM_REL_VR_VIRTUAL void Unk_83(void);                           // 83 - { return; }
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		virtual void Unk_84(void);
#endif
		SKYRIM_REL_VR_VIRTUAL void                         SetObjectReference(TESBoundObject* a_object);                                         // 84 - sets flag 24 if the object has destructibles
		SKYRIM_REL_VR_VIRTUAL void                         MoveHavok(bool a_forceRec);                                                           // 85
		SKYRIM_REL_VR_VIRTUAL void                         GetLinearVelocity(NiPoint3& a_velocity) const;                                        // 86
		SKYRIM_REL_VR_VIRTUAL void                         SetActionComplete(bool a_set);                                                        // 87 - { return; }
		SKYRIM_REL_VR_VIRTUAL void                         SetMovementComplete(bool a_set);                                                      // 88 - { return; }
		SKYRIM_REL_VR_VIRTUAL void                         Disable();                                                                            // 89
		SKYRIM_REL_VR_VIRTUAL void                         ResetInventory(bool a_leveledOnly);                                                   // 8A
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL NiNode*        GetFireNode();                                                                        // 8B - { return 0; }
		SKYRIM_REL_VR_VIRTUAL void                         SetFireNode(NiNode* a_fireNode);                                                      // 8C - { return; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL NiAVObject*    GetCurrent3D() const;                                                                 // 8D - { return Get3D2(); }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL Explosion*     AsExplosion();                                                                        // 8E - { return 0; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL Projectile*    AsProjectile();                                                                       // 8F - { return 0; }
		SKYRIM_REL_VR_VIRTUAL bool                         OnAddCellPerformQueueReference(TESObjectCELL& a_cell) const;                          // 90 - { return true; }
		SKYRIM_REL_VR_VIRTUAL void                         DoMoveToHigh();                                                                       // 91 - { return; }
		SKYRIM_REL_VR_VIRTUAL void                         TryMoveToMiddleLow();                                                                 // 92 - { return; }
		SKYRIM_REL_VR_VIRTUAL bool                         TryChangeSkyCellActorsProcessLevel();                                                 // 93 - { return false; }
		SKYRIM_REL_VR_VIRTUAL void                         Unk_94(void);                                                                         // 94 - { return; }
		SKYRIM_REL_VR_VIRTUAL void                         TryUpdateActorLastSeenTime();                                                         // 95 - { return; }
		SKYRIM_REL_VR_VIRTUAL void                         Unk_96(void);                                                                         // 96 - related to lockpicking
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL TESObjectCELL* GetSaveParentCell() const;                                                            // 97
		SKYRIM_REL_VR_VIRTUAL void                         SetParentCell(TESObjectCELL* a_cell);                                                 // 98
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool           IsDead(bool a_notEssential = true) const;                                             // 99
		SKYRIM_REL_VR_VIRTUAL BSAnimNoteReceiver*          CreateAnimNoteReceiver();                                                             // 9A
		SKYRIM_REL_VR_VIRTUAL BSAnimNoteReceiver*          GetAnimNoteReceiver();                                                                // 9B
		SKYRIM_REL_VR_VIRTUAL bool                         ProcessInWater(hkpCollidable* a_collidable, float a_waterHeight, float a_deltaTime);  // 9C
		SKYRIM_REL_VR_VIRTUAL bool                         ApplyCurrent(float a_velocityTime, const hkVector4& a_velocity);                      // 9D - { return 0; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL TESAmmo*       GetCurrentAmmo() const;                                                               // 9E - { return 0; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL BGSDecalGroup* GetDecalGroup() const;                                                                // 9F
		SKYRIM_REL_VR_VIRTUAL bool                         Unk_A0(NiAVObject* a_node, float& a_angleX, float& a_angleZ, NiPoint3& a_pos);        // A0
		SKYRIM_REL_VR_VIRTUAL void                         UnequipItem(std::uint64_t a_arg1, TESBoundObject* a_object);                          // A1 - { return; }

		static NiPointer<TESObjectREFR> LookupByHandle(RefHandle a_refHandle);
		static bool                     LookupByHandle(RefHandle a_refHandle, NiPointer<TESObjectREFR>& a_refrOut);
		static TESObjectREFR*           FindReferenceFor3D(NiAVObject* a_object3D);

		bool                                            ActivateRef(TESObjectREFR* a_activator, uint8_t a_arg2, TESBoundObject* a_object, int32_t a_count, bool a_defaultProcessingOnly);
		ModelReferenceEffect*                           ApplyArtObject(BGSArtObject* a_artObject, float a_duration = -1.0f, TESObjectREFR* a_facingRef = nullptr, bool a_faceTarget = false, bool a_attachToCamera = false, NiAVObject* a_attachNode = nullptr, bool a_interfaceEffect = false);
		ShaderReferenceEffect*                          ApplyEffectShader(TESEffectShader* a_effectShader, float a_duration = -1.0f, TESObjectREFR* a_facingRef = nullptr, bool a_faceTarget = false, bool a_attachToCamera = false, NiAVObject* a_attachNode = nullptr, bool a_interfaceEffect = false);
		[[nodiscard]] bool                              CanBeMoved();
		ObjectRefHandle                                 CreateRefHandle();
		void                                            DoTrap(TrapData& a_data);
		void                                            DoTrap(TrapEntry* a_trap, TargetEntry* a_target);
		void                                            Enable(bool a_resetInventory);
		[[nodiscard]] NiAVObject*                       Get3D() const;
		[[nodiscard]] NiAVObject*                       Get3D(bool a_firstPerson) const;
		[[nodiscard]] TESNPC*                           GetActorOwner();
		[[nodiscard]] NiPoint3                          GetAngle() const;
		[[nodiscard]] float                             GetAngleX() const;
		[[nodiscard]] float                             GetAngleY() const;
		[[nodiscard]] float                             GetAngleZ() const;
		[[nodiscard]] float                             GetBaseHeight() const;
		[[nodiscard]] TESBoundObject*                   GetBaseObject();
		[[nodiscard]] const TESBoundObject*             GetBaseObject() const;
		[[nodiscard]] const BSTSmartPointer<BipedAnim>& GetBiped() const;
		[[nodiscard]] const BSTSmartPointer<BipedAnim>& GetBiped(bool a_firstPerson) const;
		[[nodiscard]] std::uint16_t                     GetCalcLevel(bool a_adjustLevel) const;
		[[nodiscard]] TESContainer*                     GetContainer() const;
		[[nodiscard]] BGSLocation*                      GetCurrentLocation() const;
		[[nodiscard]] const char*                       GetDisplayFullName();
		[[nodiscard]] InventoryDropMap                  GetDroppedInventory();
		[[nodiscard]] InventoryDropMap                  GetDroppedInventory(std::function<bool(TESBoundObject&)> a_filter);
		[[nodiscard]] BGSLocation*                      GetEditorLocation() const;
		[[nodiscard]] bool                              GetEditorLocation(NiPoint3& a_outPos, NiPoint3& a_outRot, TESForm*& a_outWorldOrCell, TESObjectCELL* a_fallback);
		[[nodiscard]] std::optional<double>             GetEnchantmentCharge() const;
		[[nodiscard]] TESFaction*                       GetFactionOwner();
		[[nodiscard]] ObjectRefHandle                   GetHandle();
		[[nodiscard]] float                             GetHeadingAngle(const RE::NiPoint3& a_pos, bool a_abs);
		[[nodiscard]] float                             GetHeight() const;
		[[nodiscard]] InventoryItemMap                  GetInventory();
		[[nodiscard]] InventoryItemMap                  GetInventory(std::function<bool(TESBoundObject&)> a_filter, bool a_noInit = false);
		[[nodiscard]] std::int32_t                      GetInventoryCount(bool no_init = false);
		[[nodiscard]] InventoryCountMap                 GetInventoryCounts();
		[[nodiscard]] InventoryCountMap                 GetInventoryCounts(std::function<bool(TESBoundObject&)> a_filter, bool a_noInit = false);
		[[nodiscard]] InventoryChanges*                 GetInventoryChanges(bool a_noInit = false);
		[[nodiscard]] TESObjectREFR*                    GetLinkedRef(BGSKeyword* a_keyword);
		[[nodiscard]] REFR_LOCK*                        GetLock() const;
		[[nodiscard]] LOCK_LEVEL                        GetLockLevel() const;
		[[nodiscard]] const char*                       GetName() const;
		[[nodiscard]] NiAVObject*                       GetNodeByName(const BSFixedString& a_nodeName);
		[[nodiscard]] constexpr TESBoundObject*         GetObjectReference() const noexcept { return data.objectReference; }
		[[nodiscard]] TESForm*                          GetOwner() const;
		[[nodiscard]] constexpr TESObjectCELL*          GetParentCell() const noexcept { return parentCell; }
		[[nodiscard]] constexpr NiPoint3                GetPosition() const noexcept { return data.location; }
		[[nodiscard]] constexpr float                   GetPositionX() const noexcept { return data.location.x; }
		[[nodiscard]] constexpr float                   GetPositionY() const noexcept { return data.location.y; }
		[[nodiscard]] constexpr float                   GetPositionZ() const noexcept { return data.location.z; }
		[[nodiscard]] float                             GetScale() const;
		[[nodiscard]] NiControllerSequence*             GetSequence(stl::zstring a_name) const;
		[[nodiscard]] std::uint32_t                     GetStealValue(const InventoryEntryData* a_entryData, std::uint32_t a_numItems, bool a_useMult) const;
		void                                            GetTransform(NiTransform& a_transform) const;
		[[nodiscard]] float                             GetWaterHeight() const;
		[[nodiscard]] float                             GetWeight() const;
		[[nodiscard]] float                             GetWeightInContainer();
		[[nodiscard]] TESWorldSpace*                    GetWorldspace() const;
		[[nodiscard]] bool                              HasCollision() const;
		[[nodiscard]] bool                              HasContainer() const;
		[[nodiscard]] bool                              HasKeyword(const BGSKeyword* a_keyword) const;
		[[nodiscard]] bool                              HasKeywordInArray(const std::vector<BGSKeyword*>& a_keywords, bool a_matchAll) const;
		[[nodiscard]] bool                              HasKeywordInList(BGSListForm* a_keywordList, bool a_matchAll) const;
		bool                                            HasKeywordWithType(DEFAULT_OBJECT keywordType) const;
		bool                                            HasKeywordWithType(DefaultObjectID keywordType) const;
		[[nodiscard]] bool                              HasQuestObject() const;
		void                                            InitChildActivates(TESObjectREFR* a_actionRef);
		bool                                            InitInventoryIfRequired(bool a_ignoreContainerExtraData = false);
		bool                                            Is3DLoaded() const;
		bool                                            IsActivationBlocked() const;
		bool                                            IsAnimal() const;
		ModelReferenceEffect*                           InstantiateHitArt(BGSArtObject* a_art, float a_dur, TESObjectREFR* a_facingRef, bool a_faceTarget, bool a_attachToCamera, NiAVObject* a_attachNode = nullptr, bool a_interfaceEffect = false);
		ShaderReferenceEffect*                          InstantiateHitShader(TESEffectShader* a_shader, float a_dur, TESObjectREFR* a_facingRef = nullptr, bool a_faceTarget = false, bool a_attachToCamera = false, NiAVObject* a_attachNode = nullptr, bool a_interfaceEffect = false);
		[[nodiscard]] bool                              IsAnOwner(const Actor* a_testOwner, bool a_useFaction, bool a_requiresOwner) const;
		[[nodiscard]] bool                              IsCrimeToActivate();
		[[nodiscard]] bool                              IsDisabled() const;
		bool                                            IsDragon() const;
		[[nodiscard]] bool                              IsEnchanted() const;
		[[nodiscard]] bool                              IsHorse() const;
		bool                                            IsHumanoid() const;
		[[nodiscard]] bool                              IsInitiallyDisabled() const;
		[[nodiscard]] bool                              IsInWater() const;
		bool                                            IsJewelry() const;
		[[nodiscard]] bool                              IsLocked() const;
		[[nodiscard]] bool                              IsMarkedForDeletion() const;
		[[nodiscard]] bool                              IsOffLimits();
		[[nodiscard]] bool                              IsPersistent() const;
		[[nodiscard]] float                             IsPointDeepUnderWater(float a_zPos, TESObjectCELL* a_cell) const;
		[[nodiscard]] bool                              IsPointSubmergedMoreThan(const NiPoint3& a_pos, TESObjectCELL* a_cell, float a_waterLevel) const;
		void                                            MoveTo(TESObjectREFR* a_target);
		bool                                            MoveToNode(TESObjectREFR* a_target, const BSFixedString& a_nodeName);
		bool                                            MoveToNode(TESObjectREFR* a_target, NiAVObject* a_node);
		bool                                            NameIncludes(std::string a_word);
		void                                            OpenContainer(std::int32_t a_openType) const;
		NiPointer<TESObjectREFR>                        PlaceObjectAtMe(TESBoundObject* a_baseToPlace, bool a_forcePersist) const;
		void                                            PlayAnimation(stl::zstring a_from, stl::zstring a_to);
		void                                            PlayAnimation(NiControllerManager* a_manager, NiControllerSequence* a_toSeq, NiControllerSequence* a_fromSeq);
		void                                            SetActivationBlocked(bool a_blocked);
		void                                            SetCollision(bool a_enable);
		bool                                            SetDisplayName(const BSFixedString& a_name, bool a_force);
		void                                            SetEncounterZone(BGSEncounterZone* a_zone);
		bool                                            SetMotionType(MotionType a_motionType, bool a_allowActivate = true);
		void                                            SetPosition(float a_x, float a_y, float a_z);
		void                                            SetPosition(NiPoint3 a_pos);

		struct REFERENCE_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                 \
	std::uint64_t unk88;        /* 88, 90 */ \
	std::uint16_t refScale;     /* 90, 98 */ \
	std::int8_t   modelState;   /* 92, 9A */ \
	bool          preDestroyed; /* 93, 9B */ \
	std::uint32_t pad94;        /* 94, 9C */

			RUNTIME_DATA_CONTENT
		};

		[[nodiscard]] inline REFERENCE_RUNTIME_DATA& GetReferenceRuntimeData() noexcept
		{
			return REL::RelocateMemberIfNewer<REFERENCE_RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x88, 0x90);
		}

		[[nodiscard]] inline const REFERENCE_RUNTIME_DATA& GetReferenceRuntimeData() const noexcept
		{
			return REL::RelocateMemberIfNewer<REFERENCE_RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x88, 0x90);
		}

		// members
		OBJ_REFR         data;        // 40
		TESObjectCELL*   parentCell;  // 60
		LOADED_REF_DATA* loadedData;  // 68
		ExtraDataList    extraList;   // 70

#ifndef ENABLE_SKYRIM_AE
		RUNTIME_DATA_CONTENT
#endif

	private:
		InventoryChanges* ForceInitInventoryChanges();
		InventoryChanges* MakeInventoryChanges();
		void              MoveTo_Impl(const ObjectRefHandle& a_targetHandle, TESObjectCELL* a_targetCell, TESWorldSpace* a_selfWorldSpace, const NiPoint3& a_position, const NiPoint3& a_rotation);
		void              PlayAnimation_Impl(NiControllerManager* a_manager, NiControllerSequence* a_toSeq, NiControllerSequence* a_fromSeq, bool a_arg4 = false);
		KEEP_FOR_RE()
	};
#ifndef ENABLE_SKYRIM_AE
	static_assert(sizeof(TESObjectREFR) == 0x98);
#endif
}
#undef RUNTIME_DATA_CONTENT
