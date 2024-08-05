#pragma once

#include "RE/B/BSTCaseInsensitiveStringMap.h"
#include "RE/S/Setting.h"
#include "RE/S/SettingCollection.h"

namespace RE
{
	template <class T>
	class SettingCollectionMap : public SettingCollection<T>
	{
	public:
		~SettingCollectionMap() override;  // 00

		// override (SettingCollection<T>)
		void InsertSetting(T* a_setting) override;  // 01
		void RemoveSetting(T* a_setting) override;  // 02
		void WriteAllSettings() override;           // 08
		void ReadAllSettings() override;            // 09

		// members
		BSTCaseInsensitiveStringMap<T*> settings;  // 118
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(SettingCollectionMap<Setting>) == 0x140);
}
