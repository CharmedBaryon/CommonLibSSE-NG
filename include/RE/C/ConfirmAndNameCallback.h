#pragma once

#include "RE/I/IMessageBoxCallback.h"

namespace RE
{
	class RaceSexMenu;

	class ConfirmAndNameCallback : public IMessageBoxCallback
	{
	public:
		inline constexpr static auto RTTI = RTTI___ConfirmAndNameCallback;
		inline constexpr static auto VTABLE = VTABLE___ConfirmAndNameCallback;

		~ConfirmAndNameCallback() override;  // 00

		// override (IMessageBoxCallback)
		virtual void Run(std::uint8_t a_button) override;

		// members
		RaceSexMenu* menu;  // 10
	};
	static_assert(sizeof(ConfirmAndNameCallback) == 0x18);
}
