#include "RE/S/Setting.h"

namespace RE
{
	Setting::~Setting()
	{
		if (IsManaged()) {
			free(name);
			free(data.s);
		}
		name = nullptr;
		data.s = nullptr;
	}

	bool Setting::IsPreferenceSetting() const
	{
		return false;
	}

	Setting::Setting(const std::string& name)
	{
		auto charlen = strlen(name.c_str()) + 1;
		this->name = new char[charlen];
		strcpy_s(this->name, charlen, name.c_str());
	}

	Setting::Setting(const std::string& name, bool value) :
		Setting(name)
	{
		this->data.b = value;
	}

	Setting::Setting(const std::string& name, const std::string& value) :
		Setting(name)
	{
		auto charlen = strlen(value.c_str()) + 1;
		this->data.s = new char[charlen];
		strcpy_s(this->data.s, charlen, value.c_str());
	}

	Setting::Setting(const std::string& name, float value) :
		Setting(name)
	{
		this->data.f = value;
	}

	Setting::Setting(const std::string& name, std::int8_t value) :
		Setting(name)
	{
		this->data.c = value;
	}

	Setting::Setting(const std::string& name, std::int32_t value) :
		Setting(name)
	{
		this->data.i = value;
	}

	Setting::Setting(const std::string& name, std::uint8_t value) :
		Setting(name)
	{
		this->data.h = value;
	}

	Setting::Setting(const std::string& name, std::uint32_t value) :
		Setting(name)
	{
		this->data.u = value;
	}

	bool Setting::IsManaged() const
	{
		return name && name[0] == 'S';
	}

	auto Setting::GetType() const
		-> Type
	{
		if (!name) {
			return Type::kUnknown;
		} else {
			switch (name[0]) {
			case 'b':
				return Type::kBool;
			case 'c':
				return Type::kCharacter;
			case 'h':
				return Type::kUnsignedCharacter;
			case 'f':
				return Type::kFloat;
			case 'i':
				return Type::kInteger;
			case 'r':
				return Type::kColorRGB;
			case 'a':
				return Type::kColorRGBA;
			case 'S':
			case 's':
				return Type::kString;
			case 'u':
				return Type::kUnsignedInteger;
			default:
				return Type::kUnknown;
			}
		}
	}

	const char* Setting::GetName() const
	{
		return name ? name : "";
	}

	bool Setting::GetBool() const
	{
		return this->data.b;
	}

	std::int8_t Setting::GetCharacter() const
	{
		return this->data.c;
	}

	float Setting::GetFloat() const
	{
		return this->data.f;
	}

	std::int32_t Setting::GetInteger() const
	{
		return this->data.i;
	}

	const char* Setting::GetString() const
	{
		return this->data.s;
	}

	std::uint8_t Setting::GetUnsignedCharacter() const
	{
		return this->data.h;
	}

	std::uint32_t Setting::GetUnsignedInteger() const
	{
		return this->data.u;
	}

	std::uint32_t Setting::GetColor() const
	{
		return this->data.r;
	}

	std::uint32_t Setting::GetColorA() const
	{
		return this->data.a;
	}

	void Setting::SetBool(bool value)
	{
		this->data.b = value;
	}

	void Setting::SetCharacter(std::int8_t value)
	{
		this->data.c = value;
	}

	void Setting::SetFloat(float value)
	{
		this->data.f = value;
	}

	void Setting::SetInteger(std::int32_t value)
	{
		this->data.i = value;
	}

	void Setting::SetString(const std::string& value)
	{
		if (data.s) {
			free(data.s);
			data.s = nullptr;
		}

		auto charlen = strlen(value.c_str()) + 1;
		this->data.s = new char[charlen];
		strcpy_s(this->data.s, charlen, value.c_str());
	}

	void Setting::SetUnsignedCharacter(std::uint8_t value)
	{
		this->data.h = value;
	}

	void Setting::SetUnsignedInteger(std::uint32_t value)
	{
		this->data.u = value;
	}

	void Setting::SetColor(std::uint32_t value)
	{
		this->data.r = value;
	}

	void Setting::SetColorA(std::uint32_t value)
	{
		this->data.a = value;
	}
}
