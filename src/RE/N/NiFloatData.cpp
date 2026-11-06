#include "RE/N/NiFloatData.h"

namespace RE
{
	NiFloatData* NiFloatData::Create()
	{
		using func_t = decltype(&NiFloatData::Create);
		static REL::Relocation<func_t> func{ RELOCATION_ID(71069, 72667) };
		return func();
	}

	std::uint32_t NiFloatData::GetNumKeys() const
	{
		return numKeys;
	}

	NiFloatKey* NiFloatData::GetAnim(std::uint32_t& a_numKeys, KeyType& a_type, std::uint8_t& a_size) const
	{
		a_numKeys = numKeys;
		a_type = type;
		a_size = keySize;
		return keys;
	}

	void NiFloatData::ReplaceAnim(NiFloatKey* a_keys, std::uint32_t a_numKeys, KeyType a_type)
	{
		using func_t = decltype(&NiFloatData::ReplaceAnim);
		static REL::Relocation<func_t> func{ RELOCATION_ID(71071, 72669) };
		return func(this, a_keys, a_numKeys, a_type);
	}
}
