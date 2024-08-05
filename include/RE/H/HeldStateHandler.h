#pragma once

#include "RE/P/PlayerInputHandler.h"

namespace RE
{
	class HeldStateHandler : public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_HeldStateHandler;
		inline static constexpr auto VTABLE = VTABLE_HeldStateHandler;

		~HeldStateHandler() override = default;  // 00

		// add
		virtual void UpdateHeldStateActive(const ButtonEvent* a_event);  // 05
		virtual void SetHeldStateActive(bool a_flag);                    // 06

		// members
		bool          heldStateActive{ false };      // 10
		bool          triggerReleaseEvent{ false };  // 11
		std::uint16_t pad12{ 0 };                    // 12
		std::uint32_t pad14{ 0 };                    // 14
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(HeldStateHandler) == 0x30);
#else
	static_assert(sizeof(HeldStateHandler) == 0x18);
#endif
}
