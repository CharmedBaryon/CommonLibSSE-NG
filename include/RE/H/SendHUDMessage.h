#pragma once

namespace RE
{
	namespace SendHUDMessage
	{
		inline void PopHUDMode(const char* a_hudMode)
		{
			using func_t = decltype(&SendHUDMessage::PopHUDMode);
			REL::Relocation<func_t> func{ RELOCATION_ID(50726, 51621) };
			return func(a_hudMode);
		}

		inline void PushHUDMode(const char* a_hudMode)
		{
			using func_t = decltype(&SendHUDMessage::PushHUDMode);
			REL::Relocation<func_t> func{ RELOCATION_ID(50725, 51620) };
			return func(a_hudMode);
		}
	}
}
