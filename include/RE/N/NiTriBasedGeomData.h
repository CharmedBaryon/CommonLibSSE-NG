#pragma once

#include "RE/N/NiGeometryData.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class NiTriBasedGeomData : public NiGeometryData
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiTriBasedGeomData;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiTriBasedGeomData;
		inline static constexpr auto VTABLE = VTABLE_NiTriBasedGeomData;

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                \
	std::uint16_t numTriangles;    /* 00 */ \
	std::uint16_t activeTriangles; /* 02 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x4);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x68, 0x80);

#ifndef SKYRIM_CROSS_VR
#	ifdef EXCLUSIVE_SKYRIM_VR
		std::uint8_t unk68_vrOnly[0x18];  // 68 - VR-only, content not yet identified
#	endif
		RUNTIME_DATA_CONTENT;  // 68, 80
#endif
	};
	STATIC_ASSERT_SIZE(NiTriBasedGeomData, 0x70, 0x70, 0x88, 0x68);
}
#undef RUNTIME_DATA_CONTENT
