#pragma once

#include "RE/B/BSTArray.h"
#include "RE/F/FormTypes.h"
#include "RE/H/hkRefPtr.h"
#include "RE/I/ImpactResults.h"
#include "RE/N/NiPoint3.h"
#include "RE/P/Projectile.h"

namespace RE
{
	class hkpSphereShape;

	class ConeProjectile : public Projectile
	{
	public:
		inline static constexpr auto RTTI = RTTI_ConeProjectile;
		inline static constexpr auto VTABLE = VTABLE_ConeProjectile;
		inline static constexpr auto FORMTYPE = FormType::ProjectileCone;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
			};
		};

		~ConeProjectile() override;  // 00

		// override (Projectile)
		void SaveGame(BGSSaveFormBuffer* a_buf) override;        // 0E
		void LoadGame(BGSLoadFormBuffer* a_buf) override;        // 0F
		void InitLoadGame(BGSLoadFormBuffer* a_buf) override;    // 10
		void FinishLoadGame(BGSLoadFormBuffer* a_buf) override;  // 11
		void Revert(BGSLoadFormBuffer* a_buf) override;          // 12
#ifndef SKYRIM_CROSS_VR
		void      Process3D() override;                                                                                                                                                       // A9
		void      UpdateImpl(float a_delta) override;                                                                                                                                         // AB
		bool      ProcessImpacts() override;                                                                                                                                                  // AC
		bool      GetKillOnCollision() override;                                                                                                                                              // B8 - { return 0; }
		bhkShape* GetCollisionShape() override;                                                                                                                                               // BC
		void      AddImpact(TESObjectREFR* a_ref, const NiPoint3& a_targetLoc, const NiPoint3& a_velocity, hkpCollidable* a_collidable, std::int32_t a_arg6, std::uint32_t a_arg7) override;  // BD
		bool      HandleHits(hkpCollidable* a_collidable) override;                                                                                                                           // BE
		void      Handle3DLoaded() override;                                                                                                                                                  // C0
#endif

		// add
		SKYRIM_REL_VR_VIRTUAL void Unk_C2(void);  // C2 - { return 1; }

		inline float GetHeight() const
		{
			return GetConeRuntimeData().initialCollisionSphereRadius * 2;
		}

		struct CONE_RUNTIME_DATA
		{
#define CONE_RUNTIME_DATA_CONTENT                                    \
	ImpactResult             impactResult;                 /* 1D8 */ \
	float                    environmentTimer;             /* 1DC */ \
	float                    coneAngleTangent;             /* 1E0 */ \
	float                    initialCollisionSphereRadius; /* 1E4 */ \
	NiPoint3                 origin;                       /* 1E8 */ \
	std::uint32_t            pad1F4;                       /* 1F4 */ \
	hkRefPtr<hkpSphereShape> collisionShape;               /* 1F8 */ \
	BSTArray<void*>          collisions;                   /* 200 */

			CONE_RUNTIME_DATA_CONTENT
		};

		[[nodiscard]] inline CONE_RUNTIME_DATA& GetConeRuntimeData() noexcept
		{
			return REL::RelocateMemberIfNewer<CONE_RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x1D8, 0x1E0);
		}

		[[nodiscard]] inline const CONE_RUNTIME_DATA& GetConeRuntimeData() const noexcept
		{
			return REL::RelocateMemberIfNewer<CONE_RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x1D8, 0x1E0);
		}

		// members
#ifndef ENABLE_SKYRIM_AE
		CONE_RUNTIME_DATA_CONTENT
#endif
	private:
		KEEP_FOR_RE()
	};
#ifndef ENABLE_SKYRIM_AE
	static_assert(sizeof(ConeProjectile) == 0x218);
#endif
}
#undef CONE_RUNTIME_DATA_CONTENT
