#pragma once

#include "RE/I/IMessageBoxCallback.h"

namespace RE
{
	class MagicMenu;

	class SpendSoulCallback : public IMessageBoxCallback
	{
	public:
		inline static constexpr auto RTTI = RTTI___SpendSoulCallback;
		inline static constexpr auto VTABLE = VTABLE___SpendSoulCallback;

		~SpendSoulCallback() override;  // 00

		// override (IMessageBoxCallback)
		void Run(std::uint8_t a_button) override;  //01

		// members
		MagicMenu* magicMenu;  // 10
	};
	static_assert(sizeof(SpendSoulCallback) == 0x18);
}
