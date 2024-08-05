#pragma once

#include "RE/I/IMessageBoxCallback.h"

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
		void Run(Message a_msg) override;  //01

		//members
		MapMenu*     mapMenu;     // 10
		std::int32_t cursorPosX;  // 18
		std::int32_t cursorPosY;  // 1C
#if defined(EXCLUSIVE_SKYRIM_VR)
		RUNTIME_DATA_CONTENT;
#endif
		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0, 0x20);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0, 0x20);
		}

	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(FastTravelConfirmCallback) == 0x30);
#else
	static_assert(sizeof(FastTravelConfirmCallback) == 0x20);
#endif
}
#undef RUNTIME_DATA_CONTENT
