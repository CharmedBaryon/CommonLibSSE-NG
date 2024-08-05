#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/E/ExtraMagicCaster.h"

namespace RE
{
	class TESObjectREFR;

	class NonActorMagicCaster : public ExtraMagicCaster
	{
	public:
		inline static constexpr auto RTTI = RTTI_NonActorMagicCaster;
		inline static constexpr auto VTABLE = VTABLE_NonActorMagicCaster;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kMagicCaster;

		~NonActorMagicCaster() override;  // 00

		// override (MagicCaster)
		void           CastSpellImmediate(MagicItem* a_spell, bool a_noHitEffectArt, TESObjectREFR* a_target, float a_effectiveness, bool a_hostileEffectivenessOnly, float a_magnitudeOverride, Actor* a_blameActor) override;  // 01
		void           FinishCastImpl() override;                                                                                                                                                                                // 07 - { return; }
		TESObjectREFR* GetCasterStatsObject() const override;                                                                                                                                                                    // 0B - { return 0; }
		Actor*         GetCasterAsActor() const override;                                                                                                                                                                        // 0C - { return 0; }
		TESObjectREFR* GetCasterObjectReference(Actor** a_outCaster) const override;                                                                                                                                             // 0D
		NiNode*        GetMagicNode() override;                                                                                                                                                                                  // 0E - { return 0; }
		void           SaveGame(BGSSaveGameBuffer* a_buf) override;                                                                                                                                                              // 18
		void           LoadGame(BGSLoadGameBuffer* a_buf) override;                                                                                                                                                              // 19

		// members
		TESObjectREFR* unk58;       // 58
		ActorHandle    blameActor;  // 60
		std::uint32_t  unk64;       // 64
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(NonActorMagicCaster) == 0x68);
}
