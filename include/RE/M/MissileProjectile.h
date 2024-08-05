#pragma once

#include "RE/F/FormTypes.h"
#include "RE/I/ImpactResults.h"
#include "RE/P/Projectile.h"

namespace RE
{
	class MissileProjectile : public Projectile
	{
	public:
		inline static constexpr auto RTTI = RTTI_MissileProjectile;
		inline static constexpr auto VTABLE = VTABLE_MissileProjectile;
		inline static constexpr auto FORMTYPE = FormType::ProjectileMissile;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
			};
		};

		~MissileProjectile() override;  // 00

		// override (Projectile)
		void SaveGame(BGSSaveFormBuffer* a_buf) override;        // 0E
		void LoadGame(BGSLoadFormBuffer* a_buf) override;        // 0F
		void InitLoadGame(BGSLoadFormBuffer* a_buf) override;    // 10
		void FinishLoadGame(BGSLoadFormBuffer* a_buf) override;  // 11
		void Revert(BGSLoadFormBuffer* a_buf) override;          // 12
#ifndef SKYRIM_CROSS_VR
		bool IsMissileProjectile() override;                                                                                                                                             // A2 - { return 1; }
		void Process3D() override;                                                                                                                                                       // A9
		void UpdateImpl(float a_delta) override;                                                                                                                                         // AB
		bool ProcessImpacts() override;                                                                                                                                                  // AC
		bool GetKillOnCollision() override;                                                                                                                                              // B8 - { return unk1D8 == 1; }
		void AddImpact(TESObjectREFR* a_ref, const NiPoint3& a_targetLoc, const NiPoint3& a_velocity, hkpCollidable* a_collidable, std::int32_t a_arg6, std::uint32_t a_arg7) override;  // BD
		void Handle3DLoaded() override;                                                                                                                                                  // C0
#endif

		// add
		SKYRIM_REL_VR_VIRTUAL void Unk_C2(void);  // C2 - { return 0; }
		SKYRIM_REL_VR_VIRTUAL void Unk_C3(void);  // C3 - { return 0; }

		struct MISSILE_RUNTIME_DATA
		{
#define MISSILE_RUNTIME_DATA_CONTENT                    \
	ImpactResult  impactResult;          /* 1D8, 1E0 */ \
	bool          waitingToInitialize3D; /* 1DC */      \
	std::uint8_t  unk1DD;                /* 1DD */      \
	std::uint16_t unk1DE;                /* 1DE */

			MISSILE_RUNTIME_DATA_CONTENT
		};

		[[nodiscard]] inline MISSILE_RUNTIME_DATA& GetMissileRuntimeData() noexcept
		{
			return REL::RelocateMemberIfNewer<MISSILE_RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x1D8, 0x1E0);
		}

		[[nodiscard]] inline const MISSILE_RUNTIME_DATA& GetMissileRuntimeData() const noexcept
		{
			return REL::RelocateMemberIfNewer<MISSILE_RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x1D8, 0x1E0);
		}

		// members
#ifndef ENABLE_SKYRIM_AE
		MISSILE_RUNTIME_DATA_CONTENT;
#endif
	private:
		KEEP_FOR_RE()
	};
#ifndef ENABLE_SKYRIM_AE
	static_assert(sizeof(MissileProjectile) == 0x1E0);
#endif
}
#undef MISSILE_RUNTIME_DATA_CONTENT
