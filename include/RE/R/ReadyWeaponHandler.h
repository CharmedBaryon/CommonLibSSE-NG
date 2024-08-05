#pragma once

#include "RE/P/PlayerInputHandler.h"

namespace RE
{
	struct ReadyWeaponHandler : public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_ReadyWeaponHandler;
		inline static constexpr auto VTABLE = VTABLE_ReadyWeaponHandler;

		~ReadyWeaponHandler() override;  // 00

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;                                  // 01
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data) override;  // 04
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(ReadyWeaponHandler) == 0x10);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(ReadyWeaponHandler) == 0x28);
#endif
}
