#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	class MenuModeChangeEvent
	{
	public:
		enum class Mode
		{
			kNone = static_cast<std::underlying_type_t<Mode>>(-1),
			kHidden = 0,
			kDisplayed = 1
		};

		BSFixedString                        menu;  // 00
		stl::enumeration<Mode, std::uint8_t> mode;  // 08
	private:
		KEEP_FOR_RE()
	};
}
