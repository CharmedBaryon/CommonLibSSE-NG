#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/V/ValueModifierEffect.h"

namespace RE
{
	class GrabActorEffect : public ValueModifierEffect
	{
	public:
		inline static constexpr auto RTTI = RTTI_GrabActorEffect;
		inline static constexpr auto VTABLE = VTABLE_GrabActorEffect;

		// override (ValueModifierEffect)
		void Update(float a_delta) override;               // 04
		void SaveGame(BGSSaveFormBuffer* a_buf) override;  // 08

		~GrabActorEffect() override;  // 13

		void Start() override;                                                                   // 14
		void Finish() override;                                                                  // 15
		void ModifyActorValue(Actor* a_actor, float a_value, ActorValue a_actorValue) override;  // 20

		// members
		void*         unk98;         // 98 - smart ptr
		ActorHandle   grabbedActor;  // A0
		std::uint32_t unkA4;         // A4
		bool          unkA8;         // A8
		bool          grabbed;       // A9
		std::uint16_t unkAA;         // AA
		std::uint32_t unkAC;         // AC
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GrabActorEffect) == 0xB0);
}
