#pragma once

#include "RE/B/BGSLoadGameSubBuffer.h"
#include "RE/B/BSTEvent.h"
#include "RE/M/MagicCaster.h"
#include "RE/R/RefAttachTechniqueInput.h"
#include "RE/S/SimpleAnimationGraphManagerHolder.h"

namespace RE
{
	class BGSArtObject;
	class BGSArtObjectCloneTask;
	class BSLight;
	class ReferenceEffectController;

	struct BSAnimationGraphEvent;

	class ActorMagicCaster :
		public MagicCaster,                         // 00
		public SimpleAnimationGraphManagerHolder,   // 48
		public BSTEventSink<BSAnimationGraphEvent>  // 60
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActorMagicCaster;
		inline static constexpr auto VTABLE = VTABLE_ActorMagicCaster;

		using InterruptHandler_t = void(Actor*);

		enum class Flags
		{
			kNone = 0,
			kDualCasting = 1 << 0,
			kSkipCheckCast = 1 << 1,
			kStartCloneTask = 1 << 2,
			kCastingArtAttached = 1 << 3,
			kCheckDeferredInterrupt = 1 << 4,
			kDeferInterrupt = 1 << 5
		};

		~ActorMagicCaster() override;  // 00

		// override (MagicCaster)
		void                       RequestCastImpl() override;                                                                                                                             // 03
		bool                       StartChargeImpl() override;                                                                                                                             // 04
		void                       StartReadyImpl() override;                                                                                                                              // 05
		void                       StartCastImpl() override;                                                                                                                               // 06
		void                       FinishCastImpl() override;                                                                                                                              // 07 - { return; }
		void                       InterruptCastImpl(bool a_depleteEnergy) override;                                                                                                       // 08 - { return; }
		void                       SpellCast(bool a_doCast, std::uint32_t a_arg2, MagicItem* a_spell) override;                                                                            // 09 - { return; }
		bool                       CheckCast(MagicItem* a_spell, bool a_dualCast, float* a_effectStrength, MagicSystem::CannotCastReason* a_reason, bool a_useBaseValueForCost) override;  // 0A
		TESObjectREFR*             GetCasterStatsObject() const override;                                                                                                                  // 0B - { return actor; }
		Actor*                     GetCasterAsActor() const override;                                                                                                                      // 0C - { return actor; }
		NiNode*                    GetMagicNode() override;                                                                                                                                // 0E - { return magicNode; }
		void                       ClearMagicNode() override;                                                                                                                              // 0F - { magicNode = 0; }
		void                       SetCurrentSpellImpl(MagicItem* a_spell) override;                                                                                                       // 10 - { return; }
		void                       SelectSpellImpl() override;                                                                                                                             // 11 - { return; }
		void                       DeselectSpellImpl() override;                                                                                                                           // 12 - { return; }
		void                       SetSkipCheckCast() override;                                                                                                                            // 13 - { return; }
		void                       SetCastingTimerForCharge() override;                                                                                                                    // 14
		MagicSystem::CastingSource GetCastingSource() const override;                                                                                                                      // 15 - { return castingSource; }
		bool                       GetIsDualCasting() const override;                                                                                                                      // 16 - { return flags & 1; }
		void                       SetDualCasting(bool a_set) override;                                                                                                                    // 17
		void                       SaveGame(BGSSaveGameBuffer* a_buf) override;                                                                                                            // 18
		void                       LoadGame(BGSLoadGameBuffer* a_buf) override;                                                                                                            // 19
		void                       FinishLoadGame(BGSLoadGameBuffer* a_buf) override;                                                                                                      // 1A
		void                       PrepareSound(MagicSystem::SoundID a_sound, MagicItem* a_spell) override;                                                                                // 1B
		void                       AdjustActiveEffect(ActiveEffect* a_activeEffect, float a_power, bool a_arg3) override;                                                                  // 1C

		// add
		virtual void Update(float a_delta);  // 1D

		void CheckAttachCastingArt()
		{
			using func_t = decltype(&ActorMagicCaster::CheckAttachCastingArt);
			static REL::Relocation<func_t> func{ RELOCATION_ID(33403, 34185) };
			return func(this);
		}

		// members
		RefAttachTechniqueInput                castingArtData;               // 64
		NiPointer<BGSArtObjectCloneTask>       cloneTask;                    // B0
		Actor*                                 actor;                        // B8
		NiNode*                                magicNode;                    // C0
		NiPointer<BSLight>                     light;                        // C8
		InterruptHandler_t*                    interruptHandler;             // D0
		BGSLoadGameSubBuffer                   loadGameSubBuffer;            // D8
		BGSArtObject*                          castingArt;                   // E0
		ReferenceEffectController*             weaponEnchantmentController;  // E8
		float                                  costCharged;                  // F0
		MagicSystem::CastingSource             castingSource;                // F4
		stl::enumeration<Flags, std::uint32_t> flags;                        // F8
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ActorMagicCaster) == 0x100);
}
