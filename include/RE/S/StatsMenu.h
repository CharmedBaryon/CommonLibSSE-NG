#pragma once

#include "RE/A/ActorValues.h"
#include "RE/B/BSResourceHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"
#include "RE/M/MenuEventHandler.h"
#include "RE/N/NiPoint3.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSEffectShaderProperty;
	class BSFadeNode;
	class BSScaleformMovieLoadTask;
	class NiCamera;
	class NiControllerManager;
	class NiControllerSequence;
	class NiNode;
	class StatsNode;

	// menuDepth = 3
	// flags = kPausesGame | kUsesMenuContext | kDisablePauseMenu | kRequiresUpdate | kCustomRendering
	// kUsesCursor if gamepad disabled
	// context = kStats
	class StatsMenu :
#ifndef SKYRIM_CROSS_VR
		public IMenu,            // 000
		public MenuEventHandler  // 030, 040
#else
		public IMenu  // 000
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_StatsMenu;
		inline static constexpr auto      VTABLE = VTABLE_StatsMenu;
		constexpr static std::string_view MENU_NAME = "StatsMenu";

		enum class MenuState : std::uint32_t
		{
			kNormal = 0,
			kZoomed = 1,
			kFadeIn = 2,
			kFadeOut = 3
		};

		enum
		{
			kTotalTrees = 18
		};

		struct Models
		{
			enum Model : std::uint32_t
			{
				kSkydome,
				kStars,
				kLines,
				kTotal
			};
		};
		using Model = Models::Model;

		struct UnkData
		{
		public:
			enum class State
			{
				kResting = 0,
				kEntering = 1,
				kExiting = 2
			};

			// members
			BSEffectShaderProperty*            unk00;  // 00
			REX::EnumSet<State, std::uint32_t> state;  // 08
			std::uint32_t                      unk0C;  // 0C
		};
		static_assert(sizeof(UnkData) == 0x10);

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                                               \
	NiPointer<NiCamera>                    camera;                      /* 040 */                                          \
	float                                  horizontalVelocity;          /* 048 */                                          \
	std::uint32_t                          unk04C;                      /* 04C */                                          \
	BSTArray<ActorValue>                   skillTrees;                  /* 050 */                                          \
	ModelDBHandle                          modelHandles[Model::kTotal]; /* 068 */                                          \
	BSFadeNode*                            skydomeNode;                 /* 080 */                                          \
	BSFadeNode*                            starsNode;                   /* 088 */                                          \
	BSFadeNode*                            linesNode;                   /* 090 */                                          \
	UnkData                                unk098[kTotalTrees];         /* 098 */                                          \
	REX::EnumSet<MenuState, std::uint32_t> menuState;                   /* 1B8 */                                          \
	bool                                   scrolling;                   /* 1BC */                                          \
	std::uint8_t                           unk1BD;                      /* 1BD */                                          \
	std::uint16_t                          unk1BE;                      /* 1BE */                                          \
	std::uint32_t                          selectedTree;                /* 1C0 */                                          \
	std::uint32_t                          unk1C4;                      /* 1C4 */                                          \
	StatsNode*                             unk1C8;                      /* 1C8 */                                          \
	std::uint32_t                          unk1D0;                      /* 1D0 */                                          \
	NiPoint3                               unk1D4;                      /* 1D4 */                                          \
	std::uint64_t                          unk1E0;                      /* 1E0 */                                          \
	std::uint32_t                          unk1E8;                      /* 1E8 */                                          \
	NiPoint3                               skillsLookAt;                /* 1EC */                                          \
	NiPoint3                               starCameraOffset;            /* 1F8 */                                          \
	NiPoint3                               starLookAt;                  /* 204 */                                          \
	std::uint64_t                          unk210;                      /* 210 */                                          \
	std::uint64_t                          unk218;                      /* 218 */                                          \
	std::uint64_t                          unk220;                      /* 220 */                                          \
	std::uint64_t                          unk228;                      /* 228 */                                          \
	std::uint64_t                          unk230;                      /* 230 */                                          \
	std::uint64_t                          unk238;                      /* 238 */                                          \
	float                                  unk240;                      /* 240 */                                          \
	float                                  unk244;                      /* 244 */                                          \
	float                                  unk248;                      /* 248 */                                          \
	float                                  unk24C;                      /* 24C */                                          \
	float                                  unk250;                      /* 250 */                                          \
	float                                  unk254;                      /* 254 */                                          \
	float                                  unk258;                      /* 258 */                                          \
	float                                  unk25C;                      /* 25C */                                          \
	float                                  unk260;                      /* 260 */                                          \
	float                                  unk264;                      /* 264 */                                          \
	float                                  unk268;                      /* 268 */                                          \
	float                                  unk26C;                      /* 26C */                                          \
	float                                  unk270;                      /* 270 */                                          \
	float                                  unk274;                      /* 274 */                                          \
	std::uint32_t                          unk278;                      /* 278 */                                          \
	float                                  unk27C;                      /* 27C */                                          \
	float                                  horizontalAcceleration;      /* 280 */                                          \
	std::uint32_t                          unk284;                      /* 284 */                                          \
	NiNode*                                cameraPosition;              /* 288 */                                          \
	NiControllerSequence*                  cameraIntro;                 /* 290 */                                          \
	NiControllerSequence*                  cameraOutro;                 /* 298 */                                          \
	NiControllerSequence*                  idle;                        /* 2A0 */                                          \
	NiControllerManager*                   skydomeNodeController;       /* 2A8 */                                          \
	ImageSpaceModifierInstanceForm*        unk2B0;                      /* 2B0 - SkillMenuTransition */                    \
	ImageSpaceModifierInstanceForm*        unk2B8;                      /* 2B8 - SkillMenuIdle */                          \
	BSTArray<StatsNode*>                   unk2C0;                      /* 2C0 */                                          \
	BSTArray<GFxValue>                     unk2D8;                      /* 2D8 */                                          \
	BSScaleformMovieLoadTask*              unk2F0;                      /* 2F0 */                                          \
	GFxValue                               beastSkillHolder;            /* 2F8 - StatsMenuBaseInstance.BeastSkillHolder */ \
	std::uint32_t                          numSelectableTrees;          /* 310 */                                          \
	float                                  screenHeight;                /* 314 */                                          \
	float                                  screenWidth;                 /* 318 */                                          \
	std::uint32_t                          flags;                       /* 31C */                                          \
	std::uint8_t                           unk320;                      /* 320 */                                          \
	std::uint8_t                           unk321;                      /* 321 */                                          \
	bool                                   fadeInTriggered;             /* 322 */                                          \
	bool                                   is3dInitialized;             /* 323 */                                          \
	std::uint32_t                          unk324;                      /* 324 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x2E8);

		~StatsMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		void               Unk_03(void) override;                            // 03 - { unk321 = 1; }
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04
		void               PostDisplay() override;                           // 06

		// override (MenuEventHandler)
#ifndef SKYRIM_CROSS_VR
		bool CanProcess(InputEvent* a_event) override;  // 01
#endif
#ifdef EXCLUSIVE_SKYRIM_VR
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03
		bool ProcessButton(ButtonEvent* a_event) override;          // 05
#endif

#ifndef SKYRIM_CROSS_VR
		RUNTIME_CAST_ACCESSOR(MenuEventHandler, AsMenuEventHandler, 0x30, 0x40);
#endif

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x40, 0x50);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 40, 50
#endif
	};
	STATIC_ASSERT_SIZE(StatsMenu, 0x328, 0x328, 0x338, 0x30);
}
#undef RUNTIME_DATA_CONTENT
