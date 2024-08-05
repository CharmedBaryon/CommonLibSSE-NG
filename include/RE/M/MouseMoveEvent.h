#pragma once

#include "RE/I/IDEvent.h"

namespace RE
{
	class MouseMoveEvent : public IDEvent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MouseMoveEvent;
		inline static constexpr auto VTABLE = VTABLE_MouseMoveEvent;

		~MouseMoveEvent() override;  // 00

		void Init(std::int32_t a_mouseInputX, std::int32_t a_mouseInputY)
		{
			mouseInputX = a_mouseInputX;
			mouseInputY = a_mouseInputY;
		}

		void Init(std::int32_t a_mouseInputX, std::int32_t a_mouseInputY, const BSFixedString& a_userEvent)
		{
			mouseInputX = a_mouseInputX;
			mouseInputY = a_mouseInputY;
			userEvent = a_userEvent;
		}

		// members
		std::int32_t mouseInputX;  // 28
		std::int32_t mouseInputY;  // 2C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(MouseMoveEvent) == 0x30);
}
