#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"
#include "REL/Relocation.h"
#include "REL/RuntimeDataAccessors.h"
#include "SKSE/Version.h"

namespace RE
{
	class ButtonEvent;
	class InputEvent;
	class KinectEvent;
	class MouseMoveEvent;
#ifdef ENABLE_SKYRIM_AE
	class MotionGestureEvent;
	class SixaxisEvent;
#endif
	class ThumbstickEvent;
	class VrWandTouchpadPositionEvent;
	class VrWandTouchpadSwipeEvent;

	class MenuEventHandler : public BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI = RTTI_MenuEventHandler;
		inline static constexpr auto VTABLE = VTABLE_MenuEventHandler;

		MenuEventHandler() = default;
		virtual ~MenuEventHandler() = default;  // 00

		virtual bool CanProcess(InputEvent* a_event) = 0;  // 01

#if defined(EXCLUSIVE_SKYRIM_VR)
		virtual bool ProcessVrWandTouchpadSwipe(VrWandTouchpadSwipeEvent* a_event);        // VR 02 - { return false; }
		virtual bool ProcessVrWandTouchpadPosition(VrWandTouchpadPositionEvent* a_event);  // VR 03 - { return false; }
		virtual bool Unk_04(void* a_event);                                                // VR 04 - { return false; }
		virtual bool ProcessKinect(KinectEvent* a_event);                                  // VR 05 - { return false; }
		virtual bool ProcessThumbstick(ThumbstickEvent* a_event);                          // VR 06 - { return false; }
		virtual bool ProcessMouseMove(MouseMoveEvent* a_event);                            // VR 07 - { return false; }
		virtual bool ProcessButton(ButtonEvent* a_event);                                  // VR 08 - { return false; }
#else
		static constexpr std::size_t kAE1799AddedVFuncCount = 2;  // matches ProcessMotionGesture/ProcessSixaxis below

		bool ProcessKinect(KinectEvent* a_event)
		{
			return REL::RelocateVirtual<decltype(&MenuEventHandler::ProcessKinect)>(REL::VersionShift(0x02, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), 0x05, this, a_event);
		}
		bool ProcessThumbstick(ThumbstickEvent* a_event)
		{
			return REL::RelocateVirtual<decltype(&MenuEventHandler::ProcessThumbstick)>(REL::VersionShift(0x03, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), 0x06, this, a_event);
		}
		bool ProcessMouseMove(MouseMoveEvent* a_event)
		{
			return REL::RelocateVirtual<decltype(&MenuEventHandler::ProcessMouseMove)>(REL::VersionShift(0x04, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), 0x07, this, a_event);
		}
		bool ProcessButton(ButtonEvent* a_event)
		{
			return REL::RelocateVirtual<decltype(&MenuEventHandler::ProcessButton)>(REL::VersionShift(0x05, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), 0x08, this, a_event);
		}

#	ifdef ENABLE_SKYRIM_AE
		bool ProcessMotionGesture(MotionGestureEvent* a_event)
		{
			if (!REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
				return false;
			}
			return REL::RelocateVirtual<bool(MenuEventHandler*, MotionGestureEvent*)>(0x02, 0x02, this, a_event);
		}
		bool ProcessSixaxis(SixaxisEvent* a_event)
		{
			if (!REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
				return false;
			}
			return REL::RelocateVirtual<bool(MenuEventHandler*, SixaxisEvent*)>(0x03, 0x03, this, a_event);
		}
#	endif

		bool ProcessVrWandTouchpadSwipe(VrWandTouchpadSwipeEvent* a_event)
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return false;
			} else {
				return REL::RelocateVirtual<bool(MenuEventHandler*, VrWandTouchpadSwipeEvent*)>(0x02, 0x02, this, a_event);
			}
		}
		bool ProcessVrWandTouchpadPosition(VrWandTouchpadPositionEvent* a_event)
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return false;
			} else {
				return REL::RelocateVirtual<bool(MenuEventHandler*, VrWandTouchpadPositionEvent*)>(0x03, 0x03, this, a_event);
			}
		}
		bool Unk_04(void* a_event)
		{
			if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
				return false;
			} else {
				return REL::RelocateVirtual<bool(MenuEventHandler*, void*)>(0x04, 0x04, this, a_event);
			}
		}
#endif

		// members
		bool          registered;  // 0C
		std::uint8_t  unk0D;       // 0D
		std::uint16_t pad0E;       // 0E
	};
	static_assert(sizeof(MenuEventHandler) == 0x10);
}
