#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTSingleton.h"

namespace RE
{
	class InterfaceStrings : public BSTSingletonSDM<InterfaceStrings>
	{
	public:
		static InterfaceStrings* GetSingleton();

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                       \
	BSFixedString creationClubMenu;        /* 198 - "Creation Club Menu */         \
	BSFixedString titleSequenceMenu;       /* 1A8 - "TitleSequence Menu */         \
	BSFixedString consoleNativeUIMenu;     /* 1B0 - "Console Native UI Menu */     \
	BSFixedString kinectMenu;              /* 1B8 - "Kinect Menu */                \
	BSFixedString loadWaitSpinner;         /* 1C0 - "LoadWaitSpinner */            \
	BSFixedString streamingInstallMenu;    /* 1C8 - "StreamingInstallMenu */       \
	BSFixedString textWidget;              /* 1D0 - "TextWidget */                 \
	BSFixedString buttonBarWidget;         /* 1D8 - "ButtonBarWidget */            \
	BSFixedString graphWidget;             /* 1E0 - "GraphWidget */                \
	BSFixedString textureWidget;           /* 1E8 - "TextureWidget */              \
	BSFixedString uiMenuOK;                /* 1F0 - "UIMenuOK */                   \
	BSFixedString uiMenuCancel;            /* 1F8 - "UIMenuCancel */               \
	BSFixedString showText;                /* 200 - "Show Text */                  \
	BSFixedString hideText;                /* 208 - "Hide Text */                  \
	BSFixedString showList;                /* 210 - "Show List */                  \
	BSFixedString voiceReady;              /* 218 - "Voice Ready */                \
	BSFixedString dmfoStr;                 /* 220 - "DMFOStr */                    \
	BSFixedString showJournal;             /* 228 - "Show Journal */               \
	BSFixedString journalSettingsSaved;    /* 230 - "Journal Settings Saved */     \
	BSFixedString closeMenu;               /* 238 - "CloseMenu */                  \
	BSFixedString closingAllMenus;         /* 240 - "Closing All Menus */          \
	BSFixedString refreshMenu;             /* 248 - "RefreshMenu */                \
	BSFixedString cancelLoading;           /* 250 - "CancelLoading */              \
	BSFixedString menuTextureDegradeEvent; /* 258 - "Menu Texture Degrade Event */ \
	BSFixedString diamondMarker;           /* 270 - "<img src='DiamondMarker' width='10' height='15' align='baseline' vspace='5 */

			RUNTIME_DATA_CONTENT
		};

		struct AE_RUNTIME_DATA
		{
#define AE_RUNTIME_DATA_CONTENT                                                    \
	BSFixedString creationClubMenu;        /* 198 - "Creation Club Menu */         \
	BSFixedString marketplaceMenu;         /* 1A0 - "Marketplace Menu */           \
	BSFixedString titleSequenceMenu;       /* 1A8 - "TitleSequence Menu */         \
	BSFixedString consoleNativeUIMenu;     /* 1B0 - "Console Native UI Menu */     \
	BSFixedString kinectMenu;              /* 1B8 - "Kinect Menu */                \
	BSFixedString loadWaitSpinner;         /* 1C0 - "LoadWaitSpinner */            \
	BSFixedString streamingInstallMenu;    /* 1C8 - "StreamingInstallMenu */       \
	BSFixedString textWidget;              /* 1D0 - "TextWidget */                 \
	BSFixedString buttonBarWidget;         /* 1D8 - "ButtonBarWidget */            \
	BSFixedString graphWidget;             /* 1E0 - "GraphWidget */                \
	BSFixedString textureWidget;           /* 1E8 - "TextureWidget */              \
	BSFixedString uiMenuOK;                /* 1F0 - "UIMenuOK */                   \
	BSFixedString uiMenuCancel;            /* 1F8 - "UIMenuCancel */               \
	BSFixedString showText;                /* 200 - "Show Text */                  \
	BSFixedString hideText;                /* 208 - "Hide Text */                  \
	BSFixedString showList;                /* 210 - "Show List */                  \
	BSFixedString voiceReady;              /* 218 - "Voice Ready */                \
	BSFixedString dmfoStr;                 /* 220 - "DMFOStr */                    \
	BSFixedString showJournal;             /* 228 - "Show Journal */               \
	BSFixedString journalSettingsSaved;    /* 230 - "Journal Settings Saved */     \
	BSFixedString closeMenu;               /* 238 - "CloseMenu */                  \
	BSFixedString closingAllMenus;         /* 240 - "Closing All Menus */          \
	BSFixedString refreshMenu;             /* 248 - "RefreshMenu */                \
	BSFixedString cancelLoading;           /* 250 - "CancelLoading */              \
	BSFixedString menuTextureDegradeEvent; /* 258 - "Menu Texture Degrade Event */ \
	BSFixedString userSettingsLoaded;      /* 260 - "UserSettingsLoaded */         \
	BSFixedString activityStarted;         /* 268 - "ActivityStarted */            \
	BSFixedString diamondMarker;           /* 270 - "<img src='DiamondMarker' width='10' height='15' align='baseline' vspace='5 */
			AE_RUNTIME_DATA_CONTENT
		};

		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT                                                                                                    \
	BSFixedString titleSequenceMenu;       /* 1A8 - "TitleSequence Menu */                                                         \
	BSFixedString consoleNativeUIMenu;     /* 1B0 - "Console Native UI Menu */                                                     \
	BSFixedString kinectMenu;              /* 1B8 - "Kinect Menu */                                                                \
	BSFixedString loadWaitSpinner;         /* 1C0 - "LoadWaitSpinner */                                                            \
	BSFixedString streamingInstallMenu;    /* 1C8 - "StreamingInstallMenu */                                                       \
	BSFixedString textWidget;              /* 1D0 - "TextWidget */                                                                 \
	BSFixedString buttonBarWidget;         /* 1D8 - "ButtonBarWidget */                                                            \
	BSFixedString graphWidget;             /* 1E0 - "GraphWidget */                                                                \
	BSFixedString textureWidget;           /* 1E8 - "TextureWidget */                                                              \
	BSFixedString uiMenuOK;                /* 1F0 - "UIMenuOK */                                                                   \
	BSFixedString uiMenuCancel;            /* 1F8 - "UIMenuCancel */                                                               \
	BSFixedString showText;                /* 200 - "Show Text */                                                                  \
	BSFixedString hideText;                /* 208 - "Hide Text */                                                                  \
	BSFixedString showList;                /* 210 - "Show List */                                                                  \
	BSFixedString voiceReady;              /* 218 - "Voice Ready */                                                                \
	BSFixedString dmfoStr;                 /* 220 - "DMFOStr */                                                                    \
	BSFixedString showJournal;             /* 228 - "Show Journal */                                                               \
	BSFixedString journalSettingsSaved;    /* 230 - "Journal Settings Saved */                                                     \
	BSFixedString closeMenu;               /* 238 - "CloseMenu */                                                                  \
	BSFixedString closingAllMenus;         /* 240 - "Closing All Menus */                                                          \
	BSFixedString refreshMenu;             /* 248 - "RefreshMenu */                                                                \
	BSFixedString cancelLoading;           /* 250 - "CancelLoading */                                                              \
	BSFixedString menuTextureDegradeEvent; /* 258 - "Menu Texture Degrade Event */                                                 \
	BSFixedString diamondMarker;           /* 270 - "<img src='DiamondMarker' width='10' height='15' align='baseline' vspace='5 */ \
	BSFixedString wsEnemyMeters;           /* 258 - "WSEnemyMeters */                                                              \
	BSFixedString wsActivateRollover;      /* 260 - "WSActivateRollover */                                                         \
	BSFixedString wsDebugOverlay;          /* 268 - "WSDebugOverlay */                                                             \
	BSFixedString statsMenuSkillRing;      /* 270 - "StatsMenuSkillRing */                                                         \
	BSFixedString statsMenuPerks;          /* 278 - "StatsMenuPerks */                                                             \
	BSFixedString mapMarkerText3D;         /* 280 - "MapMarkerText3D */                                                            \
	BSFixedString calibrationOptionMenu;   /* 288 - "CalibrationOptionMenu */
			VR_RUNTIME_DATA_CONTENT
		};

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x198, 0x198);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x198, 0x198);
		}

		[[nodiscard]] inline AE_RUNTIME_DATA& GetAERuntimeData() noexcept
		{
			return REL::RelocateMember<AE_RUNTIME_DATA>(this, 0x198, 0x198);
		}

		[[nodiscard]] inline const AE_RUNTIME_DATA& GetAERuntimeData() const noexcept
		{
			return REL::RelocateMember<AE_RUNTIME_DATA>(this, 0x198, 0x198);
		}

		[[nodiscard]] inline VR_RUNTIME_DATA& GetVRRuntimeData() noexcept
		{
			return REL::RelocateMember<VR_RUNTIME_DATA>(this, 0x198, 0x198);
		}

		[[nodiscard]] inline const VR_RUNTIME_DATA& GetVRRuntimeData() const noexcept
		{
			return REL::RelocateMember<VR_RUNTIME_DATA>(this, 0x198, 0x198);
		}

		// members
		std::uint8_t  pad001;                  // 001
		std::uint16_t pad002;                  // 002
		std::uint32_t pad004;                  // 004
		BSFixedString faderData;               // 008 - "FaderData"
		BSFixedString hudData;                 // 010 - "HUDData"
		BSFixedString hudCamData;              // 018 - "HUDCamData"
		BSFixedString floatingQuestMarkers;    // 020 - "FloatingQuestMarkers"
		BSFixedString consoleData;             // 028 - "ConsoleData"
		BSFixedString quantityData;            // 030 - "QuantityData"
		BSFixedString messageBoxData;          // 038 - "MessageBoxData"
		BSFixedString bsUIScaleformData;       // 040 - "BSUIScaleformData"
		BSFixedString bsUIMessageData;         // 048 - "BSUIMessageData"
		BSFixedString bsUIAnalogData;          // 050 - "BSUIAnalogData"
		BSFixedString inventoryUpdateData;     // 058 - "InventoryUpdateData"
		BSFixedString refHandleUIData;         // 060 - "RefHandleUIData"
		BSFixedString tesFormUIData;           // 068 - "TESFormUIData"
		BSFixedString loadingMenuData;         // 070 - "LoadingMenuData"
		BSFixedString kinectStateData;         // 078 - "KinectStateChangeData"
		BSFixedString kinectUserEventData;     // 080 - "KinectUserEventData"
		BSFixedString inventoryMenu;           // 088 - "InventoryMenu"
		BSFixedString console;                 // 090 - "Console"
		BSFixedString dialogueMenu;            // 098 - "Dialogue Menu"
		BSFixedString hudMenu;                 // 0A0 - "HUD Menu"
		BSFixedString mainMenu;                // 0A8 - "Main Menu"
		BSFixedString messageBoxMenu;          // 0B0 - "MessageBoxMenu"
		BSFixedString cursorMenu;              // 0B8 - "Cursor Menu"
		BSFixedString faderMenu;               // 0C0 - "Fader Menu"
		BSFixedString magicMenu;               // 0C8 - "MagicMenu"
		BSFixedString topMenu;                 // 0D0 - "Top Menu"
		BSFixedString overlayMenu;             // 0D8 - "Overlay Menu"
		BSFixedString overlayInteractionMenu;  // 0E0 - "Overlay Interaction Menu"
		BSFixedString loadingMenu;             // 0E8 - "Loading Menu"
		BSFixedString tweenMenu;               // 0F0 - "TweenMenu"
		BSFixedString barterMenu;              // 0F8 - "BarterMenu"
		BSFixedString giftMenu;                // 100 - "GiftMenu"
		BSFixedString debugTextMenu;           // 108 - "Debug Text Menu"
		BSFixedString mapMenu;                 // 110 - "MapMenu"
		BSFixedString lockpickingMenu;         // 118 - "Lockpicking Menu"
		BSFixedString quantityMenu;            // 120 - "Quantity Menu"
		BSFixedString statsMenu;               // 128 - "StatsMenu"
		BSFixedString containerMenu;           // 130 - "ContainerMenu"
		BSFixedString sleepWaitMenu;           // 138 - "Sleep/Wait Menu"
		BSFixedString levelUpMenu;             // 140 - "LevelUp Menu"
		BSFixedString journalMenu;             // 148 - "Journal Menu"
		BSFixedString bookMenu;                // 150 - "Book Menu"
		BSFixedString favoritesMenu;           // 158 - "FavoritesMenu"
		BSFixedString raceSexMenu;             // 160 - "RaceSex Menu"
		BSFixedString craftingMenu;            // 168 - "Crafting Menu"
		BSFixedString trainingMenu;            // 170 - "Training Menu"
		BSFixedString mistMenu;                // 178 - "Mist Menu"
		BSFixedString tutorialMenu;            // 180 - "Tutorial Menu"
		BSFixedString creditsMenu;             // 188 - "Credits Menu"
		BSFixedString modManagerMenu;          // 190 - "Mod Manager Menu"
#if defined(EXCLUSIVE_SKYRIM_FLAT)
#	ifndef ENABLE_SKYRIM_AE
		RUNTIME_DATA_CONTENT;
#	else
		AE_RUNTIME_DATA_CONTENT;
#	endif
#elif defined(EXCLUSIVE_SKYRIM_VR)
		VR_RUNTIME_DATA_CONTENT;
#else
#endif
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
#	ifndef ENABLE_SKYRIM_AE
	static_assert(sizeof(InterfaceStrings) == 0x260);
#	else
	static_assert(sizeof(InterfaceStrings) == 0x278);
#	endif
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(InterfaceStrings) == 0x290);
#else
	static_assert(sizeof(InterfaceStrings) == 0x198);
#endif
}
#undef RUNTIME_DATA_CONTENT
#undef AE_RUNTIME_DATA_CONTENT
#undef VR_RUNTIME_DATA_CONTENT
