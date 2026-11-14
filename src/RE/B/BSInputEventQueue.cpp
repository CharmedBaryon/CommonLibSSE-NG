#include "RE/B/BSInputEventQueue.h"

namespace RE
{
	BSInputEventQueue* BSInputEventQueue::GetSingleton()
	{
		static REL::Relocation<BSInputEventQueue**> singleton{ RELOCATION_ID(520856, 407374) };
		return *singleton;
	}

	template <>
	ButtonEvent* BSInputEventQueue::GetCachedEvent<ButtonEvent>()
	{
		if (buttonEventCount < MAX_BUTTON_EVENTS) {
			return CachedEventAt<ButtonEvent>(kButtonEventArray, buttonEventCount);
		}

		return nullptr;
	}

	template <>
	CharEvent* BSInputEventQueue::GetCachedEvent<CharEvent>()
	{
		if (charEventCount < MAX_CHAR_EVENTS) {
			return CachedEventAt<CharEvent>(kCharEventArray, charEventCount);
		}

		return nullptr;
	}

	template <>
	MouseMoveEvent* BSInputEventQueue::GetCachedEvent<MouseMoveEvent>()
	{
		if (mouseEventCount < MAX_MOUSE_EVENTS) {
			return CachedEventAt<MouseMoveEvent>(kMouseEventArray, mouseEventCount);
		}

		return nullptr;
	}

	template <>
	ThumbstickEvent* BSInputEventQueue::GetCachedEvent<ThumbstickEvent>()
	{
		if (thumbstickEventCount < MAX_THUMBSTICK_EVENTS) {
			return CachedEventAt<ThumbstickEvent>(kThumbstickEventArray, thumbstickEventCount);
		}

		return nullptr;
	}

	template <>
	DeviceConnectEvent* BSInputEventQueue::GetCachedEvent<DeviceConnectEvent>()
	{
		if (connectEventCount < MAX_CONNECT_EVENTS) {
			return CachedEventAt<DeviceConnectEvent>(kConnectEventArray, connectEventCount);
		}

		return nullptr;
	}

	template <>
	KinectEvent* BSInputEventQueue::GetCachedEvent<KinectEvent>()
	{
		if (kinectEventCount < MAX_KINECT_EVENTS) {
			return CachedEventAt<KinectEvent>(kKinectEventArray, kinectEventCount);
		}

		return nullptr;
	}

	template <>
	void BSInputEventQueue::AdvanceCount<ButtonEvent>()
	{
		++buttonEventCount;
	}

	template <>
	void BSInputEventQueue::AdvanceCount<CharEvent>()
	{
		++charEventCount;
	}

	template <>
	void BSInputEventQueue::AdvanceCount<MouseMoveEvent>()
	{
		++mouseEventCount;
	}

	template <>
	void BSInputEventQueue::AdvanceCount<ThumbstickEvent>()
	{
		++thumbstickEventCount;
	}

	template <>
	void BSInputEventQueue::AdvanceCount<DeviceConnectEvent>()
	{
		++connectEventCount;
	}

	template <>
	void BSInputEventQueue::AdvanceCount<KinectEvent>()
	{
		++kinectEventCount;
	}

#ifdef ENABLE_SKYRIM_VR
	void BSInputEventQueue::AddButtonEvent(INPUT_DEVICE a_device, std::int32_t a_arg2, std::int32_t a_id, float a_value, float a_duration, const BSFixedString& a_userEvent)
	{
		if SKYRIM_REL_CONSTEXPR (REL::Module::IsVR()) {
			AddEvent<ButtonEvent>(a_device, a_arg2, a_id, a_value, a_duration, a_userEvent);
		}
	}

	void BSInputEventQueue::AddThumbstickEvent(ThumbstickEvent::InputType a_id, INPUT_DEVICE a_device, float a_xValue, float a_yValue)
	{
		if SKYRIM_REL_CONSTEXPR (REL::Module::IsVR()) {
			AddEvent<ThumbstickEvent>(a_id, a_device, a_xValue, a_yValue);
		}
	}
#endif

	void BSInputEventQueue::PushOntoInputQueue(InputEvent* a_event)
	{
		if (!GetQueueHead()) {
			GetQueueHead() = a_event;
		}

		if (GetQueueTail()) {
			GetQueueTail()->next = a_event;
		}

		GetQueueTail() = a_event;
		GetQueueTail()->next = nullptr;
	}

	void BSInputEventQueue::ClearInputQueue()
	{
		kinectEventCount = 0;
		connectEventCount = 0;
		thumbstickEventCount = 0;
		mouseEventCount = 0;
		charEventCount = 0;
		buttonEventCount = 0;
		GetQueueTail() = nullptr;
		GetQueueHead() = nullptr;
	}
}
