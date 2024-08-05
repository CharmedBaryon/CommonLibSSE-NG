#pragma once

#include "RE/B/BSTArray.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"

namespace RE
{
	class BGSLocation;
	class TESLoadScreen;

	// menuDepth = 9
	// flags = kPausesGame | kAlwaysOpen | kAllowSaving | kApplicationMenu
	// context = kNone
	class LoadingMenu : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_LoadingMenu;
		inline static constexpr auto      VTABLE = VTABLE_LoadingMenu;
		constexpr static std::string_view MENU_NAME = "Loading Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                       \
	GFxValue                 root;            /* 30 - "Menu_mc" */ \
	BGSLocation*             currentLocation; /* 48 */             \
	bool                     unk50;           /* 50 */             \
	bool                     unk51;           /* 51 */             \
	std::uint16_t            pad52;           /* 52 */             \
	std::uint32_t            pad54;           /* 54 */             \
	BSTArray<TESLoadScreen*> loadScreens;     /* 58 */             \
	std::uint32_t            unk70;           /* 70 */             \
	std::uint32_t            pad74;           /* 74 */             \
	std::uint64_t            unk78;           /* 78 */

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
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 30, 40
#endif
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(LoadingMenu) == 0x80);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(LoadingMenu) == 0x90);
#else
	static_assert(sizeof(LoadingMenu) == 0x30);
#endif
}
#undef RUNTIME_DATA_CONTENT
