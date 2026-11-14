#pragma once

#include "RE/I/IMessageBoxCallback.h"

namespace RE
{
	class RaceSexMenu;

	class ConfirmCloseRaceSexMenuCallback : public IMessageBoxCallback
	{
	public:
		inline constexpr static auto RTTI = RTTI___ConfirmCloseRaceSexMenuCallback;
		inline constexpr static auto VTABLE = VTABLE___ConfirmCloseRaceSexMenuCallback;

		~ConfirmCloseRaceSexMenuCallback() override;  // 00

		// override (IMessageBoxCallback)
		virtual void Run(std::uint8_t a_button) override;

		// members
		RaceSexMenu* menu;  // 10
	};
	static_assert(sizeof(ConfirmCloseRaceSexMenuCallback) == 0x18);
}
