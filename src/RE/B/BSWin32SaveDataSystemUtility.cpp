#include "RE/B/BSWin32SaveDataSystemUtility.h"

namespace RE
{
	BSWin32SaveDataSystemUtility* BSWin32SaveDataSystemUtility::GetSingleton()
	{
		using func_t = decltype(&BSWin32SaveDataSystemUtility::GetSingleton);
		static REL::Relocation<func_t> func{ RELOCATION_ID(101884, 109278) };
		return func();
	}
}
