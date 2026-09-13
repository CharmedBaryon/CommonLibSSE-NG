#pragma once

#include "RE/N/NiExtraData.h"

namespace RE
{
	class NiBinaryExtraData : public NiExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiBinaryExtraData;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiBinaryExtraData;
		inline static constexpr auto VTABLE = VTABLE_NiBinaryExtraData;

		static NiBinaryExtraData* Create(std::string_view a_name, const std::uint8_t* a_data, std::uint32_t a_size);

		std::uint8_t* data;  // 18
		std::uint32_t size;  // 20
	};
	static_assert(sizeof(NiBinaryExtraData) == 0x28);
}
