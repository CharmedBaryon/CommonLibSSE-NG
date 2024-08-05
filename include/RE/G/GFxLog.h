#pragma once

#include "RE/G/GFxLogBase.h"
#include "RE/G/GFxState.h"

namespace RE
{
	class GFxLog :
		public GFxState,           // 00
		public GFxLogBase<GFxLog>  // 18
	{
	public:
		inline static constexpr auto RTTI = RTTI_GFxLog;
		inline static constexpr auto VTABLE = VTABLE_GFxLog;

		GFxLog();
		~GFxLog() override = default;  // 00

		// add
		virtual void LogMessageVarg(LogMessageType a_messageType, const char* a_fmt, std::va_list a_argList);  // 01

		void LogMessageByType(LogMessageType a_messageType, const char* a_fmt, ...);

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GFxLog) == 0x20);
}
