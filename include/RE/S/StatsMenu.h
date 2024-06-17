#pragma once

#include "RE/A/ActorValues.h"
#include "RE/B/BSTArray.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"
#include "RE/M/MenuEventHandler.h"
#include "RE/N/NiPoint3.h"

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

	namespace BSResource
	{
		struct ID;
	}

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
		constexpr static std::string_view MENU_NAME = "StatsMenu";

		enum
		{
			kTotalTrees = 18
		};

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
			BSEffectShaderProperty*                unk00;  // 00
			stl::enumeration<State, std::uint32_t> state;  // 08
			std::uint32_t                          unk0C;  // 0C
		};
		static_assert(sizeof(UnkData) == 0x10);

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                             \
	NiCamera*                 unk040;                 /* 000 */                                          \
	float                     horizontalVelocity;     /* 008 */                                          \
	std::uint32_t             unk04C;                 /* 00C */                                          \
	BSTArray<ActorValue>      skillTrees;             /* 010 */                                          \
	BSResource::ID*           skydomeHash;            /* 028 */                                          \
	BSResource::ID*           starsHash;              /* 030 */                                          \
	BSResource::ID*           linesHash;              /* 038 */                                          \
	BSFadeNode*               skydomeNode;            /* 040 */                                          \
	BSFadeNode*               starsNode;              /* 048 */                                          \
	BSFadeNode*               linesNode;              /* 050 */                                          \
	UnkData                   unk098[kTotalTrees];    /* 058 */                                          \
	bool                      zoomed;                 /* 178 */                                          \
	std::uint8_t              unk1B9;                 /* 179 */                                          \
	std::uint16_t             unk1BA;                 /* 17A */                                          \
	bool                      scrolling;              /* 17C */                                          \
	std::uint8_t              unk1BD;                 /* 17D */                                          \
	std::uint16_t             unk1BE;                 /* 17E */                                          \
	std::uint32_t             selectedTree;           /* 180 */                                          \
	std::uint32_t             unk1C4;                 /* 184 */                                          \
	StatsNode*                unk1C8;                 /* 188 */                                          \
	std::uint32_t             unk1D0;                 /* 190 */                                          \
	std::uint32_t             unk1D4;                 /* 194 */                                          \
	std::uint32_t             unk1D8;                 /* 198 */                                          \
	std::uint32_t             unk1DC;                 /* 19C */                                          \
	std::uint64_t             unk1E0;                 /* 1A0 */                                          \
	std::uint32_t             unk1E8;                 /* 1A8 */                                          \
	NiPoint3                  skillsLookAt;           /* 1AC */                                          \
	NiPoint3                  starCameraOffset;       /* 1B8 */                                          \
	NiPoint3                  starLookAt;             /* 0C4 */                                          \
	std::uint64_t             unk210;                 /* 0D0 */                                          \
	std::uint64_t             unk218;                 /* 0D8 */                                          \
	std::uint64_t             unk220;                 /* 0E0 */                                          \
	std::uint64_t             unk228;                 /* 0E8 */                                          \
	std::uint64_t             unk230;                 /* 0F0 */                                          \
	std::uint64_t             unk238;                 /* 0F8 */                                          \
	float                     unk240;                 /* 200 */                                          \
	float                     unk244;                 /* 204 */                                          \
	float                     unk248;                 /* 208 */                                          \
	float                     unk24C;                 /* 20C */                                          \
	float                     unk250;                 /* 210 */                                          \
	float                     unk254;                 /* 214 */                                          \
	float                     unk258;                 /* 218 */                                          \
	float                     unk25C;                 /* 21C */                                          \
	float                     unk260;                 /* 220 */                                          \
	float                     unk264;                 /* 224 */                                          \
	float                     unk268;                 /* 228 */                                          \
	float                     unk26C;                 /* 22C */                                          \
	float                     unk270;                 /* 230 */                                          \
	float                     unk274;                 /* 234 */                                          \
	std::uint32_t             unk278;                 /* 238 */                                          \
	float                     unk27C;                 /* 23C */                                          \
	float                     horizontalAcceleration; /* 240 */                                          \
	std::uint32_t             unk284;                 /* 244 */                                          \
	NiNode*                   cameraPosition;         /* 248 */                                          \
	NiControllerSequence*     cameraIntro;            /* 250 */                                          \
	NiControllerSequence*     cameraOutro;            /* 258 */                                          \
	NiControllerSequence*     idle;                   /* 260 */                                          \
	NiControllerManager*      unk2A8;                 /* 268 */                                          \
	std::uint64_t             unk2B0;                 /* 270 */                                          \
	std::uint64_t             unk2B8;                 /* 278 */                                          \
	BSTArray<StatsNode*>      unk2C0;                 /* 280 */                                          \
	BSTArray<GFxValue>        unk2D8;                 /* 298 */                                          \
	BSScaleformMovieLoadTask* unk2F0;                 /* 2B0 */                                          \
	GFxValue                  unk2F8;                 /* 2B8 - StatsMenuBaseInstance.BeastSkillHolder */ \
	std::uint32_t             numSelectableTrees;     /* 2D0 */                                          \
	float                     unk314;                 /* 2D4 */                                          \
	float                     unk318;                 /* 2D8 */                                          \
	std::uint32_t             flags;                  /* 2DC */                                          \
	std::uint8_t              unk320;                 /* 2E0 */                                          \
	std::uint8_t              unk321;                 /* 2E1 */                                          \
	std::uint16_t             unk322;                 /* 2E2 */                                          \
	std::uint32_t             unk324;                 /* 2E4 */

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
		bool CanProcess(InputEvent* a_event) override;              // 01
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03
		bool ProcessButton(ButtonEvent* a_event) override;          // 05
#endif

		[[nodiscard]] MenuEventHandler* AsMenuEventHandler() noexcept
		{
			return &REL::RelocateMember<MenuEventHandler>(this, 0x30, 0x40);
		}

		[[nodiscard]] const MenuEventHandler* AsMenuEventHandler() const noexcept
		{
			return const_cast<StatsMenu*>(this)->AsMenuEventHandler();
		}

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x40, 0x50);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x40, 0x50);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 40, 50
#endif
	private:
		KEEP_FOR_RE()
	};
#if !defined(ENABLE_SKYRIM_VR)
#	ifdef ENABLE_SKYRIM_AE
	static_assert(sizeof(StatsMenu) == 0x338);
#	else
	static_assert(sizeof(StatsMenu) == 0x328);
#	endif
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(StatsMenu) == 0x338);
#endif
}
#undef RUNTIME_DATA_CONTENT
