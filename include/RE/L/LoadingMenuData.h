#pragma once

#include "RE/I/IUIMessageData.h"

namespace RE
{
	class BGSLocation;

	class LoadingMenuData : public IUIMessageData
	{
	public:
		inline static constexpr auto             RTTI = RTTI_LoadingMenuData;
		inline static constexpr auto             VTABLE = VTABLE_LoadingMenuData;
		inline static constexpr std::string_view CLASS_NAME = "LoadingMenuData";

		// override (IUIMessageData)
		~LoadingMenuData() override;  // 00

		// members
		BGSLocation*  currentLocation;  // 10
		bool          unk18;            // 18
		std::uint8_t  pad19;            // 19
		std::uint16_t pad1A;            // 1A
	};
	static_assert(sizeof(LoadingMenuData) == 0x20);
}
