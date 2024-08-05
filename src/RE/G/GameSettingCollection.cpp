#include "RE/G/GameSettingCollection.h"

namespace RE
{
	GameSettingCollection* GameSettingCollection::GetSingleton()
	{
		REL::Relocation<GameSettingCollection**> singleton{ RELOCATION_ID(514622, 400782) };
		return *singleton;
	}

	Setting* GameSettingCollection::GetSetting(const char* a_name)
	{
		auto it = settings.find(a_name);
		return it != settings.end() ? it->second : nullptr;
	}
}
