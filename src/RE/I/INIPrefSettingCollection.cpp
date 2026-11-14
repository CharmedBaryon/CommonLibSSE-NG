#include "RE/I/INIPrefSettingCollection.h"

namespace RE
{
	INIPrefSettingCollection* INIPrefSettingCollection::GetSingleton()
	{
		static REL::Relocation<INIPrefSettingCollection**> singleton{ RELOCATION_ID(523673, 410219) };
		return *singleton;
	}
}
