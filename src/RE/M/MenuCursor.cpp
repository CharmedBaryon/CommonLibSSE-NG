#include "RE/M/MenuCursor.h"
#include "REX/W32/USER32.h"

namespace RE
{
	MenuCursor* MenuCursor::GetSingleton()
	{
		static REL::Relocation<MenuCursor**> singleton{ RELOCATION_ID(517043, 403551) };
		return *singleton;
	}

	void MenuCursor::SetCursorVisibility(bool a_visible)
	{
		auto& runtimeData = GetRuntimeData();
		if (a_visible && runtimeData.showCursorCount < 0) {
			do {
				runtimeData.showCursorCount = REX::W32::ShowCursor(true);
			} while (runtimeData.showCursorCount < 0);
		} else if (!a_visible && runtimeData.showCursorCount >= 0) {
			do {
				runtimeData.showCursorCount = REX::W32::ShowCursor(false);
			} while (runtimeData.showCursorCount >= 0);
		}
	}
}
