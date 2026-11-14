#pragma once

#include "RE/I/IUIMessageData.h"

namespace RE
{
	class ModManagerData : public IUIMessageData
	{
	public:
		inline static constexpr auto             RTTI = RTTI_ModManagerData;
		inline static constexpr auto             VTABLE = VTABLE_ModManagerData;
		inline static constexpr std::string_view CLASS_NAME = "ModManagerData";

		// override (IUIMessageData)
		virtual ~ModManagerData() = default;  // 00

		// members
		bool          useTransparentBackground;  // 10
		std::uint8_t  pad11;                     // 11
		std::uint16_t pad12;                     // 12
		std::uint32_t pad14;                     // 14
	};
	static_assert(sizeof(ModManagerData) == 0x18);
}
