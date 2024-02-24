#include "RE/M/MenuCursor.h"
#include "REX/W32/USER32.h"

namespace RE
{
	MenuCursor* MenuCursor::GetSingleton()
	{
		REL::Relocation<MenuCursor**> singleton{ RELOCATION_ID(517043, 403551) };
		return *singleton;
	}

	void MenuCursor::SetCursorVisibility(bool a_visible)
	{
		if (a_visible && showCursorCount < 0) {
			do {
				showCursorCount = REX::W32::ShowCursor(true);
			} while (showCursorCount < 0);
		} else if (!a_visible && showCursorCount >= 0) {
			do {
				showCursorCount = REX::W32::ShowCursor(false);
			} while (showCursorCount >= 0);
		}
	}
}
