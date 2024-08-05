#pragma once

#include "RE/B/BSTList.h"
#include "RE/S/SettingCollection.h"

namespace RE
{
	template <class T>
	class SettingCollectionList : public SettingCollection<T>
	{
	public:
		~SettingCollectionList() override;  // 00

		// override (SettingCollection<T>)
		void InsertSetting(T* a_setting) override;  // 01
		void RemoveSetting(T* a_setting) override;  // 02
		void WriteAllSettings() override;           // 08
		void ReadAllSettings() override;            // 09

		// members
		BSSimpleList<T*> settings;  // 118
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(SettingCollectionList<void*>) == 0x128);
}
