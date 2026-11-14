#pragma once

#include "RE/A/ActorValues.h"
#include "RE/I/IMessageBoxCallback.h"

namespace RE
{
	class LevelUpMenu;

	class ConfirmLevelUpAttributeCallback : public IMessageBoxCallback
	{
	public:
		inline static constexpr auto RTTI = RTTI___ConfirmLevelUpAttributeCallback;
		inline static constexpr auto VTABLE = VTABLE___ConfirmLevelUpAttributeCallback;

		~ConfirmLevelUpAttributeCallback() override;  // 00

		// override (IMessageBoxCallback)
		void Run(std::uint8_t a_button) override;  //01

		// members
		LevelUpMenu* levelUpMenu;  // 10
		ActorValue   actorValue;   // 18
	};
	static_assert(sizeof(ConfirmLevelUpAttributeCallback) == 0x20);
}
