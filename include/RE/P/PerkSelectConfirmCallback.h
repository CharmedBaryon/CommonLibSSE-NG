#pragma once

#include "RE/I/IMessageBoxCallback.h"

namespace RE
{
	class StatsMenu;

	class PerkSelectConfirmCallback : public RE::IMessageBoxCallback
	{
	public:
		inline static constexpr auto RTTI = RTTI___PerkSelectConfirmCallback;
		inline static constexpr auto VTABLE = VTABLE___PerkSelectConfirmCallback;

		virtual ~PerkSelectConfirmCallback();  // 00

		// override (IMessageBoxCallback)
		void Run(std::uint8_t a_button) override;  // 01

		// members
		StatsMenu* menu;  // 10
	};
	static_assert(sizeof(PerkSelectConfirmCallback) == 0x18);
}
