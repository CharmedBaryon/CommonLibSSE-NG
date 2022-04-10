#pragma once

#include "RE/I/IMenu.h"
#include "RE/M/MenuEventHandler.h"
#include "RE/R/RaceSexCamera.h"
#include "RE/S/Sexes.h"

namespace RE
{
	// menuDepth = 3
	// flags = kPausesGame | kUsesMenuContext | kRequiresUpdate | kTopmostRenderedMenu | kUpdateUsesCursor
	// context = kItemMenu
	class RaceSexMenu :
		public IMenu,            // 00
		public MenuEventHandler  // 30
	{
	public:
		inline static auto                RTTI = RTTI_RaceSexMenu;
		constexpr static std::string_view MENU_NAME = "RaceSex Menu";

		struct RUNTIME_DATA
		{
			BSTArray<void*>                      unk040[7];  // 000
			RaceSexCamera                        camera;     // 0A8
			BSTArray<void*>                      unk140[2];  // 100
			BSTArray<void*>                      unk170;     // 130
			std::uint64_t                        unk188;     // 148
			std::uint32_t                        unk190;     // 150
			std::uint32_t                        unk194;     // 154
			stl::enumeration<SEX, std::uint32_t> sex;        // 158
			std::uint16_t                        unk19C;     // 15C
			std::uint8_t                         unk19E;     // 15E
			std::uint8_t                         pad19F;     // 15F
			std::uint8_t                         unk1A0;     // 160
			std::uint8_t                         unk1A1;     // 161
			std::uint16_t                        unk1A2;     // 162
			std::uint32_t                        unk1A4;     // 164
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x168);

		~RaceSexMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;                       // 01
		void               PostCreate() override;                                                 // 02
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;                         // 04
		void               AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;  // 05

		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override = 0;          // 01
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03
		bool ProcessMouseMove(MouseMoveEvent* a_event) override;    // 04
		bool ProcessButton(ButtonEvent* a_event) override;          // 05

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x40, 0x50);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x40, 0x50);
		}

		// members
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		RUNTIME_DATA runtimeData; // 40, 50
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(RaceSexMenu) == 0x1A8);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(RaceSexMenu) == 0x1B8);
#endif
}
