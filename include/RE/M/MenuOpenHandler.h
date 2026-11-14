#pragma once

#include "RE/M/MenuEventHandler.h"

namespace RE
{
	struct MenuOpenHandler : public MenuEventHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_MenuOpenHandler;
		inline static constexpr auto VTABLE = VTABLE_MenuOpenHandler;

		~MenuOpenHandler() override;  // 00

		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		bool ProcessKinect(KinectEvent* a_event) override;  // 02 (VR 05)
		bool ProcessButton(ButtonEvent* a_event) override;  // 05 (VR 08)
#endif

		// members
		bool          unk10;  // 10
		std::uint8_t  unk11;  // 11
		std::uint16_t unk12;  // 12
		std::uint32_t unk14;  // 14
	};
	static_assert(sizeof(MenuOpenHandler) == 0x18);
}
