#pragma once

#include "RE/I/IMessageBoxCallback.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class MapMenu;

	class FastTravelConfirmCallback : public IMessageBoxCallback
	{
	public:
		inline static constexpr auto RTTI = RTTI___FastTravelConfirmCallback;
		inline static constexpr auto VTABLE = VTABLE___FastTravelConfirmCallback;

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT       \
	RE::NiPoint3  coords; /*	20 */ \
	std::uint16_t unk2c;  /*    2c*/
			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x10);

		~FastTravelConfirmCallback() override;  // 00

		// override (IMessageBoxCallback)
		void Run(std::uint8_t a_button) override;  //01

		//members
		MapMenu*     mapMenu;     // 10
		std::int32_t cursorPosX;  // 18
		std::int32_t cursorPosY;  // 1C
#if defined(EXCLUSIVE_SKYRIM_VR)
		RUNTIME_DATA_CONTENT;
#endif
		VR_ONLY_POINTER_ACCESSOR(RUNTIME_DATA, GetRuntimeData, 0x20);
	};
	STATIC_ASSERT_SIZE(FastTravelConfirmCallback, 0x20, 0x20, 0x30);
}
#undef RUNTIME_DATA_CONTENT
