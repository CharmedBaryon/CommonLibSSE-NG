#include "RE/N/NiColorData.h"

namespace RE
{
	std::uint32_t NiColorData::GetNumKeys() const
	{
		return numKeys;
	}

	NiColorKey* NiColorData::GetAnim(std::uint32_t& a_numKeys, KeyType& a_type, std::uint8_t& a_size) const
	{
		a_numKeys = numKeys;
		a_type = type;
		a_size = keySize;
		return keys;
	}
}
