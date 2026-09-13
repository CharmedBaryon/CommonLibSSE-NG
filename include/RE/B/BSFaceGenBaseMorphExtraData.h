#pragma once

#include "RE/N/NiExtraData.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSFaceGenBaseMorphExtraData : public NiExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSFaceGenBaseMorphExtraData;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSFaceGenBaseMorphExtraData;
		inline static constexpr auto VTABLE = VTABLE_BSFaceGenBaseMorphExtraData;

		NiPoint3*     vertexData;        // 18 - allocated using modelVertexCount, not vertexCount
		std::uint32_t modelVertexCount;  // 20
		std::uint32_t vertexCount;       // 24 - a distinct count used by other consumers
	};
	static_assert(sizeof(BSFaceGenBaseMorphExtraData) == 0x28);
}
