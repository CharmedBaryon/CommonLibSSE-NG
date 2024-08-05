#include "RE/B/BSInputEventQueue.h"

namespace RE
{
	BSInputEventQueue* BSInputEventQueue::GetSingleton()
	{
		REL::Relocation<BSInputEventQueue**> singleton{ RELOCATION_ID(520856, 407374) };
		return *singleton;
	}

	void BSInputEventQueue::AddButtonEvent(INPUT_DEVICE a_device, std::int32_t a_id, float a_value, float a_duration)
	{
		if (buttonEventCount < MAX_BUTTON_EVENTS) {
			auto& cachedEvent = GetRuntimeData().buttonEvents[buttonEventCount];
			cachedEvent.GetRuntimeData().value = a_value;
			cachedEvent.GetRuntimeData().heldDownSecs = a_duration;
			cachedEvent.device = a_device;
			cachedEvent.idCode = a_id;
			cachedEvent.userEvent = {};
			cachedEvent.AsVRWandEvent()->unkVR28 = -1;
			PushOntoInputQueue(&cachedEvent);
			++buttonEventCount;
		}
	}

	void BSInputEventQueue::AddCharEvent(std::uint32_t a_keyCode)
	{
		if (charEventCount < MAX_CHAR_EVENTS) {
			auto& cachedEvent = GetRuntimeData().charEvents[charEventCount];
			cachedEvent.keyCode = a_keyCode;

			PushOntoInputQueue(&cachedEvent);
			++charEventCount;
		}
	}

	void BSInputEventQueue::AddMouseMoveEvent(std::int32_t a_mouseInputX, std::int32_t a_mouseInputY)
	{
		if (mouseEventCount < MAX_MOUSE_EVENTS) {
			auto& cachedEvent = GetRuntimeData().mouseEvents[mouseEventCount];
			cachedEvent.mouseInputX = a_mouseInputX;
			cachedEvent.mouseInputY = a_mouseInputY;
			cachedEvent.userEvent = {};

			PushOntoInputQueue(&cachedEvent);
			++mouseEventCount;
		}
	}

	void BSInputEventQueue::AddThumbstickEvent(ThumbstickEvent::InputType a_id, float a_xValue, float a_yValue)
	{
		if (thumbstickEventCount < MAX_THUMBSTICK_EVENTS) {
			auto& cachedEvent = GetRuntimeData().thumbstickEvents[thumbstickEventCount];
			cachedEvent.xValue = a_xValue;
			cachedEvent.yValue = a_yValue;
			cachedEvent.device = INPUT_DEVICE::kGamepad;
			cachedEvent.idCode = a_id;
			cachedEvent.userEvent = {};

			PushOntoInputQueue(&cachedEvent);
			++thumbstickEventCount;
		}
	}

	void BSInputEventQueue::AddConnectEvent(INPUT_DEVICE a_device, bool a_connected)
	{
		if (connectEventCount < MAX_CONNECT_EVENTS) {
			auto& cachedEvent = GetRuntimeData().connectEvents[connectEventCount];
			cachedEvent.device = a_device;
			cachedEvent.connected = a_connected;

			PushOntoInputQueue(&cachedEvent);
			++connectEventCount;
		}
	}

	void BSInputEventQueue::AddKinectEvent(const BSFixedString& a_userEvent, const BSFixedString& a_heard)
	{
		if (kinectEventCount < MAX_KINECT_EVENTS) {
			auto& cachedEvent = GetRuntimeData().kinectEvents[kinectEventCount];
			cachedEvent.userEvent = a_userEvent;
			cachedEvent.heard = a_heard;

			PushOntoInputQueue(&cachedEvent);
			++kinectEventCount;
		}
	}

	void BSInputEventQueue::AddButtonEvent(INPUT_DEVICE a_device, std::int32_t a_arg2, std::int32_t a_id, float a_value, float a_duration)
	{
		if SKYRIM_REL_CONSTEXPR (REL::Module::IsVR()) {
			if (buttonEventCount < MAX_BUTTON_EVENTS) {
				auto& cachedEvent = GetRuntimeData().buttonEvents[buttonEventCount];
				cachedEvent.GetRuntimeData().value = a_value;
				cachedEvent.GetRuntimeData().heldDownSecs = a_duration;
				cachedEvent.device = a_device;
				cachedEvent.idCode = a_id;
				cachedEvent.userEvent = {};
				cachedEvent.AsVRWandEvent()->unkVR28 = a_arg2;
				PushOntoInputQueue(&cachedEvent);
				++buttonEventCount;
			}
		}
	}

	void BSInputEventQueue::AddThumbstickEvent(ThumbstickEvent::InputType a_id, INPUT_DEVICE a_device, float a_xValue, float a_yValue)
	{
		if SKYRIM_REL_CONSTEXPR (REL::Module::IsVR()) {
			if (thumbstickEventCount < MAX_THUMBSTICK_EVENTS) {
				auto& cachedEvent = GetRuntimeData().thumbstickEvents[thumbstickEventCount];
				cachedEvent.xValue = a_xValue;
				cachedEvent.yValue = a_yValue;
				cachedEvent.device = a_device;
				cachedEvent.idCode = a_id;
				cachedEvent.userEvent = {};

				PushOntoInputQueue(&cachedEvent);
				++thumbstickEventCount;
			}
		}
	}

	void BSInputEventQueue::PushOntoInputQueue(InputEvent* a_event)
	{
		if (!GetRuntimeData().queueHead) {
			GetRuntimeData().queueHead = a_event;
		}

		if (GetRuntimeData().queueTail) {
			GetRuntimeData().queueTail->next = a_event;
		}

		GetRuntimeData().queueTail = a_event;
		GetRuntimeData().queueTail->next = nullptr;
	}

	void BSInputEventQueue::ClearInputQueue()
	{
		kinectEventCount = 0;
		connectEventCount = 0;
		thumbstickEventCount = 0;
		mouseEventCount = 0;
		charEventCount = 0;
		buttonEventCount = 0;
		GetRuntimeData().queueTail = nullptr;
		GetRuntimeData().queueHead = nullptr;
	}
}
