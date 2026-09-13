#pragma once

#include "RE/N/NiTriBasedGeomData.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class NiTriStripsData : public NiTriBasedGeomData
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiTriStripsData;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiTriStripsData;
		inline static constexpr auto VTABLE = VTABLE_NiTriStripsData;

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT              \
	std::uint16_t  numStrips;    /* 00 */ \
	std::uint16_t* stripLengths; /* 08 */ \
	std::uint16_t* stripLists;   /* 10 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x18);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x70, 0x88);

#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 70, 88
#endif
	};
	STATIC_ASSERT_SIZE(NiTriStripsData, 0x88, 0x88, 0xA0, 0x68);
}
#undef RUNTIME_DATA_CONTENT
