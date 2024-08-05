#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSSoundHandle.h"
#include "RE/F/FormTypes.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/T/TESObjectREFR.h"

namespace RE
{
	class BGSHazard;
	class NiLight;

	class Hazard : public TESObjectREFR
	{
	public:
		inline static constexpr auto RTTI = RTTI_Hazard;
		inline static constexpr auto VTABLE = VTABLE_Hazard;
		inline static constexpr auto FORMTYPE = FormType::PlacedHazard;

		enum class Flags
		{
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
			};
		};

		~Hazard() override;  // 00

		// override (TESObjectREFR)
		void SaveGame(BGSSaveFormBuffer* a_buf) override;        // 0E
		void LoadGame(BGSLoadFormBuffer* a_buf) override;        // 0F
		void FinishLoadGame(BGSLoadFormBuffer* a_buf) override;  // 11
		void Revert(BGSLoadFormBuffer* a_buf) override;          // 12
		void InitItemImpl() override;                            // 13
		void SetActorCause(ActorCause* a_cause) override;        // 50
		void Release3DRelatedData() override;                    // 6B
#ifndef SKYRIM_CROSS_VR
		// Override functions past where Skyrim VR breaks compatibility.
		bool OnAddCellPerformQueueReference(TESObjectCELL& a_cell) const override;  // 90 - { return false; }
#endif

		// add
		SKYRIM_REL_VR_VIRTUAL void Initialize();         // A2
		SKYRIM_REL_VR_VIRTUAL void Unk_A3(void);         // A3 - { return; }
		SKYRIM_REL_VR_VIRTUAL bool IsPermanent() const;  // A4 - { return TESDataHandler::GetSingleton()->IsGeneratedFormID(formID) == 0; }

		struct HAZARD_RUNTIME_DATA
		{
#define HAZARD_RUNTIME_DATA_CONTENT                                     \
	void*                                  hazardDBHandle; /* 98, A0 */ \
	ActorHandle                            ownerActor;     /* A0 */     \
	float                                  age;            /* A4 */     \
	float                                  lifetime;       /* A8 */     \
	float                                  targetTimer;    /* AC */     \
	float                                  radius;         /* B0 */     \
	float                                  magnitude;      /* B4 */     \
	BGSHazard*                             hazard;         /* B8 */     \
	NiPointer<NiLight>                     light;          /* C0 */     \
	BSSoundHandle                          sound;          /* C8 */     \
	stl::enumeration<Flags, std::uint32_t> flags;          /* D4 */

			HAZARD_RUNTIME_DATA_CONTENT
		};

		[[nodiscard]] inline HAZARD_RUNTIME_DATA& GetHazardRuntimeData() noexcept
		{
			return REL::RelocateMemberIfNewer<HAZARD_RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x98, 0xA0);
		}

		[[nodiscard]] inline const HAZARD_RUNTIME_DATA& GetHazardRuntimeData() const noexcept
		{
			return REL::RelocateMemberIfNewer<HAZARD_RUNTIME_DATA>(SKSE::RUNTIME_SSE_1_6_629, this, 0x98, 0xA0);
		}

		// members
#ifndef ENABLE_SKYRIM_AE
		HAZARD_RUNTIME_DATA_CONTENT;
#endif
	private:
		KEEP_FOR_RE()
	};
#ifndef ENABLE_SKYRIM_AE
static_assert(sizeof(Hazard) == 0xD8);
#endif
}
#undef HAZARD_RUNTIME_DATA_CONTENT
