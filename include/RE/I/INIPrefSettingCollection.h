#pragma once

#include "RE/I/INISettingCollection.h"

namespace RE
{
	class INIPrefSettingCollection : public INISettingCollection
	{
	public:
		inline static constexpr auto RTTI = RTTI_INIPrefSettingCollection;
		inline static constexpr auto VTABLE = VTABLE_INIPrefSettingCollection;

		~INIPrefSettingCollection() override;  // 00

		// override (INISettingCollection)
		void Unk_07(void) override;        // 07 - { return 1; }
		void WriteAllSettings() override;  // 08
		void ReadAllSettings() override;   // 09

		static INIPrefSettingCollection* GetSingleton();

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(INIPrefSettingCollection) == 0x128);
}
