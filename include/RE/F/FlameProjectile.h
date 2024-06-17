#pragma once

#include "RE/F/FormTypes.h"
#include "RE/P/Projectile.h"

namespace RE
{
	class FlameProjectile : public Projectile
	{
	public:
		inline static constexpr auto RTTI = RTTI_FlameProjectile;
		inline static constexpr auto VTABLE = VTABLE_FlameProjectile;
		inline static constexpr auto FORMTYPE = FormType::ProjectileFlame;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
			};
		};

		~FlameProjectile() override;  // 00

		// override (Projectile)
		void SaveGame(BGSSaveFormBuffer* a_buf) override;        // 0E
		void LoadGame(BGSLoadFormBuffer* a_buf) override;        // 0F
		void InitLoadGame(BGSLoadFormBuffer* a_buf) override;    // 10
		void FinishLoadGame(BGSLoadFormBuffer* a_buf) override;  // 11
		void Revert(BGSLoadFormBuffer* a_buf) override;          // 12
#ifndef SKYRIM_CROSS_VR
		bool IsFlameProjectile() override;                                                                                                                                               // A4 - { return 1; }
		void Process3D() override;                                                                                                                                                       // A9
		void UpdateImpl(float a_delta) override;                                                                                                                                         // AB
		bool RunTargetPick() override;                                                                                                                                                   // B7
		void AddImpact(TESObjectREFR* a_ref, const NiPoint3& a_targetLoc, const NiPoint3& a_velocity, hkpCollidable* a_collidable, std::int32_t a_arg6, std::uint32_t a_arg7) override;  // BD
		void Handle3DLoaded() override;                                                                                                                                                  // C0 - { flags = flags & 0xFFFFFFCC | 8; }
		bool ShouldUseDesiredTarget() override;                                                                                                                                          // C1
#endif

		struct FLAME_RUNTIME_DATA
		{
#define FLAME_RUNTIME_DATA_CONTENT   \
	float expirationTimer; /* 1D8 */ \
	float coneAngle;       /* 1DC */

			FLAME_RUNTIME_DATA_CONTENT
		};

		[[nodiscard]] inline FLAME_RUNTIME_DATA& GetFlameRuntimeData() noexcept
		{
			return REL::RelocateMemberIfNewer<FLAME_RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x1D8, 0x1E0);
		}

		[[nodiscard]] inline const FLAME_RUNTIME_DATA& GetFlameRuntimeData() const noexcept
		{
			return REL::RelocateMemberIfNewer<FLAME_RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x1D8, 0x1E0);
		}

		// members
#ifndef ENABLE_SKYRIM_AE
		FLAME_RUNTIME_DATA_CONTENT;
#endif
	private:
		KEEP_FOR_RE()
	};
#ifndef ENABLE_SKYRIM_AE
static_assert(sizeof(FlameProjectile) == 0x1E0);
#endif
}
#undef FLAME_RUNTIME_DATA_CONTENT
