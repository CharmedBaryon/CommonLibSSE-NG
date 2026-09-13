#pragma once

#include "RE/A/AmiiboEvent.h"
#include "RE/B/BSTSingleton.h"
#include "RE/B/ButtonEvent.h"
#include "RE/C/CharEvent.h"
#include "RE/D/DeviceConnectEvent.h"
#include "RE/K/KinectEvent.h"
#include "RE/M/MotionGestureEvent.h"
#include "RE/M/MouseMoveEvent.h"
#include "RE/S/SixaxisEvent.h"
#include "RE/T/ThumbstickEvent.h"
#include "RE/V/VrWandTouchpadPositionEvent.h"
#include "RE/V/VrWandTouchpadSwipeEvent.h"
#include "REL/RuntimeDataAccessors.h"
#include "SKSE/Version.h"

#ifdef ENABLE_SKYRIM_AE
#	include "RE/A/AmiiboEvent.h"
#	include "RE/M/MotionGestureEvent.h"
#	include "RE/S/SixaxisEvent.h"
#endif

namespace RE
{
	class BSInputEventQueue : public BSTSingletonSDM<BSInputEventQueue>
	{
	public:
		inline static constexpr std::uint8_t MAX_BUTTON_EVENTS = 10;
		inline static constexpr std::uint8_t MAX_CHAR_EVENTS = 5;
		inline static constexpr std::uint8_t MAX_MOUSE_EVENTS = 1;
		inline static constexpr std::uint8_t MAX_THUMBSTICK_EVENTS = 2;
		inline static constexpr std::uint8_t MAX_CONNECT_EVENTS = 1;
		inline static constexpr std::uint8_t MAX_KINECT_EVENTS = 1;
		inline static constexpr std::uint8_t MAX_VR_TOUCHPAD_POSITION_EVENTS = 3;
		inline static constexpr std::uint8_t MAX_VR_TOUCHPAD_SWIPE_EVENTS = 3;
#ifdef ENABLE_SKYRIM_AE
		// New in AE 1.7.99.
		inline static constexpr std::uint8_t MAX_SIXAXIS_EVENTS = 2;
		inline static constexpr std::uint8_t MAX_MOTION_GESTURE_EVENTS = 2;
		inline static constexpr std::uint8_t MAX_AMIIBO_EVENTS = 1;
#endif

		static BSInputEventQueue* GetSingleton();

		template <class... Args>
		void AddButtonEvent(Args&&... args)
		{
			AddEvent<ButtonEvent>(std::forward<Args>(args)...);
		}

		template <class... Args>
		void AddCharEvent(Args&&... args)
		{
			AddEvent<CharEvent>(std::forward<Args>(args)...);
		}

		template <class... Args>
		void AddMouseMoveEvent(Args&&... args)
		{
			AddEvent<MouseMoveEvent>(std::forward<Args>(args)...);
		}

		template <class... Args>
		void AddThumbstickEvent(Args&&... args)
		{
			AddEvent<ThumbstickEvent>(std::forward<Args>(args)...);
		}

		template <class... Args>
		void AddConnectEvent(Args&&... args)
		{
			AddEvent<DeviceConnectEvent>(std::forward<Args>(args)...);
		}

		template <class... Args>
		void AddKinectEvent(Args&&... args)
		{
			AddEvent<KinectEvent>(std::forward<Args>(args)...);
		}

// VR-specific overloads (forward to the template implementations)
#if defined(ENABLE_SKYRIM_VR)
		void AddButtonEvent(INPUT_DEVICE a_device, std::int32_t a_arg2, std::int32_t a_id, float a_value, float a_duration, const BSFixedString& a_userEvent = {});
		void AddThumbstickEvent(ThumbstickEvent::InputType a_id, INPUT_DEVICE a_device, float a_xValue, float a_yValue);
#endif

		void PushOntoInputQueue(InputEvent* a_event);
		void ClearInputQueue();

		struct VRTOUCHPAD_DATA
		{
#define VRTOUCHPAD_DATA_CONTENT                 \
	std::uint32_t vrTouchpadPositionEventCount; \
	std::uint32_t vrTouchpadSwipeEventCount;
			VRTOUCHPAD_DATA_CONTENT
		};
		static_assert(sizeof(VRTOUCHPAD_DATA) == 0x8);

		struct VRTOUCHPADEVENT_DATA
		{
#define VRTOUCHPADEVENT_DATA_CONTENT                                                       \
	VrWandTouchpadPositionEvent vrTouchpadPositionEvents[MAX_VR_TOUCHPAD_POSITION_EVENTS]; \
	VrWandTouchpadSwipeEvent    vrTouchpadSwipeEvents[MAX_VR_TOUCHPAD_SWIPE_EVENTS];
            VRTOUCHPADEVENT_DATA_CONTENT
		};
		static_assert(sizeof(VRTOUCHPADEVENT_DATA) == 0x198);

		// On AE, use GetQueueHead()/GetQueueTail(), not this struct's queueHead/queueTail.
		struct RUNTIME_DATA
		{
#if !defined(ENABLE_SKYRIM_VR)  // Non-VR
#	define RUNTIME_DATA_CONTENT                                             \
		ButtonEvent        buttonEvents[MAX_BUTTON_EVENTS];         /* 020*/ \
		CharEvent          charEvents[MAX_CHAR_EVENTS];             /* 200*/ \
		MouseMoveEvent     mouseEvents[MAX_MOUSE_EVENTS];           /* 2A0*/ \
		ThumbstickEvent    thumbstickEvents[MAX_THUMBSTICK_EVENTS]; /* 2D0*/ \
		DeviceConnectEvent connectEvents[MAX_CONNECT_EVENTS];       /* 330*/ \
		KinectEvent        kinectEvents[MAX_KINECT_EVENTS];         /* 350*/ \
		InputEvent*        queueHead;                               /* 380*/ \
		InputEvent*        queueTail;                               /* 388*/
#else
#	define RUNTIME_DATA_CONTENT                                             \
		VRTOUCHPAD_DATA_CONTENT;                                    /* 020*/ \
		ButtonEvent        buttonEvents[MAX_BUTTON_EVENTS];         /* 028*/ \
		CharEvent          charEvents[MAX_CHAR_EVENTS];             /* 258*/ \
		MouseMoveEvent     mouseEvents[MAX_MOUSE_EVENTS];           /* 2F8*/ \
		ThumbstickEvent    thumbstickEvents[MAX_THUMBSTICK_EVENTS]; /* 328*/ \
		DeviceConnectEvent connectEvents[MAX_CONNECT_EVENTS];       /* 388*/ \
		KinectEvent        kinectEvents[MAX_KINECT_EVENTS];         /* 3A8*/ \
		VRTOUCHPADEVENT_DATA_CONTENT;                               /* 3D8*/ \
		InputEvent* queueHead;                                      /* 570*/ \
		InputEvent* queueTail;                                      /* 578*/
#endif
			RUNTIME_DATA_CONTENT
		};

#ifdef ENABLE_SKYRIM_AE
		struct AE1799_EVENT_DATA
		{
			SixaxisEvent       sixaxisEvents[MAX_SIXAXIS_EVENTS];               // 000
			MotionGestureEvent motionGestureEvents[MAX_MOTION_GESTURE_EVENTS];  // 120
			AmiiboEvent        amiiboEvents[MAX_AMIIBO_EVENTS];                 // 190
		};
		static_assert(sizeof(AE1799_EVENT_DATA) == 0x1D0);
#endif

		// members
		std::uint8_t  pad001;                // 001
		std::uint16_t pad002;                // 002
		std::uint32_t buttonEventCount;      // 004
		std::uint32_t charEventCount;        // 008
		std::uint32_t mouseEventCount;       // 00C
		std::uint32_t thumbstickEventCount;  // 010
		std::uint32_t connectEventCount;     // 014
		std::uint32_t kinectEventCount;      // 018
		std::uint32_t pad01C;                // 01C
#if (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_VR))
		RUNTIME_DATA_CONTENT
#endif

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
#ifdef ENABLE_SKYRIM_AE
			const std::ptrdiff_t seAndAe =
				REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99) ?
					0x28 :
					0x20;
#else
			const std::ptrdiff_t seAndAe = 0x20;
#endif
			return REL::RelocateMember<RUNTIME_DATA>(this, seAndAe, 0x20);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return const_cast<BSInputEventQueue*>(this)->GetRuntimeData();
		}

#ifdef ENABLE_SKYRIM_AE
		RUNTIME_DATA_ACCESSOR_VERSIONED_OPTIONAL_EX(AE1799_EVENT_DATA, GetAe1799EventData, SKSE::RUNTIME_SSE_1_7_99, 0x388);
#endif

		// Engine offsets of the queue's head/tail links. As with the cached event arrays
		// below, RUNTIME_DATA's compiled offsets can't supply these in a cross-VR build.
		static constexpr std::ptrdiff_t kQueueHeadSE = 0x380;
		static constexpr std::ptrdiff_t kQueueHeadAE1799 = 0x558;
		static constexpr std::ptrdiff_t kQueueTailSE = 0x388;
		static constexpr std::ptrdiff_t kQueueTailAE1799 = 0x560;
		static constexpr std::ptrdiff_t kQueueHeadVR = 0x570;
		static constexpr std::ptrdiff_t kQueueTailVR = 0x578;

#if defined(EXCLUSIVE_SKYRIM_VR)
		[[nodiscard]] inline InputEvent*& GetQueueHead() noexcept
		{
			return GetRuntimeData().queueHead;
		}
		[[nodiscard]] inline InputEvent*& GetQueueTail() noexcept { return GetRuntimeData().queueTail; }
#elif defined(ENABLE_SKYRIM_VR)  // SKYRIM_CROSS_VR: either runtime is possible
		[[nodiscard]] inline InputEvent*& GetQueueHead() noexcept
		{
			if (REL::Module::IsVR()) {
				return REL::RelocateMember<InputEvent*>(this, 0, kQueueHeadVR);
			}
			return REL::RelocateMemberIfNewer<InputEvent*>(SKSE::RUNTIME_SSE_1_7_99, this, kQueueHeadSE, kQueueHeadAE1799);
		}

		[[nodiscard]] inline InputEvent*& GetQueueTail() noexcept
		{
			if (REL::Module::IsVR()) {
				return REL::RelocateMember<InputEvent*>(this, 0, kQueueTailVR);
			}
			return REL::RelocateMemberIfNewer<InputEvent*>(SKSE::RUNTIME_SSE_1_7_99, this, kQueueTailSE, kQueueTailAE1799);
		}
#else                            // SE-only, AE-only, or flat -- no VR possible
		[[nodiscard]] inline InputEvent*& GetQueueHead() noexcept
		{
			return REL::RelocateMemberIfNewer<InputEvent*>(SKSE::RUNTIME_SSE_1_7_99, this, kQueueHeadSE, kQueueHeadAE1799);
		}

		[[nodiscard]] inline InputEvent*& GetQueueTail() noexcept
		{
			return REL::RelocateMemberIfNewer<InputEvent*>(SKSE::RUNTIME_SSE_1_7_99, this, kQueueTailSE, kQueueTailAE1799);
		}
#endif

		[[nodiscard]] VRTOUCHPAD_DATA* GetVRTouchpadData() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return &REL::RelocateMember<VRTOUCHPAD_DATA>(this, 0, 0x20);
			}
		}

		[[nodiscard]] inline const VRTOUCHPAD_DATA* GetVRTouchpadData() const noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return &REL::RelocateMember<VRTOUCHPAD_DATA>(this, 0, 0x20);
			}
		}

		[[nodiscard]] VRTOUCHPADEVENT_DATA* GetVRTouchpadEventData() noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return &REL::RelocateMember<VRTOUCHPADEVENT_DATA>(this, 0, 0x3D8);
			}
		}

		[[nodiscard]] inline const VRTOUCHPADEVENT_DATA* GetVRTouchpadEventData() const noexcept
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			} else {
				return &REL::RelocateMember<VRTOUCHPADEVENT_DATA>(this, 0, 0x3D8);
			}
		}

	private:
		// Per-runtime layout of each cached event array, taken from the engine's
		// Enqueue<Type>Event functions. RUNTIME_DATA can't supply these: in a cross-VR
		// build the event types inherit a common base, so their compile-time sizes -- and
		// therefore every following array's offset -- differ from the engine's.
		struct CachedEventArray
		{
			std::ptrdiff_t flatSE;      // SE 1.5.97, and AE below 1.7.99
			std::ptrdiff_t flatAE1799;  // AE 1.7.99 and above
			std::ptrdiff_t vr;
			std::ptrdiff_t flatStride;
			std::ptrdiff_t vrStride;

			[[nodiscard]] SKYRIM_REL std::ptrdiff_t Flat(std::uint32_t a_index) const noexcept
			{
				const auto base = REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99) ? flatAE1799 : flatSE;
				return base + static_cast<std::ptrdiff_t>(a_index) * flatStride;
			}

			[[nodiscard]] SKYRIM_REL std::ptrdiff_t VR(std::uint32_t a_index) const noexcept
			{
				return vr + static_cast<std::ptrdiff_t>(a_index) * vrStride;
			}
		};

		static constexpr CachedEventArray kButtonEventArray{ 0x20, 0x28, 0x28, 0x30, 0x38 };
		static constexpr CachedEventArray kCharEventArray{ 0x200, 0x208, 0x258, 0x20, 0x20 };
		static constexpr CachedEventArray kMouseEventArray{ 0x2A0, 0x2A8, 0x2F8, 0x30, 0x30 };
		static constexpr CachedEventArray kThumbstickEventArray{ 0x2D0, 0x2D8, 0x328, 0x30, 0x30 };
		static constexpr CachedEventArray kConnectEventArray{ 0x330, 0x338, 0x388, 0x20, 0x20 };
		static constexpr CachedEventArray kKinectEventArray{ 0x350, 0x358, 0x3A8, 0x30, 0x30 };

		template <class T>
		[[nodiscard]] T* CachedEventAt(const CachedEventArray& a_array, std::uint32_t a_index) noexcept
		{
			return &REL::RelocateMember<T>(this, a_array.Flat(a_index), a_array.VR(a_index));
		}

		template <class T>
		T* GetCachedEvent();

		template <class T>
		void AdvanceCount();

		template <class T, class... Args>
		void AddEvent(Args&&... args)
		{
			if (auto cachedEvent = GetCachedEvent<T>()) {
				cachedEvent->Init(std::forward<Args>(args)...);
				PushOntoInputQueue(cachedEvent);
				AdvanceCount<T>();
			}
		}
	};
#if defined(EXCLUSIVE_SKYRIM_SE)
	static_assert(sizeof(BSInputEventQueue) == 0x390);
	static_assert(offsetof(BSInputEventQueue, buttonEvents) == 0x20);
	static_assert(offsetof(BSInputEventQueue, charEvents) == 0x200);
	static_assert(offsetof(BSInputEventQueue, mouseEvents) == 0x2A0);
	static_assert(offsetof(BSInputEventQueue, thumbstickEvents) == 0x2D0);
	static_assert(offsetof(BSInputEventQueue, connectEvents) == 0x330);
	static_assert(offsetof(BSInputEventQueue, kinectEvents) == 0x350);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BSInputEventQueue) == 0x580);
	static_assert(offsetof(BSInputEventQueue, buttonEvents) == 0x28);
	static_assert(offsetof(BSInputEventQueue, charEvents) == 0x258);
	static_assert(offsetof(BSInputEventQueue, mouseEvents) == 0x2F8);
	static_assert(offsetof(BSInputEventQueue, thumbstickEvents) == 0x328);
	static_assert(offsetof(BSInputEventQueue, connectEvents) == 0x388);
	static_assert(offsetof(BSInputEventQueue, kinectEvents) == 0x3A8);
	static_assert(offsetof(BSInputEventQueue, vrTouchpadPositionEvents) == 0x3D8);
#else
	static_assert(sizeof(BSInputEventQueue) == 0x20);
#endif
}
#undef RUNTIME_DATA_CONTENT
#undef VRTOUCHPAD_DATA_CONTENT
#undef VRTOUCHPADEVENT_DATA_CONTENT
