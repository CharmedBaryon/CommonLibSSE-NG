#pragma once

#include "RE/B/BGSProjectile.h"
#include "RE/B/BSAtomic.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSSoundHandle.h"
#include "RE/B/BSTList.h"
#include "RE/B/BSTSingleton.h"
#include "RE/C/CollisionLayers.h"
#include "RE/F/FormTypes.h"
#include "RE/I/ImpactResults.h"
#include "RE/M/MagicItem.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTransform.h"
#include "RE/T/TESObjectREFR.h"

namespace RE
{
	class Actor;
	class bhkCollisionObject;
	class bhkShape;
	class bhkSimpleShapePhantom;
	class BGSMaterialType;
	class BSLight;
	class CombatController;
	class MagicItem;
	class QueuedFile;

	class Projectile : public TESObjectREFR
	{
	public:
		inline static constexpr auto RTTI = RTTI_Projectile;
		inline static constexpr auto VTABLE = VTABLE_Projectile;

		struct WobbleControl
		{
		public:
			// members
			NiMatrix3        unk00;   // 00
			ProjectileHandle handle;  // 24
			float            wobble;  // 28
		};
		static_assert(sizeof(WobbleControl) == 0x2C);

		class Manager : public BSTSingletonSDM<Manager>
		{
		public:
			static Manager* GetSingleton();

			// members
			BSTArray<ProjectileHandle> unlimited;       // 08
			BSTArray<ProjectileHandle> limited;         // 20
			BSTArray<ProjectileHandle> pending;         // 38
			mutable BSSpinLock         projectileLock;  // 50
			BSTArray<WobbleControl>    wobble;          // 58
		};

		struct ProjectileRot
		{
		public:
			// members
			float x;
			float z;
		};
		static_assert(sizeof(ProjectileRot) == 0x08);

		struct LaunchData
		{
		public:
			inline static constexpr auto RTTI = RTTI_Projectile__LaunchData;
			inline static constexpr auto VTABLE = VTABLE_Projectile__LaunchData;

			virtual ~LaunchData() = default;

			LaunchData() = default;
			LaunchData(BGSProjectile* a_bproj, Actor* a_shooter, const NiPoint3& a_origin, const ProjectileRot& a_angles);
			LaunchData(Actor* a_shooter, const NiPoint3& a_origin, const ProjectileRot& a_angles, MagicItem* a_spell);
			LaunchData(Actor* a_shooter, const NiPoint3& a_origin, const ProjectileRot& a_angles, TESAmmo* a_ammo, TESObjectWEAP* a_weap);

			// members
			NiPoint3                   origin;                 // 08
			NiPoint3                   contactNormal;          // 14
			BGSProjectile*             projectileBase;         // 20
			TESObjectREFR*             shooter;                // 28
			CombatController*          combatController;       // 30
			TESObjectWEAP*             weaponSource;           // 38
			TESAmmo*                   ammoSource;             // 40
			float                      angleZ;                 // 48
			float                      angleX;                 // 4C
			void*                      unk50;                  // 50 - maps to Projectile unk110
			TESObjectREFR*             desiredTarget;          // 58
			float                      unk60;                  // 60 - maps to Projectile unk1A8
			float                      unk64;                  // 64 - maps to Projectile unk1AC
			TESObjectCELL*             parentCell;             // 68
			MagicItem*                 spell;                  // 70
			MagicSystem::CastingSource castingSource;          // 78
			std::uint32_t              pad7C;                  // 7C
			EnchantmentItem*           enchantItem;            // 80
			AlchemyItem*               poison;                 // 88
			std::int32_t               area;                   // 90
			float                      power;                  // 94
			float                      scale;                  // 98
			bool                       alwaysHit;              // 9C
			bool                       noDamageOutsideCombat;  // 9D
			bool                       autoAim;                // 9E
			bool                       chainShatter;           // 9F
			bool                       useOrigin;              // A0
			bool                       deferInitialization;    // A1
			bool                       forceConeOfFire;        // A2
		};
		static_assert(sizeof(LaunchData) == 0xA8);

		struct ImpactData
		{
		public:
			// members
			NiPoint3                                  desiredTargetLoc;    // 00
			NiPoint3                                  negativeVelocity;    // 0C
			ObjectRefHandle                           collidee;            // 18
			NiPointer<bhkCollisionObject>             colObj;              // 20
			BGSMaterialType*                          material;            // 28
			std::int32_t                              damageRootNodeType;  // 30
			stl::enumeration<COL_LAYER, std::int32_t> collidedLayer;       // 34
			NiNode*                                   damageRootNode;      // 38
			ImpactResult                              impactResult;        // 40
			std::uint16_t                             unk44;               // 44
			std::uint16_t                             unk46;               // 46
			std::uint8_t                              unk48;               // 48
			std::uint8_t                              unk49;               // 49
		};
		static_assert(sizeof(ImpactData) == 0x50);

		enum class Flags
		{
			kNone = 0,
			kUnk0 = 1 << 0,
			kNotAddThreat = 1 << 1,
			kUnk2 = 1 << 2,
			kUnk3 = 1 << 3,
			kIsTracer = 1 << 4,
			kFading = 1 << 5,
			kGravityUpdateModel = 1 << 6,
			kUnk7 = 1 << 7,
			kInited = 1 << 8,
			kChainShatter = 1 << 9,
			kUnk10 = 1 << 10,
			kUnk11 = 1 << 11,
			kAlwaysHit = 1 << 12,
			kHitScan = 1 << 13,
			kUnk14 = 1 << 14,
			kDestroyAfterHit = 1 << 15,
			kAddedToManager = 1 << 16,
			kNoDamageOutsideCombat = 1 << 17,
			kCanStartTrails = 1 << 18,
			kAggressiveActor = 1 << 19,
			kAddedVisualEffectOnGround = 1 << 20,
			kAutoAim = 1 << 21,
			kProcessedImpacts = 1 << 22,
			kUnk23 = 1 << 23,
			kUnk24 = 1 << 24,
			kDestroyed = 1 << 25,
			kUnk26 = 1 << 26,
			kUnk27 = 1 << 27,
			kIsDual = 1 << 28,
			kUseOrigin = 1 << 29,
			kUnk30 = 1 << 30,
			kMoved = 1 << 31
		};

		~Projectile() override;  // 00

		// override (TESObjectREFR)
		bool         Load(TESFile* a_mod) override;                                     // 06 - { return TESObjectREFR::Load(a_mod); }
		void         SaveGame(BGSSaveFormBuffer* a_buf) override;                       // 0E
		void         LoadGame(BGSLoadFormBuffer* a_buf) override;                       // 0F
		void         InitLoadGame(BGSLoadFormBuffer* a_buf) override;                   // 10
		void         FinishLoadGame(BGSLoadFormBuffer* a_buf) override;                 // 11
		void         Revert(BGSLoadFormBuffer* a_buf) override;                         // 12
		bool         GetAllowPromoteToPersistent() const override;                      // 47 - { return false; }
		bool         HasKeywordHelper(const BGSKeyword* a_keyword) const override;      // 48
		void         SetActorCause(ActorCause* a_cause) override;                       // 50 - { actorCause = a_cause; }
		ActorCause*  GetActorCause() const override;                                    // 51 - { return actorCause; }
		MagicCaster* GetMagicCaster(MagicSystem::CastingSource a_source) override;      // 5C
		bool         DetachHavok(NiAVObject* a_obj3D) override;                         // 65
		void         InitHavok() override;                                              // 66
		NiAVObject*  Load3D(bool a_backgroundLoading) override;                         // 6A
		void         Set3D(NiAVObject* a_object, bool a_queue3DTasks = true) override;  // 6C
#ifndef SKYRIM_CROSS_VR
		// Override functions past where Skyrim VR breaks compatibility.
		void                      MoveHavok(bool a_forceRec) override;                                   // 85 - { return; }
		void                      GetLinearVelocity(NiPoint3& a_velocity) const override;                // 86
		NiNode*                   GetFireNode() override;                                                // 8B
		[[nodiscard]] Projectile* AsProjectile() override;                                               // 8F - { return this; }
		bool                      OnAddCellPerformQueueReference(TESObjectCELL& a_cell) const override;  // 90 - { return false; }
#endif

		// add
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool  IsMissileProjectile();                                                                                                                                                     // A2 - { return 0; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool  IsGrenadeProjectile();                                                                                                                                                     // A3 - { return 0; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool  IsFlameProjectile();                                                                                                                                                       // A4 - { return 0; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool  IsBeamProjectile();                                                                                                                                                        // A5 - { return 0; }
		SKYRIM_REL_VR_VIRTUAL void                Unk_A6(void);                                                                                                                                                              // A6 - { return 0; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool  IsBarrierProjectile();                                                                                                                                                     // A7 - { return 0; }
		SKYRIM_REL_VR_VIRTUAL void                OnKill();                                                                                                                                                                  // A8 - { return; }
		SKYRIM_REL_VR_VIRTUAL void                Process3D();                                                                                                                                                               // A9 - { return; }
		SKYRIM_REL_VR_VIRTUAL void                PostLoad3D(NiAVObject* a_root);                                                                                                                                            // AA
		SKYRIM_REL_VR_VIRTUAL void                UpdateImpl(float a_delta);                                                                                                                                                 // AB
		SKYRIM_REL_VR_VIRTUAL bool                ProcessImpacts();                                                                                                                                                          // AC
		SKYRIM_REL_VR_VIRTUAL void                Update3D();                                                                                                                                                                // AD
		SKYRIM_REL_VR_VIRTUAL void                Unk_AE(void);                                                                                                                                                              // AE - { return 0; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL float GetPowerSpeedMult() const;                                                                                                                                                 // AF - { if (unk158) return 1.0; else return unk188; } - "float GetSpeed()"?
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL float GetWeaponSpeedMult() const;                                                                                                                                                // B0 - { return 1.0; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool  GetStopMainSoundAfterImpact();                                                                                                                                             // B1 - { return 0; }
		SKYRIM_REL_VR_VIRTUAL void                ReportHavokDeactivation();                                                                                                                                                 // B2 - { return; }
		SKYRIM_REL_VR_VIRTUAL bool                TurnOff(Actor* a_owner, bool a_noDeactivateSound);                                                                                                                         // B3
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool  IsPermanent() const;                                                                                                                                                       // B4 - { return TESDataHandler::GetSingleton()->IsGeneratedFormID(formID) == 0; }
		SKYRIM_REL_VR_VIRTUAL float               GetGravity();                                                                                                                                                              // B5 - { void* var = unk40; if ((var->unk80 >> 17) & 1) return 1.0; else return var->unk84; }
		SKYRIM_REL_VR_VIRTUAL void                CleanUpPointersOnDisable();                                                                                                                                                // B6
		SKYRIM_REL_VR_VIRTUAL bool                RunTargetPick();                                                                                                                                                           // B7
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool  GetKillOnCollision();                                                                                                                                                      // B8 - { return 1; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool  ShouldBeLimited();                                                                                                                                                         // B9 - { return 0; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool  TargetsWholeBody();                                                                                                                                                        // BA - { return 0; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL std::uint32_t GetCollisionGroup();                                                                                                                                               // BB
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bhkShape*     GetCollisionShape();                                                                                                                                               // BC
		SKYRIM_REL_VR_VIRTUAL void                        AddImpact(TESObjectREFR* a_ref, const NiPoint3& a_targetLoc, const NiPoint3& a_velocity, hkpCollidable* a_collidable, std::int32_t a_arg6, std::uint32_t a_arg7);  // BD
		SKYRIM_REL_VR_VIRTUAL bool                        HandleHits(hkpCollidable* a_collidable);                                                                                                                           // BE
		SKYRIM_REL_VR_VIRTUAL void                        OnTriggerEnter();                                                                                                                                                  // BF - { return; }
		SKYRIM_REL_VR_VIRTUAL void                        Handle3DLoaded();                                                                                                                                                  // C0 - { return; }
		[[nodiscard]] SKYRIM_REL_VR_VIRTUAL bool          ShouldUseDesiredTarget();                                                                                                                                          // C1 - { return 0; }

		BGSProjectile* GetProjectileBase() const;
		float          GetHeight() const;
		float          GetSpeed() const;

		static ProjectileHandle* Launch(ProjectileHandle* a_result, LaunchData& a_data) noexcept;
		static ProjectileHandle* LaunchSpell(ProjectileHandle* a_result, Actor* a_shooter, SpellItem* a_spell, const NiPoint3& a_origin, const ProjectileRot& a_angles) noexcept;
		static ProjectileHandle* LaunchSpell(ProjectileHandle* a_result, Actor* a_shooter, SpellItem* a_spell, MagicSystem::CastingSource a_source) noexcept;
		static ProjectileHandle* LaunchArrow(ProjectileHandle* a_result, Actor* a_shooter, TESAmmo* a_ammo, TESObjectWEAP* a_weap, const NiPoint3& a_origin, const ProjectileRot& a_angles) noexcept;
		static ProjectileHandle* LaunchArrow(ProjectileHandle* a_result, Actor* a_shooter, TESAmmo* a_ammo, TESObjectWEAP* a_weap) noexcept;

		struct PROJECTILE_RUNTIME_DATA
		{
#define PROJECTILE_RUNTIME_DATA_CONTENT                                                   \
	BSSimpleList<ImpactData*>  impacts;           /* 098, 0A0 */                          \
	NiTransform                unk0A8;            /* 0A8 */                               \
	float                      unk0DC;            /* 0DC */                               \
	bhkSimpleShapePhantom*     unk0E0;            /* 0E0 - smart ptr */                   \
	mutable BSSpinLock         unk0E8;            /* 0E8 */                               \
	NiPoint3                   velocity;          /* 0F0 */                               \
	NiPoint3                   linearVelocity;    /* 0FC */                               \
	NiPointer<BSLight>         light;             /* 108 - smart ptr */                   \
	void*                      unk110;            /* 110 - smart ptr */                   \
	NiPointer<ActorCause>      actorCause;        /* 118 */                               \
	ObjectRefHandle            shooter;           /* 120 */                               \
	ObjectRefHandle            desiredTarget;     /* 124 */                               \
	BSSoundHandle              sndHandle;         /* 128 */                               \
	BSSoundHandle              sndCountdown;      /* 134 */                               \
	std::uint32_t*             unk140;            /* 140 */                               \
	InventoryEntryData*        unk148;            /* 148 */                               \
	BGSExplosion*              explosion;         /* 150 */                               \
	MagicItem*                 spell;             /* 158 */                               \
	MagicSystem::CastingSource castingSource;     /* 160 */                               \
	std::uint32_t              pad164;            /* 164 */                               \
	EffectSetting*             avEffect;          /* 168 */                               \
	NiPointer<QueuedFile>      projectileDBFiles; /* 170 */                               \
	std::uint64_t              unk178;            /* 178 */                               \
	std::uint64_t              unk180;            /* 180 */                               \
	float                      power;             /* 188 - 14074B774 */                   \
	float                      speedMult;         /* 18C - 1407501B2 */                   \
	float                      range;             /* 190 */                               \
	float                      livingTime;        /* 194 */                               \
	float                      weaponDamage;      /* 198 */                               \
	float                      transparency;      /* 19C - for beam disappearing */       \
	float                      explosionTimer;    /* 1A0 */                               \
	std::uint32_t              unk1A4;            /* 1A4 */                               \
	float                      unk1A8;            /* 1A8 */                               \
	float                      unk1AC;            /* 1AC */                               \
	TESObjectWEAP*             weaponSource;      /* 1B0 */                               \
	TESAmmo*                   ammoSource;        /* 1B8 */                               \
	float                      distanceMoved;     /* 1C0 */                               \
	std::uint32_t              unk1C4;            /* 1C4 - pad? */                        \
	float                      scale;             /* 1C8 - for double cast model scale */ \
	std::uint32_t              flags;             /* 1CC */                               \
	bool                       unk1D0;            /* 1D0 */                               \
	bool                       unk1D1;            /* 1D1 */                               \
	std::uint8_t               unk1D2[6];         /* 1D2 */

			PROJECTILE_RUNTIME_DATA_CONTENT
		};

		[[nodiscard]] inline PROJECTILE_RUNTIME_DATA& GetProjectileRuntimeData() noexcept
		{
			return REL::RelocateMemberIfNewer<PROJECTILE_RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x98, 0xA0);
		}

		[[nodiscard]] inline const PROJECTILE_RUNTIME_DATA& GetProjectileRuntimeData() const noexcept
		{
			return REL::RelocateMemberIfNewer<PROJECTILE_RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x98, 0xA0);
		}

		// members
#ifndef ENABLE_SKYRIM_AE
		PROJECTILE_RUNTIME_DATA_CONTENT;
#endif
	private:
		KEEP_FOR_RE()
	};
#ifndef ENABLE_SKYRIM_AE
	static_assert(sizeof(Projectile) == 0x1D8);
#endif
}
#undef PROJECTILE_RUNTIME_DATA_CONTENT
