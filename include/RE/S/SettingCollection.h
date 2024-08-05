#pragma once

namespace RE
{
	class TESFile;

	template <class T>
	class SettingCollection
	{
	public:
		virtual ~SettingCollection();  // 00

		// add
		virtual void InsertSetting(T* a_setting) = 0;  // 01
		virtual void RemoveSetting(T* a_setting) = 0;  // 02
		virtual bool WriteSetting(T* a_setting) = 0;   // 03
		virtual bool ReadSetting(T* a_setting) = 0;    // 04
		virtual bool OpenHandle(bool a_create);        // 05 - { return false; }
		virtual bool CloseHandle();                    // 06 - { return true; }
		virtual void Unk_07(void);                     // 07 - { return 0; }
		virtual void WriteAllSettings();               // 08 - { return handle != 0; }
		virtual void ReadAllSettings();                // 09 - { return handle != 0; }

		// members
		char  subKey[0x104];  // 008
		void* handle;         // 110
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(SettingCollection<void*>) == 0x118);
}
