#include "RE/N/NiStringsExtraData.h"

#include "RE/N/NiTCollection.h"

namespace RE
{
	void NiStringsExtraData::copy_string(char*& a_value, const BSFixedString& a_string)
	{
		std::size_t strLen = a_string.length() + 1;
		a_value = NiAlloc<char>(strLen);
		std::memcpy(a_value, a_string.c_str(), sizeof(char) * strLen);
	}

	void NiStringsExtraData::copy_string(char*& a_value, char* a_copyValue)
	{
		std::size_t strLen = std::strlen(a_copyValue) + 1;
		a_value = NiAlloc<char>(strLen);
		std::memcpy(a_value, a_copyValue, sizeof(char) * strLen);
	}

	NiStringsExtraData* NiStringsExtraData::Create(const BSFixedString& a_name, const std::vector<BSFixedString>& a_strings)
	{
		auto data = NiExtraData::Create<NiStringsExtraData>();
		if (data) {
			data->name = a_name;
			data->size = static_cast<std::uint32_t>(a_strings.size());
			data->value = NiAlloc<char*>(data->size);

			for (std::uint32_t i = 0; i < data->size; ++i) {
				if (const auto string = a_strings[i]; !string.empty()) {
					copy_string(data->value[i], string);
				}
			}
		}

		return data;
	}

	std::optional<std::uint32_t> NiStringsExtraData::GetIndex(const BSFixedString& a_element) const
	{
		if (value) {
			for (std::uint32_t i = 0; i < size; ++i) {
				if (a_element == value[i]) {
					return i;
				}
			}
		}
		return std::nullopt;
	}

	bool NiStringsExtraData::Insert(const BSFixedString& a_element)
	{
		if (!a_element.empty() && !GetIndex(a_element)) {
			auto oldValue = value;

			value = NiAlloc<char*>(++size);

			if (oldValue) {
				for (std::uint32_t i = 0; i < size - 1; ++i) {
					copy_string(value[i], oldValue[i]);

					NiFree(oldValue[i]);
				}
				NiFree(oldValue);
			}

			copy_string(value[size - 1], a_element);

			return true;
		}

		return false;
	}

	bool NiStringsExtraData::Remove(const BSFixedString& a_element)
	{
		if (auto index = GetIndex(a_element); index && !a_element.empty()) {
			auto oldValue = value;

			value = NiAlloc<char*>(--size);

			for (std::uint32_t i = 0; i < size + 1; ++i) {
				if (i != *index) {
					copy_string(value[i], oldValue[i]);
				}
				NiFree(oldValue[i]);
			}
			NiFree(oldValue);

			return true;
		}

		return false;
	}

	bool NiStringsExtraData::Replace(const BSFixedString& a_from, const BSFixedString& a_to)
	{
		if (auto index = GetIndex(a_from); index && !a_to.empty()) {
			NiFree(value[*index]);
			copy_string(value[*index], a_to);

			return true;
		}

		return false;
	}
}
