#pragma once

#include "RE/I/IMenu.h"
#include "RE/M/MenuEventHandler.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiMatrix3.h"
#include "RE/S/SimpleAnimationGraphManagerHolder.h"

namespace RE
{
	class BSLightingShaderProperty;
	class NiAVObject;
	class NiControllerManager;
	class NiControllerSequence;

	struct ImageSpaceBaseData;

	// menuDepth = 8
	// flags = kDisablePauseMenu | kAllowSaving | kDontHideCursorWhenTopmost
	// context = kNone
	class MistMenu :
#ifndef SKYRIM_CROSS_VR
		public IMenu,                              // 00
		public SimpleAnimationGraphManagerHolder,  // 30, 40
		public MenuEventHandler                    // 48, 58
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_MistMenu;
		inline static constexpr auto      VTABLE = VTABLE_MistMenu;
		constexpr static std::string_view MENU_NAME = "Mist Menu";

		struct Colors
		{
			enum Color
			{
				kXNeg,
				kXPos,
				kYNeg,
				kYPos,
				kZNeg,
				kZPos,

				kTotal
			};
		};

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                            \
	NiColor                         ambientColors[Colors::kTotal]; /* 058 */                            \
	std::uint32_t                   unk0A0;                        /* 0A0 */                            \
	std::uint32_t                   unk0A4;                        /* 0A4 */                            \
	std::uint64_t                   unk0A8;                        /* 0A8 */                            \
	NiPointer<NiNode>               mistModel;                     /* 0B0 - smart ptr */                \
	void*                           mistModelDBHandle;             /* 0B8 */                            \
	void*                           loadScreenDBHandle;            /* 0C0 */                            \
	NiPointer<BSFadeNode>           cameraPath;                    /* 0C8 - parent of cameraPathNode */ \
	NiPointer<NiNode>               cameraPathNode;                /* 0D0 - smart ptr */                \
	NiPointer<NiControllerSequence> cameraPathSequence;            /* 0D8 - smart ptr */                \
	NiPointer<NiControllerManager>  cameraPathController;          /* 0E0 - smart ptr */                \
	BSLightingShaderProperty*       logoShaderProperty;            /* 0E8 - default logo only */        \
	NiPointer<BSFadeNode>           loadScreenModel;               /* 0F0 */                            \
	ImageSpaceBaseData*             originalImageSpace;            /* 0F8 - imagespacedata? */          \
	float                           cameraFOV;                     /* 100 */                            \
	float                           angleZ;                        /* 104 */                            \
	float                           unk108;                        /* 108 */                            \
	float                           unk10C;                        /* 10C */                            \
	NiMatrix3                       cameraRotate;                  /* 110 */                            \
	bool                            showMist;                      /* 134 */                            \
	bool                            showLoadScreen;                /* 135 */                            \
	std::uint8_t                    unk136;                        /* 136 */                            \
	std::uint8_t                    unk137;                        /* 137 */                            \
	std::uint8_t                    unk138;                        /* 138 - initCameraPath? */          \
	std::uint8_t                    unk139;                        /* 139 - cameraPath related */       \
	bool                            leftButtonHeldDown;            /* 13A */                            \
	bool                            rightButtonHeldDown;           /* 13B */                            \
	std::uint32_t                   pad13C;                        /* 13C */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0xE8);

		~MistMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;                         // 04
		void               AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;  // 05
		void               PostDisplay() override;                                                // 06

		// override (MenuEventHandler)
#ifndef SKYRIM_CROSS_VR
		bool CanProcess(InputEvent* a_event) override;              // 01
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03
		bool ProcessMouseMove(MouseMoveEvent* a_event) override;    // 04
		bool ProcessButton(ButtonEvent* a_event) override;          // 05
#endif

		[[nodiscard]] SimpleAnimationGraphManagerHolder* AsSimpleAnimationGraphManagerHolder() noexcept
		{
			return &REL::RelocateMember<SimpleAnimationGraphManagerHolder>(this, 0x30, 0x40);
		}

		[[nodiscard]] const SimpleAnimationGraphManagerHolder* AsSimpleAnimationGraphManagerHolder() const noexcept
		{
			return const_cast<MistMenu*>(this)->AsSimpleAnimationGraphManagerHolder();
		}

		[[nodiscard]] MenuEventHandler* AsMenuEventHandler() noexcept
		{
			return &REL::RelocateMember<MenuEventHandler>(this, 0x48, 0x58);
		}

		[[nodiscard]] const MenuEventHandler* AsMenuEventHandler() const noexcept
		{
			return const_cast<MistMenu*>(this)->AsMenuEventHandler();
		}

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x58, 0x68);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x58, 0x68);
		}

		[[nodiscard]] static MistMenu* GetSingleton()
		{
			REL::Relocation<MistMenu**> singleton{ RELOCATION_ID(519827, 406370) };
			return *singleton;
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 58, 68
#endif
	private:
		KEEP_FOR_RE()
	};
#if !defined(ENABLE_SKYRIM_VR)
#	ifdef ENABLE_SKYRIM_AE
	static_assert(sizeof(MistMenu) == 0x150);
#	else
	static_assert(sizeof(MistMenu) == 0x140);
#	endif
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(MistMenu) == 0x150);
#endif
}
#undef RUNTIME_DATA_CONTENT
