#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"

namespace RE
{
	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0)
	class hkbSymbolIdMap : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbSymbolIdMap;
		inline static constexpr auto VTABLE = VTABLE_hkbSymbolIdMap;

		// members
		hkArray<std::int32_t> internalToExternalMap;        // 10
		std::uint8_t          externalToInternalMap[0x10];  // 20 - hkMap<int32_t, int32_t>, not modeled as a generic type here
	};
	static_assert(offsetof(hkbSymbolIdMap, internalToExternalMap) == 0x10);
	static_assert(offsetof(hkbSymbolIdMap, externalToInternalMap) == 0x20);
	static_assert(sizeof(hkbSymbolIdMap) == 0x30);
}
