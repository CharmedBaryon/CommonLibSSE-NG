#include "RE/H/HeldStateHandler.h"

#include "RE/B/ButtonEvent.h"

namespace RE
{
	void HeldStateHandler::UpdateHeldStateActive(const ButtonEvent* a_event)
	{
		heldStateActive = a_event->GetRuntimeData().value != 0.0f || a_event->GetRuntimeData().heldDownSecs < 0.0f;
	}

	void HeldStateHandler::SetHeldStateActive(bool a_flag)
	{
		heldStateActive = a_flag;
	}
}
