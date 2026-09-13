#include "REX/REX/INI.h"
#include "REX/REX/JSON.h"
#include "REX/REX/TOML.h"

#include "SKSE/Logger.h"

#ifdef REX_OPTION_INI
#	include <SimpleIni.h>

namespace REX::INI
{
	namespace Impl
	{
		template <class T>
		constexpr bool is_long_integral_v = std::_Is_any_of_v<std::remove_cv_t<T>, std::uint8_t, std::uint16_t, std::uint32_t, std::int8_t, std::int16_t, std::int32_t>;

		template <class T>
		void SettingLoad<T>(
			void* a_data,
			sec_t a_section,
			key_t a_key,
			T&    a_value,
			T&    a_valueDefault)
		{
			const auto file = static_cast<CSimpleIniA*>(a_data);
			if constexpr (std::is_same_v<T, bool>) {
				a_value = file->GetBoolValue(a_section.data(), a_key.data(), a_valueDefault);
			} else if constexpr (std::is_floating_point_v<T>) {
				a_value = static_cast<T>(file->GetDoubleValue(a_section.data(), a_key.data(), a_valueDefault));
			} else if constexpr (is_long_integral_v<T>) {
				a_value = static_cast<T>(file->GetLongValue(a_section.data(), a_key.data(), a_valueDefault));
			} else if constexpr (std::is_same_v<T, std::string>) {
				a_value = file->GetValue(a_section.data(), a_key.data(), a_valueDefault.c_str());
			}
		}

		template void SettingLoad<bool>(void*, sec_t, key_t, bool&, bool&);
		template void SettingLoad<float>(void*, sec_t, key_t, float&, float&);
		template void SettingLoad<double>(void*, sec_t, key_t, double&, double&);
		template void SettingLoad<std::uint8_t>(void*, sec_t, key_t, std::uint8_t&, std::uint8_t&);
		template void SettingLoad<std::uint16_t>(void*, sec_t, key_t, std::uint16_t&, std::uint16_t&);
		template void SettingLoad<std::uint32_t>(void*, sec_t, key_t, std::uint32_t&, std::uint32_t&);
		template void SettingLoad<std::int8_t>(void*, sec_t, key_t, std::int8_t&, std::int8_t&);
		template void SettingLoad<std::int16_t>(void*, sec_t, key_t, std::int16_t&, std::int16_t&);
		template void SettingLoad<std::int32_t>(void*, sec_t, key_t, std::int32_t&, std::int32_t&);
		template void SettingLoad<std::string>(void*, sec_t, key_t, std::string&, std::string&);

		template <class T>
		void SettingSave<T>(
			void* a_data,
			sec_t a_section,
			key_t a_key,
			T&    a_value)
		{
			auto& file = *static_cast<CSimpleIniA*>(a_data);
			if constexpr (std::is_same_v<T, bool>) {
				file.SetBoolValue(a_section.data(), a_key.data(), a_value);
			} else if constexpr (std::is_floating_point_v<T>) {
				file.SetDoubleValue(a_section.data(), a_key.data(), a_value);
			} else if constexpr (is_long_integral_v<T>) {
				file.SetLongValue(a_section.data(), a_key.data(), a_value);
			} else if constexpr (std::is_same_v<T, std::string>) {
				file.SetValue(a_section.data(), a_key.data(), a_value.c_str());
			}
		}

		template void SettingSave<bool>(void*, sec_t, key_t, bool&);
		template void SettingSave<float>(void*, sec_t, key_t, float&);
		template void SettingSave<double>(void*, sec_t, key_t, double&);
		template void SettingSave<std::uint8_t>(void*, sec_t, key_t, std::uint8_t&);
		template void SettingSave<std::uint16_t>(void*, sec_t, key_t, std::uint16_t&);
		template void SettingSave<std::uint32_t>(void*, sec_t, key_t, std::uint32_t&);
		template void SettingSave<std::int8_t>(void*, sec_t, key_t, std::int8_t&);
		template void SettingSave<std::int16_t>(void*, sec_t, key_t, std::int16_t&);
		template void SettingSave<std::int32_t>(void*, sec_t, key_t, std::int32_t&);
		template void SettingSave<std::string>(void*, sec_t, key_t, std::string&);
	}

	void SettingStore::Load()
	{
		CSimpleIniA file;
		file.SetUnicode(true);
		file.SetQuotes(true);

		if (std::filesystem::exists(m_fileBase)) {
			file.LoadFile(m_fileBase.data());
			for (auto& setting : m_settings) {
				setting->Load(&file, true);
			}
		}

		if (std::filesystem::exists(m_fileUser)) {
			file.LoadFile(m_fileUser.data());
			for (auto& setting : m_settings) {
				setting->Load(&file, false);
			}
		}
	}

	void SettingStore::Save()
	{
		CSimpleIniA file;
		file.SetUnicode(true);
		file.SetQuotes(true);

		file.LoadFile(m_fileBase.data());
		for (auto& setting : m_settings) {
			setting->Save(&file);
		}

		file.SaveFile(m_fileBase.data());
	}
}
#endif

#ifdef REX_OPTION_JSON
#	include <nlohmann/json.hpp>

namespace REX::JSON
{
	namespace Impl
	{
		template <class T>
		void SettingLoad<T>(
			void*  a_data,
			path_t a_path,
			T&     a_value,
			T&     a_valueDefault)
		{
			const auto& json = *static_cast<nlohmann::json*>(a_data);
			if (a_path[0] == '/') {
				a_value = json.value<T>(nlohmann::json::json_pointer(a_path.data()), a_valueDefault);
			} else {
				a_value = json.value<T>(a_path, a_valueDefault);
			}
		}

		template void SettingLoad<bool>(void*, path_t, bool&, bool&);
		template void SettingLoad<float>(void*, path_t, float&, float&);
		template void SettingLoad<double>(void*, path_t, double&, double&);
		template void SettingLoad<std::uint8_t>(void*, path_t, std::uint8_t&, std::uint8_t&);
		template void SettingLoad<std::uint16_t>(void*, path_t, std::uint16_t&, std::uint16_t&);
		template void SettingLoad<std::uint32_t>(void*, path_t, std::uint32_t&, std::uint32_t&);
		template void SettingLoad<std::int8_t>(void*, path_t, std::int8_t&, std::int8_t&);
		template void SettingLoad<std::int16_t>(void*, path_t, std::int16_t&, std::int16_t&);
		template void SettingLoad<std::int32_t>(void*, path_t, std::int32_t&, std::int32_t&);
		template void SettingLoad<std::string>(void*, path_t, std::string&, std::string&);

		template <class T>
		void SettingSave<T>(
			void*  a_data,
			path_t a_path,
			T&     a_value)
		{
			auto& json = *static_cast<nlohmann::json*>(a_data);
			if (a_path[0] == '/') {
				json[nlohmann::json::json_pointer(a_path.data())] = a_value;
			} else {
				json[a_path] = a_value;
			}
		}

		template void SettingSave<bool>(void*, path_t, bool&);
		template void SettingSave<float>(void*, path_t, float&);
		template void SettingSave<double>(void*, path_t, double&);
		template void SettingSave<std::uint8_t>(void*, path_t, std::uint8_t&);
		template void SettingSave<std::uint16_t>(void*, path_t, std::uint16_t&);
		template void SettingSave<std::uint32_t>(void*, path_t, std::uint32_t&);
		template void SettingSave<std::int8_t>(void*, path_t, std::int8_t&);
		template void SettingSave<std::int16_t>(void*, path_t, std::int16_t&);
		template void SettingSave<std::int32_t>(void*, path_t, std::int32_t&);
		template void SettingSave<std::string>(void*, path_t, std::string&);
	}

	void SettingStore::Load()
	{
		if (std::filesystem::exists(m_fileBase)) {
			std::ifstream file{ m_fileBase.data() };
			try {
				auto result = nlohmann::json::parse(file);
				for (auto setting : m_settings) {
					setting->Load(&result, true);
				}
			} catch (const std::exception& e) {
				SKSE::log::error("{}", e.what());
			}
		}

		if (std::filesystem::exists(m_fileUser)) {
			std::ifstream file{ m_fileUser.data() };
			try {
				auto result = nlohmann::json::parse(file);
				for (auto setting : m_settings) {
					setting->Load(&result, false);
				}
			} catch (const std::exception& e) {
				SKSE::log::error("{}", e.what());
			}
		}
	}

	void SettingStore::Save()
	{
		nlohmann::json output{};
		if (std::filesystem::exists(m_fileBase)) {
			std::ifstream file{ m_fileBase.data() };
			output = nlohmann::json::parse(file);
		}

		for (auto& setting : m_settings) {
			setting->Save(&output);
		}

		std::ofstream file{ m_fileBase.data(), std::ios::trunc };
		file << std::setw(4) << output;
	}
}
#endif

#ifdef REX_OPTION_TOML
#	include <toml.hpp>

namespace REX::TOML
{
	namespace Impl
	{
		static toml::value* recurse_table(toml::value* a_result, toml::value& a_value, const std::string& a_section, bool a_create)
		{
			if (a_result && a_result->is_table()) {
				for (auto& value : a_result->as_table()) {
					if (value.first == a_section) {
						return std::addressof(value.second);
					}
				}
				if (a_create) {
					(*a_result)[a_section] = toml::table{};
					return std::addressof((*a_result)[a_section]);
				}
			} else if (a_value.is_table()) {
				for (auto& value : a_value.as_table()) {
					if (value.first == a_section) {
						return std::addressof(value.second);
					}
				}
				if (a_create) {
					a_value[a_section] = toml::table{};
					return std::addressof(a_value[a_section]);
				}
			}
			return a_result;
		}

		static bool recurse_mark_implicit(toml::value& a_value)
		{
			for (auto& kv : a_value.as_table()) {
				if (kv.second.is_table()) {
					if (!recurse_mark_implicit(kv.second)) {
						continue;
					}
					kv.second.as_table_fmt().fmt = toml::table_format::implicit;
				} else {
					return false;
				}
			}
			return true;
		}

		template <class T>
		void SettingLoad<T>(
			void* a_data,
			sec_t a_section,
			key_t a_key,
			T&    a_value,
			T&    a_valueDefault)
		{
			const auto& data = static_cast<toml::value*>(a_data);
			if (a_section.empty()) {
				auto& path = (*data);
				a_value = toml::find_or<T>(path, a_key.data(), a_valueDefault);
				return;
			} else if (a_section.size() == 1) {
				auto& path = (*data)[a_section.front()];
				a_value = toml::find_or<T>(path, a_key.data(), a_valueDefault);
				return;
			} else {
				toml::value* path{ nullptr };
				for (auto& section : a_section) {
					path = recurse_table(path, *data, section, false);
				}
				if (path) {
					a_value = toml::find_or<T>(*path, a_key.data(), a_valueDefault);
					return;
				}
			}
			a_value = a_valueDefault;
		}

		template void SettingLoad<bool>(void*, sec_t, key_t, bool&, bool&);
		template void SettingLoad<float>(void*, sec_t, key_t, float&, float&);
		template void SettingLoad<double>(void*, sec_t, key_t, double&, double&);
		template void SettingLoad<std::uint8_t>(void*, sec_t, key_t, std::uint8_t&, std::uint8_t&);
		template void SettingLoad<std::uint16_t>(void*, sec_t, key_t, std::uint16_t&, std::uint16_t&);
		template void SettingLoad<std::uint32_t>(void*, sec_t, key_t, std::uint32_t&, std::uint32_t&);
		template void SettingLoad<std::int8_t>(void*, sec_t, key_t, std::int8_t&, std::int8_t&);
		template void SettingLoad<std::int16_t>(void*, sec_t, key_t, std::int16_t&, std::int16_t&);
		template void SettingLoad<std::int32_t>(void*, sec_t, key_t, std::int32_t&, std::int32_t&);
		template void SettingLoad<std::string>(void*, sec_t, key_t, std::string&, std::string&);

		template <class T>
		void SettingSave<T>(
			void* a_data,
			sec_t a_section,
			key_t a_key,
			T&    a_value)
		{
			auto& data = *static_cast<toml::value*>(a_data);
			if (a_section.empty()) {
				data[a_key.data()] = a_value;
			} else if (a_section.size() == 1) {
				data[a_section.front()][a_key.data()] = a_value;
			} else {
				toml::value* path{ nullptr };
				for (auto& section : a_section) {
					path = recurse_table(path, data, section, true);
				}
				if (path) {
					(*path)[a_key.data()] = a_value;
				}
			}
		}

		template void SettingSave<bool>(void*, sec_t, key_t, bool&);
		template void SettingSave<float>(void*, sec_t, key_t, float&);
		template void SettingSave<double>(void*, sec_t, key_t, double&);
		template void SettingSave<std::uint8_t>(void*, sec_t, key_t, std::uint8_t&);
		template void SettingSave<std::uint16_t>(void*, sec_t, key_t, std::uint16_t&);
		template void SettingSave<std::uint32_t>(void*, sec_t, key_t, std::uint32_t&);
		template void SettingSave<std::int8_t>(void*, sec_t, key_t, std::int8_t&);
		template void SettingSave<std::int16_t>(void*, sec_t, key_t, std::int16_t&);
		template void SettingSave<std::int32_t>(void*, sec_t, key_t, std::int32_t&);
		template void SettingSave<std::string>(void*, sec_t, key_t, std::string&);
	}

	void SettingStore::Load()
	{
		if (auto result = toml::try_parse(m_fileBase.data()); result.is_ok()) {
			for (auto& setting : m_settings) {
				setting->Load(&result.unwrap(), true);
			}
		}

		if (auto result = toml::try_parse(m_fileUser.data()); result.is_ok()) {
			for (auto& setting : m_settings) {
				setting->Load(&result.unwrap(), false);
			}
		}
	}

	void SettingStore::Save()
	{
		toml::value output{};
		if (auto result = toml::try_parse(m_fileBase.data()); result.is_ok()) {
			output = result.unwrap();
		}

		for (auto setting : m_settings) {
			setting->Save(&output);
		}

		Impl::recurse_mark_implicit(output);
		std::ofstream file{ m_fileBase.data(), std::ios::trunc };
		file << toml::format(output);
	}
}
#endif
