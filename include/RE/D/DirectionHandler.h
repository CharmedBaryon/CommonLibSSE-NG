#pragma once

#include "RE/M/MenuEventHandler.h"

namespace RE
{
	struct DirectionHandler : public MenuEventHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_DirectionHandler;

		virtual ~DirectionHandler();  // 00

		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;              // 01
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03
		bool ProcessButton(ButtonEvent* a_event) override;          // 05

		// members
		std::uint32_t unk10;               // 10
		float         menuKeyRepeatLong;   // 14
		float         menuKeyRepeatShort;  // 18
		std::uint64_t unk20;               // 20
		std::uint32_t unk28;               // 28
		std::uint32_t unk2C;               // 2C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(DirectionHandler) == 0x30);
}
