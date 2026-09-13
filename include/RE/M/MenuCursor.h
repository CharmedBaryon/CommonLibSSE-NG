#pragma once

#include "RE/B/BSTSingleton.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class MenuCursor : public BSTSingletonSDM<MenuCursor>
	{
	public:
		static MenuCursor* GetSingleton();

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                 \
	float        cursorPosX;        /* 04 */ \
	float        cursorPosY;        /* 08 */ \
	float        safeZoneX;         /* 0C */ \
	float        safeZoneY;         /* 10 */ \
	float        screenWidthX;      /* 14 */ \
	float        screenWidthY;      /* 18 */ \
	float        cursorSensitivity; /* 1C */ \
	float        unk20;             /* 20 */ \
	float        unk24;             /* 24 */ \
	float        defaultMouseSpeed; /* 28 */ \
	std::int32_t showCursorCount;   /* 2C */
			RUNTIME_DATA_CONTENT
		};

		void SetCursorVisibility(bool a_visible);
		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x4, 0x8);
		// members
		std::uint8_t  pad01;  // 01
		std::uint16_t pad02;  // 02
#ifndef ENABLE_SKYRIM_VR
#elif defined(EXCLUSIVE_SKYRIM_VR)
		float unkVR04;
#else
#endif
		RUNTIME_DATA_CONTENT;  // 04, 08
	};
	STATIC_ASSERT_SIZE(MenuCursor, 0x30, 0x30, 0x34, 0x30);
}
#undef RUNTIME_DATA_CONTENT
