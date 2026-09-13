#pragma once

#include "RE/N/NiTriBasedGeomData.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class NiTriShapeData : public NiTriBasedGeomData
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiTriShapeData;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiTriShapeData;
		inline static constexpr auto VTABLE = VTABLE_NiTriShapeData;

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT               \
	std::uint32_t  triListLength; /* 00 */ \
	std::uint16_t* triList;       /* 08 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x10);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x70, 0x88);

#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 70, 88 - triListLength is triangle count * 3, not the count itself
#endif
	};
	STATIC_ASSERT_SIZE(NiTriShapeData, 0x80, 0x80, 0x98, 0x68);
}
#undef RUNTIME_DATA_CONTENT
