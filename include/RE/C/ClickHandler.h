#pragma once

#include "RE/M/MenuEventHandler.h"

namespace RE
{
	struct ClickHandler : public MenuEventHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_ClickHandler;
		inline static constexpr auto VTABLE = VTABLE_ClickHandler;

		~ClickHandler() override;

		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		bool ProcessButton(ButtonEvent* a_event) override;  // 05 (VR 08)
#endif
	};
	static_assert(sizeof(ClickHandler) == 0x10);
}
