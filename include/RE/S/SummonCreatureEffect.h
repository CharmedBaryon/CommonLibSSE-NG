#pragma once

#include "RE/A/ActiveEffect.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class SummonPlacementEffect;

	class SummonCreatureEffect : public ActiveEffect
	{
	public:
		inline static constexpr auto RTTI = RTTI_SummonCreatureEffect;
		inline static constexpr auto VTABLE = VTABLE_SummonCreatureEffect;

		// override (ActiveEffect)
		void Update(float a_delta) override;                          // 04
		void SetLocation(const NiPoint3& a_location) override;        // 07 - { location = a_location; }
		void SaveGame(BGSSaveFormBuffer* a_buf) override;             // 08
		void LoadGame(BGSLoadFormBuffer* a_buf) override;             // 09
		void FinishLoadGame(BGSLoadFormBuffer* a_buf) override;       // 0A
		void HandleEvent(const BSFixedString& a_eventName) override;  // 0D
		void ClearTargetImpl() override;                              // 12

		~SummonCreatureEffect() override;  // 13

		void Start() override;   // 14
		void Finish() override;  // 15

		// members
		NiPoint3               location;               // 90
		NiPoint3               rotation;               // 9C
		ActorHandle            commandedActor;         // A8
		std::uint32_t          unkAC;                  // AC
		SummonPlacementEffect* summonPlacementEffect;  // B0
		bool                   unkB8;                  // B8
		bool                   unkB9;                  // B9
		std::uint16_t          padBA;                  // BA
		std::uint32_t          padBC;                  // BC
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(SummonCreatureEffect) == 0xC0);
}
