#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/I/InputDevices.h"

namespace RE
{
	enum class INPUT_EVENT_TYPE
	{
		kButton = 0,
		kMouseMove,
		kChar,
		kThumbstick,
		kDeviceConnect,
		kKinect,
		// VR only (SkyrimVR): the VR runtime emits two extra wand-touchpad event types.
		kVrTouchpadPosition,  // 6 - VrWandTouchpadPositionEvent
		kVrTouchpadSwipe,     // 7 - VrWandTouchpadSwipeEvent
#ifdef ENABLE_SKYRIM_AE
		// Duplicate values vs. the VR pair above are intentional: no build constructs both kinds.
		kSixaxis = 6,        // 6 - SixaxisEvent
		kMotionGesture = 7,  // 7 - MotionGestureEvent
		kAmiibo = 8          // 8 - AmiiboEvent
#endif
	};

	class ButtonEvent;
	class CharEvent;
	class IDEvent;
	class MouseMoveEvent;
#ifdef ENABLE_SKYRIM_AE
	class AmiiboEvent;
	class MotionGestureEvent;
	class SixaxisEvent;
#endif
	class ThumbstickEvent;

	class InputEvent
	{
	public:
		inline static constexpr auto RTTI = RTTI_InputEvent;
		inline static constexpr auto VTABLE = VTABLE_InputEvent;

		virtual ~InputEvent();  // 00

		[[nodiscard]] virtual bool                 HasIDCode() const;   // 01 - { return false; }
		[[nodiscard]] virtual const BSFixedString& QUserEvent() const;  // 02 - { return ""; }

		[[nodiscard]] constexpr INPUT_EVENT_TYPE GetEventType() const noexcept { return *eventType; }
		[[nodiscard]] constexpr INPUT_DEVICE     GetDevice() const noexcept { return *device; }

		[[nodiscard]] ButtonEvent*       AsButtonEvent();
		[[nodiscard]] const ButtonEvent* AsButtonEvent() const;

		[[nodiscard]] CharEvent*       AsCharEvent();
		[[nodiscard]] const CharEvent* AsCharEvent() const;

		[[nodiscard]] IDEvent*       AsIDEvent();
		[[nodiscard]] const IDEvent* AsIDEvent() const;

		[[nodiscard]] MouseMoveEvent*       AsMouseMoveEvent();
		[[nodiscard]] const MouseMoveEvent* AsMouseMoveEvent() const;

#ifdef ENABLE_SKYRIM_AE
		[[nodiscard]] AmiiboEvent*       AsAmiiboEvent();
		[[nodiscard]] const AmiiboEvent* AsAmiiboEvent() const;

		[[nodiscard]] MotionGestureEvent*       AsMotionGestureEvent();
		[[nodiscard]] const MotionGestureEvent* AsMotionGestureEvent() const;

		[[nodiscard]] SixaxisEvent*       AsSixaxisEvent();
		[[nodiscard]] const SixaxisEvent* AsSixaxisEvent() const;
#endif

		[[nodiscard]] ThumbstickEvent*       AsThumbstickEvent();
		[[nodiscard]] const ThumbstickEvent* AsThumbstickEvent() const;

		// members
		REX::EnumSet<INPUT_DEVICE, std::uint32_t>     device;     // 08
		REX::EnumSet<INPUT_EVENT_TYPE, std::uint32_t> eventType;  // 0C
		InputEvent*                                   next;       // 10
	};
	static_assert(sizeof(InputEvent) == 0x18);
}
