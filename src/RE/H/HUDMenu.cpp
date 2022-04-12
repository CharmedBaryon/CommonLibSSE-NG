#include "RE/H/HUDMenu.h"

using namespace REL;

namespace RE
{
	BSEventNotifyControl HUDMenu::ProcessEvent(const UserEventEnabledEvent* a_event, BSTEventSource<UserEventEnabledEvent>* a_eventSource)
	{
		return RelocateVirtual<BSEventNotifyControl(HUDMenu*, const UserEventEnabledEvent*, BSTEventSource<UserEventEnabledEvent>*)>(
			0x30, 0x58, 0x01, 0x01, this, a_event, a_eventSource);
	}

	BSEventNotifyControl HUDMenu::ProcessEvent(const BSRemoteGamepadEvent* a_event, BSTEventSource<BSRemoteGamepadEvent>* a_eventSource)
	{
		return RelocateVirtual<BSEventNotifyControl(HUDMenu*, const BSRemoteGamepadEvent*, BSTEventSource<BSRemoteGamepadEvent>*)>(
			0x38, 0x60, 0x01, 0x01, this, a_event, a_eventSource);
	}
}
