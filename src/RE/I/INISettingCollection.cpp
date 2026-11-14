#include "RE/I/INISettingCollection.h"

namespace RE
{
	INISettingCollection* INISettingCollection::GetSingleton()
	{
		static REL::Relocation<INISettingCollection**> singleton{ RELOCATION_ID(524557, 411155) };
		return *singleton;
	}

	Setting* INISettingCollection::GetSetting(std::string_view a_name)
	{
		for (auto& setting : settings) {
			if (a_name.size() == strlen(setting->GetName()) &&
				_strnicmp(setting->GetName(), a_name.data(), a_name.size()) == 0) {
				return setting;
			}
		}
		return nullptr;
	}
}
