#pragma once

#include "RE/I/IMessageBoxCallback.h"

namespace RE
{
	class StatsMenu;

	class LegendarySkillResetConfirmCallback : public RE::IMessageBoxCallback
	{
	public:
		inline static constexpr auto RTTI = RTTI___LegendarySkillResetConfirmCallback;
		inline static constexpr auto VTABLE = VTABLE___LegendarySkillResetConfirmCallback;

		virtual ~LegendarySkillResetConfirmCallback();  // 00

		// override (IMessageBoxCallback)
		void Run(std::uint8_t a_button) override;  // 01

		// members
		StatsMenu*    menu;   // 10
		std::uint8_t  unk18;  // 18
		std::uint8_t  pad19;  // 19
		std::uint16_t pad1A;  // 1A
		ActorValue    skill;  // 1C
	};
	static_assert(sizeof(LegendarySkillResetConfirmCallback) == 0x20);
}
