#pragma once

#include "RE/B/BipedObjects.h"
#include "RE/I/InventoryEvent.h"

namespace RE
{
	struct ActorInventoryEvent
	{
	public:
		// members
		const INVENTORY_EVENT event;       // 00
		BIPED_OBJECT          equipIndex;  // 04
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ActorInventoryEvent) == 0x08);
}
