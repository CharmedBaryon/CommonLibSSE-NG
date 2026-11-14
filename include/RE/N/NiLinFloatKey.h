#pragma once

#include "RE/N/NiFloatKey.h"

namespace RE
{
	class NiLinFloatKey : public NiFloatKey
	{
	public:
		// engine-allocated, freed by NiFloatData's key delete function for kLink
		static NiLinFloatKey* CreateArray(std::uint32_t a_count)
		{
			using func_t = decltype(&NiLinFloatKey::CreateArray);
			static REL::Relocation<func_t> func{ RELOCATION_ID(72540, 74222) };
			return func(a_count);
		}
	};
	static_assert(sizeof(NiLinFloatKey) == 0x8);
}
