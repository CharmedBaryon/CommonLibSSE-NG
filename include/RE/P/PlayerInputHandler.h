#pragma once
#include "RE/B/BSFixedString.h"

namespace RE
{
	class ButtonEvent;
	class InputEvent;
	class MouseMoveEvent;
	class PlayerControlsData;
	class ThumbstickEvent;

	class PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_PlayerInputHandler;
		inline static constexpr auto VTABLE = VTABLE_PlayerInputHandler;

		virtual ~PlayerInputHandler() = default;  // 00

		virtual bool CanProcess(InputEvent* a_event) = 0;                                                                          // 01
		virtual void ProcessThumbstick([[maybe_unused]] ThumbstickEvent* a_event, [[maybe_unused]] PlayerControlsData* a_data) {}  // 02
		virtual void ProcessMouseMove([[maybe_unused]] MouseMoveEvent* a_event, [[maybe_unused]] PlayerControlsData* a_data) {}    // 03
		virtual void ProcessButton([[maybe_unused]] ButtonEvent* a_event, [[maybe_unused]] PlayerControlsData* a_data) {}          // 04

#ifdef ENABLE_SKYRIM_VR
		virtual void Unk_05(void);  // 05
		virtual void Unk_06(void);  // 05
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
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(PlayerInputHandler) == 0x28);
#else
	static_assert(sizeof(PlayerInputHandler) == 0x10);
#endif
}
