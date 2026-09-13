#pragma once

namespace RE
{
	enum class PROCESS_TYPE
	{
		kNone = static_cast<std::underlying_type_t<PROCESS_TYPE>>(-1),
		kHigh = 0,
		kMiddleHigh = 1,
		kMiddleLow = 2,
		kLow = 3
	};
}
