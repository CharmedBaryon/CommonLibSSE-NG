#pragma once

#include "RE/I/IUIMessageData.h"

namespace RE
{
	class TESForm;

	class TESFormUIData : public RE::IUIMessageData
	{
	public:
		inline static constexpr auto             RTTI = RTTI_TESFormUIData;
		inline static constexpr std::string_view CLASS_NAME = "TESFormUIData"sv;

		// members
		TESForm* data;  // 10
	};
	static_assert(sizeof(TESFormUIData) == 0x18);
}
