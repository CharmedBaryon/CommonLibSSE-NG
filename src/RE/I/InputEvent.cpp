#include "RE/I/InputEvent.h"

#include "RE/B/ButtonEvent.h"
#include "RE/C/CharEvent.h"
#include "RE/I/IDEvent.h"
#include "RE/M/MouseMoveEvent.h"
#include "RE/T/ThumbstickEvent.h"
#ifdef ENABLE_SKYRIM_AE
#	include "RE/A/AmiiboEvent.h"
#	include "RE/M/MotionGestureEvent.h"
#	include "RE/S/SixaxisEvent.h"
#	include "REL/Module.h"
#	include "SKSE/Version.h"
#endif

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

#ifdef ENABLE_SKYRIM_AE
	AmiiboEvent* InputEvent::AsAmiiboEvent()
	{
		return REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99) && GetEventType() == INPUT_EVENT_TYPE::kAmiibo ? static_cast<AmiiboEvent*>(this) : nullptr;
	}

	const AmiiboEvent* InputEvent::AsAmiiboEvent() const
	{
		return const_cast<InputEvent*>(this)->AsAmiiboEvent();
	}

	MotionGestureEvent* InputEvent::AsMotionGestureEvent()
	{
		return REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99) && GetEventType() == INPUT_EVENT_TYPE::kMotionGesture ? static_cast<MotionGestureEvent*>(this) : nullptr;
	}

	const MotionGestureEvent* InputEvent::AsMotionGestureEvent() const
	{
		return const_cast<InputEvent*>(this)->AsMotionGestureEvent();
	}

	SixaxisEvent* InputEvent::AsSixaxisEvent()
	{
		return REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99) && GetEventType() == INPUT_EVENT_TYPE::kSixaxis ? static_cast<SixaxisEvent*>(this) : nullptr;
	}

	const SixaxisEvent* InputEvent::AsSixaxisEvent() const
	{
		return const_cast<InputEvent*>(this)->AsSixaxisEvent();
	}
#endif

	ThumbstickEvent* InputEvent::AsThumbstickEvent()
	{
		return GetEventType() == INPUT_EVENT_TYPE::kThumbstick ? static_cast<ThumbstickEvent*>(this) : nullptr;
	}

	const ThumbstickEvent* InputEvent::AsThumbstickEvent() const
	{
		return GetEventType() == INPUT_EVENT_TYPE::kThumbstick ? static_cast<const ThumbstickEvent*>(this) : nullptr;
	}
}
