#pragma once

#include "RE/B/BSTSingleton.h"

namespace RE
{
	class MenuCursor : public BSTSingletonSDM<MenuCursor>
	{
	public:
		static MenuCursor* GetSingleton();

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                  \
	float        cursorXPosition;    /* 04 */ \
	float        cursorYPosition;    /* 08 */ \
	float        cursorXMin;         /* 0C */ \
	float        cursorYMin;         /* 10 */ \
	float        cursorXMax;         /* 14 */ \
	float        cursorYMax;         /* 18 */ \
	float        cursorSensitivity;  /* 1C */ \
	float        unk20;              /* 20 */ \
	float        unk24;              /* 24 */ \
	float        logicalWidth;       /* 28 */ \
	std::int32_t cursorDisplayCount; /* 2C */
			RUNTIME_DATA_CONTENT
		};


		void SetCursorVisibility(bool a_visible);
		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x4, 0x8);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x4, 0x8);
		}

		// members
		std::uint8_t  pad01;  // 01
		std::uint16_t pad02;  // 02
#ifndef ENABLE_SKYRIM_VR	
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		float unkVR04;
#else
#endif
		RUNTIME_DATA_CONTENT; // 04, 08

	private:
		KEEP_FOR_RE()
	};
#if !defined(ENABLE_SKYRIM_VR)
	static_assert(sizeof(MenuCursor) == 0x30);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(MenuCursor) == 0x34);
#else
	static_assert(sizeof(MenuCursor) == 0x30);
#endif
}
#undef RUNTIME_DATA_CONTENT
