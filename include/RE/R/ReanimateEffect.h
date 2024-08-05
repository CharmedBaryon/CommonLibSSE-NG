#pragma once

#include "RE/C/CommandEffect.h"

namespace RE
{
	class ReanimateEffect : public CommandEffect
	{
	public:
		inline static constexpr auto RTTI = RTTI_ReanimateEffect;
		inline static constexpr auto VTABLE = VTABLE_ReanimateEffect;

		// override (CommandEffect)
		void Update(float a_delta) override;               // 04
		void SaveGame(BGSSaveFormBuffer* a_buf) override;  // 08
		void LoadGame(BGSLoadFormBuffer* a_buf) override;  // 09
		bool ShouldDispelOnDeath() const override;         // 10 - { return !unk98 && ActiveEffect::ShouldDispelOnDeath(); }

		~ReanimateEffect() override;  // 13

		void Start() override;   // 14
		void Finish() override;  // 15

		// members
		bool          unk98;  // 98
		std::uint8_t  pad99;  // 99
		std::uint16_t pad9A;  // 9A
		std::uint32_t pad9C;  // 9C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ReanimateEffect) == 0xA0);
}
