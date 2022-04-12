#pragma once

#include "RE/B/BSTArray.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"

namespace RE
{
	// menuDepth = 9
	// flags = kPausesGame | kAlwaysOpen | kAllowSaving | kApplicationMenu
	// context = kNone
	class LoadingMenu : public IMenu
	{
	public:
		inline static auto                RTTI = RTTI_LoadingMenu;
		constexpr static std::string_view MENU_NAME = "Loading Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                    \
	GFxValue        root;  /* 00 - "Menu_mc" */ \
	std::uint64_t   unk48; /* 18 */             \
	std::uint8_t    unk50; /* 20 */             \
	std::uint8_t    unk51; /* 21 */             \
	std::uint16_t   pad52; /* 22 */             \
	std::uint32_t   pad54; /* 24 */             \
	BSTArray<void*> unk58; /* 28 */             \
	std::uint32_t   unk70; /* 40 */             \
	std::uint32_t   pad74; /* 44 */             \
	std::uint64_t   unk78; /* 48 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x50);

		~LoadingMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x30, 0x40);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x30, 0x40);
		}

		// members
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		RUNTIME_DATA_CONTENT  // 30, 40
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(LoadingMenu) == 0x80);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(LoadingMenu) == 0x90);
#endif
}
#undef RUNTIME_DATA_CONTENT
