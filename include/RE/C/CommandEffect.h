#pragma once

#include "RE/A/ActiveEffect.h"

namespace RE
{
	class CommandEffect : public ActiveEffect
	{
	public:
		inline static constexpr auto RTTI = RTTI_CommandEffect;
		inline static constexpr auto VTABLE = VTABLE_CommandEffect;

		// override (ActiveEffect)
		void           OnAdd(MagicTarget* a_target) override;              // 01
		TESObjectREFR* GetVisualsTarget() override;                        // 03
		void           Update(float a_delta) override;                     // 04
		void           LoadGame(BGSSaveFormBuffer* a_buf) override;        // 08
		void           SaveGame(BGSLoadFormBuffer* a_buf) override;        // 09
		void           FinishLoadGame(BGSLoadFormBuffer* a_buf) override;  // 0A
		void           ClearTargetImpl() override;                         // 12

		~CommandEffect() override;  // 13

		void Start() override;   // 14
		void Finish() override;  // 15

		// members
		ActorHandle   commandedActor;  // 90
		std::uint32_t pad94;           // 94
	};
	static_assert(sizeof(CommandEffect) == 0x98);
}
