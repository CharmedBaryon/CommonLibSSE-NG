#include "RE/I/InputEvent.h"

#include "RE/B/ButtonEvent.h"
#include "RE/C/CharEvent.h"
#include "RE/I/IDEvent.h"
#include "RE/M/MouseMoveEvent.h"

namespace RE
{
	ButtonEvent* InputEvent::AsButtonEvent()
	{
		return GetEventType() == INPUT_EVENT_TYPE::kButton ? static_cast<ButtonEvent*>(this) : nullptr;
	}

	const ButtonEvent* InputEvent::AsButtonEvent() const
	{
		return GetEventType() == INPUT_EVENT_TYPE::kButton ? static_cast<const ButtonEvent*>(this) : nullptr;
	}

	CharEvent* InputEvent::AsCharEvent()
	{
		return GetEventType() == INPUT_EVENT_TYPE::kChar ? static_cast<CharEvent*>(this) : nullptr;
	}

	const CharEvent* InputEvent::AsCharEvent() const
	{
		return GetEventType() == INPUT_EVENT_TYPE::kChar ? static_cast<const CharEvent*>(this) : nullptr;
	}

	IDEvent* InputEvent::AsIDEvent()
	{
		return HasIDCode() ? static_cast<IDEvent*>(this) : nullptr;
	}

	const IDEvent* InputEvent::AsIDEvent() const
	{
		return HasIDCode() ? static_cast<const IDEvent*>(this) : nullptr;
	}

	MouseMoveEvent* InputEvent::AsMouseMoveEvent()
	{
		return GetEventType() == INPUT_EVENT_TYPE::kMouseMove ? static_cast<MouseMoveEvent*>(this) : nullptr;
	}

	const MouseMoveEvent* InputEvent::AsMouseMoveEvent() const
	{
		return GetEventType() == INPUT_EVENT_TYPE::kMouseMove ? static_cast<const MouseMoveEvent*>(this) : nullptr;
	}
}
