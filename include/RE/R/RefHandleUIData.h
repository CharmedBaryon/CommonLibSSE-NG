#pragma once

#include "RE/I/IUIMessageData.h"

namespace RE
{
	class RefHandleUIData : public IUIMessageData
	{
	public:
		inline static constexpr auto             RTTI = RTTI_RefHandleUIData;
		inline static constexpr auto             VTABLE = VTABLE_RefHandleUIData;
		inline static constexpr std::string_view CLASS_NAME = "RefHandleUIData";

		// override (IUIMessageData)
		virtual ~RefHandleUIData() = default;  // 00

		// members
		RefHandle     data;   // 10
		std::uint32_t pad0C;  // 14
	};
	static_assert(sizeof(RefHandleUIData) == 0x18);
}
