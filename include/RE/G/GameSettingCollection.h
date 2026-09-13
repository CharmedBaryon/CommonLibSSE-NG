#pragma once

#include "RE/S/Setting.h"
#include "RE/S/SettingCollectionMap.h"

namespace RE
{
	class GameSettingCollection : public SettingCollectionMap<Setting>
	{
	public:
		inline static constexpr auto RTTI = RTTI_GameSettingCollection;
		inline static constexpr auto VTABLE = VTABLE_GameSettingCollection;

		~GameSettingCollection() override;  // 00

		// override (SettingCollectionMap<Setting>)
		bool WriteSetting(Setting* a_setting) override;  // 03 - { return false; }
		bool ReadSetting(Setting* a_setting) override;   // 04
		bool OpenHandle(bool a_create) override;         // 05 - { return handle != 0; }
		bool CloseHandle() override;                     // 06 - { handle = 0; return true; }

		// add
		virtual void Unk_0A(void);  // 0A

		static GameSettingCollection* GetSingleton();

		Setting* GetSetting(const char* a_name);
	};
	static_assert(sizeof(GameSettingCollection) == 0x140);

	namespace literals
	{
		template <stl::nttp::zstring S>
		inline auto operator""_gs()
		{
			static RE::Setting* setting = nullptr;
			if (!setting) {
				if (auto collection = GameSettingCollection::GetSingleton()) {
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
