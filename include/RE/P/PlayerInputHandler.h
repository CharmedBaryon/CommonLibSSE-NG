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

		virtual ~PlayerInputHandler();  // 00

		virtual bool CanProcess(InputEvent* a_event) = 0;                                      // 01
		virtual void ProcessThumbstick(ThumbstickEvent* a_event, PlayerControlsData* a_data);  // 02 - { return; }
		virtual void ProcessMouseMove(MouseMoveEvent* a_event, PlayerControlsData* a_data);    // 03 - { return; }
		virtual void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_data);          // 04 - { return; }

#ifdef ENABLE_SKYRIM_VR
		virtual void Unk_05(void);  // 05
		virtual void Unk_06(void);  // 05
#endif

		[[nodiscard]] bool IsInputEventHandlingEnabled() const;
		void               SetInputEventHandlingEnabled(bool a_enabled);

		// members
		bool          inputEventHandlingEnabled;  // 08
		std::uint8_t  pad09;                      // 09
		std::uint16_t pad0A;                      // 0A
		std::uint32_t pad0C;                      // 0C
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		std::uint64_t unk10;  // 10
		BSFixedString unk18;  // 18
		std::uint64_t unk20;
#endif
	private:
		KEEP_FOR_RE()
	};
#if !defined(ENABLE_SKYRIM_VR)
	static_assert(sizeof(PlayerInputHandler) == 0x10);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(PlayerInputHandler) == 0x28);
#else
	static_assert(sizeof(PlayerInputHandler) == 0x10);
#endif
}
