#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/I/IMenu.h"

namespace RE
{
	class HudModeChangeEvent;

	// menuDepth = 4
	// context = 22
	class WorldSpaceMenu :
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		public IMenu,                            // 00
		public BSTEventSink<HudModeChangeEvent>  // 40
#else
		public IMenu  // 00
#endif
	{
	public:
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		inline static constexpr auto RTTI = RTTI_WorldSpaceMenu;
#endif

		~WorldSpaceMenu() override;  // 00

#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		// add
		virtual void Unk_11();
		virtual void Unk_12();
		virtual void Unk_13();

		// members
		std::uint16_t unk48{ 0 };  // 40
		std::uint8_t  unk50{ 0 };  // 42
		std::uint8_t  unk51{ 0 };  // 43
		std::uint8_t  unk52{ 0 };  // 44
		std::uint8_t  pad53{ 0 };  // 45
		std::uint32_t pad54{ 0 };  // 46
#endif
	};
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(WorldSpaceMenu) == 0x58);
#endif
}
