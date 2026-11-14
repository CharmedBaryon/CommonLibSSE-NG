#pragma once
#include "RE/B/BSFixedString.h"
#include "REL/Relocation.h"
#include "REL/RuntimeDataAccessors.h"
#include "SKSE/Version.h"

namespace RE
{
	class ButtonEvent;
	class InputEvent;
	class MouseMoveEvent;
#ifdef ENABLE_SKYRIM_AE
	class MotionGestureEvent;
	class SixaxisEvent;
#endif
	class PlayerControlsData;
	class SixaxisEvent;
	class ThumbstickEvent;
	class VrWandTouchpadPositionEvent;
	class VrWandTouchpadSwipeEvent;

	class PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_PlayerInputHandler;
		inline static constexpr auto VTABLE = VTABLE_PlayerInputHandler;

		virtual ~PlayerInputHandler() = default;  // 00

		virtual bool CanProcess(InputEvent* a_event) = 0;  // 01
#if defined(EXCLUSIVE_SKYRIM_VR)
		virtual void ProcessVrWandTouchpadSwipe([[maybe_unused]] VrWandTouchpadSwipeEvent* a_event, [[maybe_unused]] PlayerControlsData* a_data)
		{}                                                                                                                                                 // 02
		virtual void ProcessVrWandTouchpadPosition([[maybe_unused]] VrWandTouchpadPositionEvent* a_event, [[maybe_unused]] PlayerControlsData* a_data) {}  // 03
		virtual void ProcessThumbstick([[maybe_unused]] ThumbstickEvent* a_event, [[maybe_unused]] PlayerControlsData* a_data) {}                          // 04
		virtual void ProcessMouseMove([[maybe_unused]] MouseMoveEvent* a_event, [[maybe_unused]] PlayerControlsData* a_data) {}                            // 05
		virtual void ProcessButton([[maybe_unused]] ButtonEvent* a_event, [[maybe_unused]] PlayerControlsData* a_data) {}                                  // 06
#else
		static constexpr std::size_t kAE1799AddedVFuncCount = 2;  // matches ProcessMotionGesture/ProcessSixaxis below

		void ProcessThumbstick(ThumbstickEvent* a_event, PlayerControlsData* a_data)
		{
			REL::RelocateVirtual<void(PlayerInputHandler*, ThumbstickEvent*, PlayerControlsData*)>(REL::VersionShift(0x02, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), 0x04, this, a_event, a_data);
		}
		void ProcessMouseMove(MouseMoveEvent* a_event, PlayerControlsData* a_data)
		{
			REL::RelocateVirtual<void(PlayerInputHandler*, MouseMoveEvent*, PlayerControlsData*)>(REL::VersionShift(0x03, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), 0x05, this, a_event, a_data);
		}
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data)
		{
			REL::RelocateVirtual<void(PlayerInputHandler*, ButtonEvent*, PlayerControlsData*)>(REL::VersionShift(0x04, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), 0x06, this, a_event, a_data);
		}

#	ifdef ENABLE_SKYRIM_AE
		void ProcessMotionGesture(MotionGestureEvent* a_event, PlayerControlsData* a_data)
		{
			if (REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
				REL::RelocateVirtual<void(PlayerInputHandler*, MotionGestureEvent*, PlayerControlsData*)>(0x02, 0x02, this, a_event, a_data);
			}
		}
		void ProcessSixaxis(SixaxisEvent* a_event, PlayerControlsData* a_data)
		{
			if (REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
				REL::RelocateVirtual<void(PlayerInputHandler*, SixaxisEvent*, PlayerControlsData*)>(0x03, 0x03, this, a_event, a_data);
			}
		}
#	endif

		void ProcessVrWandTouchpadSwipe(VrWandTouchpadSwipeEvent* a_event, PlayerControlsData* a_data)
		{
			if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
				REL::RelocateVirtual<void(PlayerInputHandler*, VrWandTouchpadSwipeEvent*, PlayerControlsData*)>(0x02, 0x02, this, a_event, a_data);
			}
		}
		void ProcessVrWandTouchpadPosition(VrWandTouchpadPositionEvent* a_event, PlayerControlsData* a_data)
		{
			if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
				REL::RelocateVirtual<void(PlayerInputHandler*, VrWandTouchpadPositionEvent*, PlayerControlsData*)>(0x03, 0x03, this, a_event, a_data);
			}
		}
#endif

		[[nodiscard]] bool IsInputEventHandlingEnabled() const;
		void               SetInputEventHandlingEnabled(bool a_enabled);

		// members
		bool          inputEventHandlingEnabled;  // 08
		std::uint8_t  pad09{ 0 };                 // 09
		std::uint16_t pad0A{ 0 };                 // 0A
		std::uint32_t pad0C{ 0 };                 // 0C
	};
	STATIC_ASSERT_SIZE(PlayerInputHandler, 0x10);
}
