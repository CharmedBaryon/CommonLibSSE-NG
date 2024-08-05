#include "RE/H/hkpProperty.h"

namespace RE
{
	hkpPropertyValue::hkpPropertyValue(std::uint64_t a_value) :
		data(a_value)
	{}

	hkpPropertyValue::hkpPropertyValue(std::int32_t a_value) :
		data(a_value)
	{}

	hkpPropertyValue::hkpPropertyValue(std::uint32_t a_value) :
		data(static_cast<std::int32_t>(a_value))
	{}

	hkpPropertyValue::hkpPropertyValue(float a_value)
	{
		union
		{
			float         f;
			std::uint32_t u;
		} value{};

		value.f = a_value;
		data = value.u;
	}

	hkpPropertyValue::hkpPropertyValue(void* a_value) :
		data(reinterpret_cast<std::uint64_t>(a_value))
	{}

	float hkpPropertyValue::GetFloat() const
	{
		union
		{
			float         f;
			std::uint32_t u;
		} value{};

		value.u = static_cast<std::uint32_t>(data);
		return value.f;
	}

	void* hkpPropertyValue::GetPointer() const
	{
		return reinterpret_cast<void*>(static_cast<std::uint64_t>(data));
	}

	std::int32_t hkpPropertyValue::GetSInt() const
	{
		return static_cast<std::int32_t>(data);
	}

	std::uint32_t hkpPropertyValue::GetUInt() const
	{
		return static_cast<std::uint32_t>(data);
	}

	std::uint64_t hkpPropertyValue::GetUInt64() const
	{
		return data;
	}

	hkpProperty::hkpProperty(std::uint32_t a_key, hkpPropertyValue a_value) :
		key(a_key),
		alignmentPadding(0),
		value(a_value)
	{}
}
