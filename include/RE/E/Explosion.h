#pragma once

#include "RE/B/BSResourceHandle.h"
#include "RE/B/BSSoundHandle.h"
#include "RE/F/FormTypes.h"
#include "RE/M/MagicSystem.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/T/TESObjectREFR.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BGSExplosion;
	class BGSMaterialType;
	class bhkCollisionObject;
	class bhkSimpleShapePhantom;
	class EffectSetting;
	class MagicItem;
	class QueuedFile;
	class NiPointLight;
	class NonActorMagicCaster;

	class Explosion : public TESObjectREFR
	{
	public:
		inline static constexpr auto RTTI = RTTI_Explosion;
		inline static constexpr auto VTABLE = VTABLE_Explosion;
		inline static constexpr auto FORMTYPE = FormType::Explosion;

		enum class Flags
		{
			kNone = 0,
			kDecalsPlaced = 1 << 0,
			kTargetsFound = 1 << 1,
			kTargetsProcessed = 1 << 2,
			kForcesApplied = 1 << 3,
			kIgnoreImageSpaceSwap = 1 << 4,
			kUnderwater = 1 << 5,
			kInitialized = 1 << 6,
			kNonHostile = 1 << 7,
			kWaterTestDone = 1 << 8,
			kSoundTestDone = 1 << 9
		};

		~Explosion() override;  // 00

		// override (TESObjectREFR)
		void         SaveGame(BGSSaveFormBuffer* a_buf) override;                   // 0E
		void         Revert(BGSLoadFormBuffer* a_buf) override;                     // 12
		void         SetActorCause(ActorCause* a_cause) override;                   // 50 - { actorCause = a_cause; }
		ActorCause*  GetActorCause() const override;                                // 51 - { return actorCause; }
		MagicCaster* GetMagicCaster(MagicSystem::CastingSource a_source) override;  // 5C
		void         InitHavok() override;                                          // 66
		void         Release3DRelatedData() override;                               // 6B
#ifndef SKYRIM_CROSS_VR
		// This is where in the TESObjectREFR vtable compatibility with SkyrimVR breaks.
		[[nodiscard]] Explosion* AsExplosion() override;                                                // 8E
		bool                     OnAddCellPerformQueueReference(TESObjectCELL& a_cell) const override;  // 90 - { return false; }
#endif

		// add
		SKYRIM_REL_VR_VIRTUAL void Initialize();           // SE/AE 0xA2, VR 0xA3
		SKYRIM_REL_VR_VIRTUAL void Update(float a_delta);  // SE/AE 0xA3, VR 0xA4
		SKYRIM_REL_VR_VIRTUAL void FindTargets();          // SE/AE 0xA4, VR 0xA5

		struct EXPLOSION_RUNTIME_DATA
		{
#define EXPLOSION_RUNTIME_DATA_CONTENT                                   \
	ModelDBHandle                      explosionDBHandle; /* 098, 0A0 */ \
	float                              age;               /* 0A0 */      \
	float                              lifetime;          /* 0A4 */      \
	float                              hitTime;           /* 0A8 */      \
	float                              radius;            /* 0AC */      \
	float                              imodRadius;        /* 0B0 */      \
	float                              unkB4;             /* 0B4 */      \
	bhkSimpleShapePhantom*             unkB8;             /* 0B8 */      \
	std::uint64_t                      unkC0;             /* 0C0 */      \
	std::uint64_t                      unkC8;             /* 0C8 */      \
	BSSoundHandle                      sound01;           /* 0D0 */      \
	BSSoundHandle                      sound02;           /* 0DC */      \
	NiPointer<NiPointLight>            light;             /* 0E8 */      \
	ActorHandle                        actorOwner;        /* 0F0 */      \
	ActorHandle                        unkF4;             /* 0F4 */      \
	std::uint32_t                      unkF8;             /* 0F8 */      \
	std::uint32_t                      padFC;             /* 0FC */      \
	NiPointer<ActorCause>              actorCause;        /* 100 */      \
	NonActorMagicCaster*               magicCaster;       /* 108 */      \
	TESObjectWEAP*                     weaponSource;      /* 110 */      \
	std::uint32_t                      frameCount;        /* 118 */      \
	NiPoint3                           unk11C;            /* 11C */      \
	NiPoint3                           negativeVelocity;  /* 128 */      \
	float                              damage;            /* 134 */      \
	float                              unk138;            /* 138 */      \
	REX::EnumSet<Flags, std::uint32_t> flags;             /* 13C */

			EXPLOSION_RUNTIME_DATA_CONTENT
		};

		RUNTIME_DATA_ACCESSOR_VERSIONED_EX(EXPLOSION_RUNTIME_DATA, GetExplosionRuntimeData, SKSE::RUNTIME_SSE_1_6_629, 0x98, 0xA0);
		// members
#if defined(EXCLUSIVE_SKYRIM_SE) || defined(EXCLUSIVE_SKYRIM_VR) || defined(EXCLUSIVE_SKYRIM_AE)
		EXPLOSION_RUNTIME_DATA_CONTENT;  // 098 (SE/VR), 0A0 (AE)
#endif
	};
	STATIC_ASSERT_SIZE(Explosion, 0x140, 0x148, 0x140);
}
#undef EXPLOSION_RUNTIME_DATA_CONTENT
