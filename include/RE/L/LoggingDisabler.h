#pragma once

#include "RE/G/GFxLog.h"

namespace RE
{
	class LoggingDisabler : public GFxLog
	{
	public:
#if !defined(ENABLE_SKYRIM_AE)
		inline static auto RTTI = RTTI___LoggingDisabler;
#endif

		LoggingDisabler() = default;

		~LoggingDisabler() override = default;  // 00

		// override (GFxLog)
		void LogMessageVarg([[maybe_unused]] LogMessageType a_messageType, [[maybe_unused]] const char* a_fmt, [[maybe_unused]] std::va_list a_argList) override{};  // 01
	};
	static_assert(sizeof(LoggingDisabler) == 0x20);
}
