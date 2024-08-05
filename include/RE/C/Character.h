#pragma once

#include "RE/A/Actor.h"

namespace RE
{
	class Character : public Actor
	{
	public:
		inline static constexpr auto RTTI = RTTI_Character;
		inline static constexpr auto VTABLE = VTABLE_Character;
		inline static constexpr auto FORMTYPE = FormType::ActorCharacter;

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

		~Character() override;  // 000

		// override (Actor)
		void                                  SaveGame(BGSSaveFormBuffer* a_buf) override;                   // 00E - { Actor::SaveBuffer(a_buf); }
		void                                  LoadGame(BGSLoadFormBuffer* a_buf) override;                   // 00F - { Actor::LoadBuffer(a_buf); }
		void                                  InitLoadGame(BGSLoadFormBuffer* a_buf) override;               // 010 - { Actor::InitLoadGame(a_arg1); }
		void                                  FinishLoadGame(BGSLoadFormBuffer* a_buf) override;             // 011 - { Actor::FinishLoadGame(a_arg1); }
		void                                  Revert(BGSLoadFormBuffer* a_buf) override;                     // 012 - { return; }
		void                                  Predestroy(void) override;                                     // 03B
		[[nodiscard]] bool                    IsChild() const override;                                      // 05E - { return race ? (race->data.flags & Flag::kChild) != Flag::kNone : false; }
		[[nodiscard]] BSFaceGenNiNode*        GetFaceNodeSkinned() override;                                 // 061
		[[nodiscard]] BSFaceGenAnimationData* GetFaceGenAnimationData() override;                            // 063
		void                                  SetBiped(const BSTSmartPointer<BipedAnim>& a_biped) override;  // 081
#ifndef SKYRIM_CROSS_VR
		void  InitiateVampireFeedPackage(Actor* a_arg1, TESObjectREFR* a_arg2) override;  // 0C0
		void  Unk_C4(void) override;                                                      // 0C4 - { unk272 = a_arg1; }
		void  Unk_C5(void) override;                                                      // 0C5 - { return unk272; }
		void  Unk_C6(void) override;                                                      // 0C6 - { return 1; }
		void  OnArmorActorValueChanged() override;                                        // 0CA
		bool  InitiateTresPassPackage(TrespassPackage* a_trespassPackage) override;       // 0D7
		void  SetSize(float a_size) override;                                             // 0D9
		float CalcArmorRating() override;                                                 // 0E6
		float GetArmorBaseFactorSum() override;                                           // 0E7
		float CalcUnarmedDamage() override;                                               // 0E8
		void  PrecacheData(void) override;                                                // 120
#endif

		// add
		virtual void Unk_128(void);  // 128
		virtual void Unk_129(void);  // 129 - { return 1; }
	private:
		KEEP_FOR_RE()
	};
#ifndef ENABLE_SKYRIM_AE
	static_assert(sizeof(Character) == 0x2B0);
#else
	static_assert(sizeof(Character) == 0x78);
#endif
}
