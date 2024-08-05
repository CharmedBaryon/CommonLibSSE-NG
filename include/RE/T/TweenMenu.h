#pragma once

#include "RE/B/BSTArray.h"
#include "RE/I/IMenu.h"

namespace RE
{
	namespace BSResource
	{
		struct ID;
	}

	// menuDepth = 0
	// flags = kPausesGame | kUpdateUsesCursor | kAllowSaving | kDontHideCursorWhenTopmost | kCustomRendering
	// context = kMenuMode
	class TweenMenu : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_TweenMenu;
		constexpr static std::string_view MENU_NAME = "TweenMenu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT              \
	BSTArray<PerkData> perkData; /* 00 */ \
	float              unk48;    /* 18 */ \
	float              unk4C;    /* 1C */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x20);

		struct PerkData
		{
		public:
			// members
			BSResource::ID* fileHash;  // 00
			const char*     fileName;  // 08
		};
		static_assert(sizeof(PerkData) == 0x10);

		~TweenMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04
		void               PostDisplay() override;                           // 06

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
	static_assert(sizeof(TweenMenu) == 0x50);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(TweenMenu) == 0x60);
#else
	static_assert(sizeof(TweenMenu) == 0x30);
#endif
}
#undef RUNTIME_DATA_CONTENT
