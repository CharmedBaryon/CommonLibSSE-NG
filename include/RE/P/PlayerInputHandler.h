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

	class PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_PlayerInputHandler;
		inline static constexpr auto VTABLE = VTABLE_PlayerInputHandler;

		virtual ~PlayerInputHandler() = default;  // 00

		virtual bool CanProcess(InputEvent* a_event) = 0;  // 01
#if defined(EXCLUSIVE_SKYRIM_VR)
		virtual void ProcessThumbstick([[maybe_unused]] ThumbstickEvent* a_event, [[maybe_unused]] PlayerControlsData* a_data)
		{}                                                                                                                       // 02
		virtual void ProcessMouseMove([[maybe_unused]] MouseMoveEvent* a_event, [[maybe_unused]] PlayerControlsData* a_data) {}  // 03
		virtual void ProcessButton([[maybe_unused]] ButtonEvent* a_event, [[maybe_unused]] PlayerControlsData* a_data) {}        // 04
		virtual void Unk_05(void);                                                                                               // 05
		virtual void Unk_06(void);                                                                                               // 06
#else
		static constexpr std::size_t kAE1799AddedVFuncCount = 2;  // matches ProcessMotionGesture/ProcessSixaxis below

		void ProcessThumbstick(ThumbstickEvent* a_event, PlayerControlsData* a_data)
		{
			REL::RelocateVirtual<void(PlayerInputHandler*, ThumbstickEvent*, PlayerControlsData*)>(REL::VersionShift(0x02, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), 0x02, this, a_event, a_data);
		}
		void ProcessMouseMove(MouseMoveEvent* a_event, PlayerControlsData* a_data)
		{
			REL::RelocateVirtual<void(PlayerInputHandler*, MouseMoveEvent*, PlayerControlsData*)>(REL::VersionShift(0x03, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), 0x03, this, a_event, a_data);
		}
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data)
		{
			REL::RelocateVirtual<void(PlayerInputHandler*, ButtonEvent*, PlayerControlsData*)>(REL::VersionShift(0x04, kAE1799AddedVFuncCount, SKSE::RUNTIME_SSE_1_7_99), 0x04, this, a_event, a_data);
		}

#	ifdef ENABLE_SKYRIM_AE
		bool ProcessMotionGesture(MotionGestureEvent* a_event)
		{
			if (!REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
				return false;
			}
			return REL::RelocateVirtual<bool(PlayerInputHandler*, MotionGestureEvent*)>(0x02, 0x02, this, a_event);
		}
		bool ProcessSixaxis(SixaxisEvent* a_event)
		{
			if (!REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99)) {
				return false;
			}
			return REL::RelocateVirtual<bool(PlayerInputHandler*, SixaxisEvent*)>(0x03, 0x03, this, a_event);
		}
#	endif

		void Unk_05(void)
		{
			if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
				REL::RelocateVirtual<void(PlayerInputHandler*)>(0x05, 0x05, this);
			}
		}
		void Unk_06(void)
		{
			if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
				REL::RelocateVirtual<void(PlayerInputHandler*)>(0x06, 0x06, this);
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
#if defined(EXCLUSIVE_SKYRIM_VR)
		std::uint64_t unk10;  // 10
		BSFixedString unk18;  // 18
		std::uint64_t unk20;
#endif
	};
	STATIC_ASSERT_SIZE(PlayerInputHandler, 0x10, 0x10, 0x28, 0x10);
}
