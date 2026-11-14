#pragma once

#include "RE/S/Setting.h"

namespace RE
{
	// auto registers/unregisters with the templated collection
	template <class T>
	class SettingT : public Setting
	{
	public:
		// Override
		virtual ~SettingT() override = default;  // 0

		SettingT() = delete;
		SettingT(const SettingT&) = delete;
		SettingT(SettingT&&) = delete;

		SettingT& operator=(const SettingT&) = delete;
		SettingT& operator=(SettingT&&) = delete;

		SettingT(const char* name, bool value) :
			Setting(name, value)
		{
		}

		SettingT(const char* name, const char* value) :
			Setting(name, value)
		{
		}

		SettingT(const char* name, float value) :
			Setting(name, value)
		{
		}

		SettingT(const char* name, std::int8_t value) :
			Setting(name, value)
		{
		}

		SettingT(const char* name, std::int32_t value) :
			Setting(name, value)
		{
		}

		SettingT(const char* name, std::uint8_t value) :
			Setting(name, value)
		{
		}

		SettingT(const char* name, std::uint32_t value) :
			Setting(name, value)
		{
		}
	};
	static_assert(sizeof(SettingT<void>) == 0x18);
}
