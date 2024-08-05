#include "RE/C/ConsoleLog.h"
#include "RE/T/TLSData.h"

namespace RE
{
	ConsoleLog* ConsoleLog::GetSingleton()
	{
		REL::Relocation<ConsoleLog**> singleton{ RELOCATION_ID(515064, 401203) };
		return *singleton;
	}

	bool ConsoleLog::IsConsoleMode()
	{
		return GetStaticTLSData()->consoleMode;
	}

	void ConsoleLog::Print(const char* a_fmt, ...)
	{
		std::va_list args;
		va_start(args, a_fmt);
		VPrint(a_fmt, args);
		va_end(args);
	}

	void ConsoleLog::VPrint(const char* a_fmt, std::va_list a_args)
	{
		using func_t = decltype(&ConsoleLog::Print);
		static REL::Relocation<func_t> func{ RELOCATION_ID(50180, 51110) };
		func(this, a_fmt, a_args);
	}
}
