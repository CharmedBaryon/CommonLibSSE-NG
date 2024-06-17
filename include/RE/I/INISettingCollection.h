#pragma once

#include "RE/S/Setting.h"
#include "RE/S/SettingCollectionList.h"

namespace RE
{
	class INISettingCollection : public SettingCollectionList<Setting>
	{
	public:
		inline static constexpr auto RTTI = RTTI_INISettingCollection;
		inline static constexpr auto VTABLE = VTABLE_INISettingCollection;

		~INISettingCollection() override;  // 00

		// override (SettingCollectionList<Setting>)
		bool WriteSetting(Setting* a_setting) override;  // 03
		bool ReadSetting(Setting* a_setting) override;   // 04
		bool OpenHandle(bool a_create) override;         // 05 - { handle = this; return true; }
		bool CloseHandle() override;                     // 06 - { handle = 0; return true; }

		static INISettingCollection* GetSingleton();

		Setting* GetSetting(std::string_view a_name);

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(INISettingCollection) == 0x128);
}
