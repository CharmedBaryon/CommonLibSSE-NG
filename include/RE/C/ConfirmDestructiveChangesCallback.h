#pragma once

#include "RE/I/IMessageBoxCallback.h"

namespace RE
{
	class RaceSexMenu;

	class ConfirmDestructiveChangesCallback : public IMessageBoxCallback
	{
	public:
		inline constexpr static auto RTTI = RTTI___ConfirmDestructiveChangesCallback;
		inline constexpr static auto VTABLE = VTABLE___ConfirmDestructiveChangesCallback;

		~ConfirmDestructiveChangesCallback() override;  // 00

		// override (IMessageBoxCallback)
		virtual void Run(std::uint8_t a_button) override;

		// members
		RaceSexMenu*  menu;   // 10
		std::uint32_t unk14;  // 18
		std::uint32_t unk18;  // 1C
	};
	static_assert(sizeof(ConfirmDestructiveChangesCallback) == 0x20);
}
