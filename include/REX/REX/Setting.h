#pragma once

#include "REX/REX/Singleton.h"

namespace REX
{
	class ISetting
	{
	public:
		virtual void Load(void* a_data, bool a_isBase) = 0;
		virtual void Save(void* a_data) = 0;
	};

	class ISettingStore
	{
	public:
		virtual void Init(const char* a_file, const char* a_fileCustom) = 0;
		virtual void Load() = 0;
		virtual void Save() = 0;
		virtual void Register(ISetting* a_setting) = 0;
	};

	template <class T, class Store>
	class TSetting :
		public ISetting
	{
	public:
		TSetting() = delete;

		TSetting(T a_default) :
			m_value(a_default),
			m_valueDefault(a_default)
		{
			Store::GetSingleton()->Register(this);
		}

	public:
		T GetValue() const { return m_value; }

		T GetValueDefault() const { return m_valueDefault; }

		void SetValue(T a_value) { m_value = a_value; }

	protected:
		T m_value;
		T m_valueDefault;
	};

	template <class T>
	class TSettingStore :
		public ISettingStore,
		public Singleton<T>
	{
	public:
		virtual void Init(const char* a_fileBase, const char* a_fileUser) override
		{
			m_fileBase = a_fileBase;
			m_fileUser = a_fileUser;
		}

		virtual void Register(ISetting* a_setting) override
		{
			m_settings.emplace_back(a_setting);
		}

	protected:
		std::string_view       m_fileBase;
		std::string_view       m_fileUser;
		std::vector<ISetting*> m_settings;
	};
}
