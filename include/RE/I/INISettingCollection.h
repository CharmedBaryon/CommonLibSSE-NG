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
	};
	static_assert(sizeof(INISettingCollection) == 0x128);

	namespace literals
	{
		template <stl::nttp::zstring S>
		inline auto operator""_ini()
		{
			static RE::Setting* setting = nullptr;
			if (!setting) {
				if (auto collection = INISettingCollection::GetSingleton()) {
					setting = collection->GetSetting(S.data());
				}
			}

			if constexpr (S.front() == 'b') {
				return setting ? std::optional(setting->data.b) : std::nullopt;
			} else if constexpr (S.front() == 'f') {
				return setting ? std::optional(setting->data.f) : std::nullopt;
			} else if constexpr (S.front() == 'i') {
				return setting ? std::optional(setting->data.i) : std::nullopt;
			} else if constexpr (S.front() == 'r') {
				return setting ? std::optional(setting->data.r) : std::nullopt;
			} else if constexpr (S.front() == 's') {
				return setting ? std::optional(setting->data.s) : std::nullopt;
			} else if constexpr (S.front() == 'u') {
				return setting ? std::optional(setting->data.u) : std::nullopt;
			}
		}
	}
}
