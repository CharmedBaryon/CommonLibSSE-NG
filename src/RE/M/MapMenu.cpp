#include "RE/M/MapMenu.h"

using namespace REL;

namespace RE
{
	BSEventNotifyControl MapMenu::ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource)
	{
		return RelocateVirtual<decltype(&MapMenu::ProcessEvent)>(0x30, 0x58, 0x01, 0x01, this, a_event, a_eventSource);
	}
}
