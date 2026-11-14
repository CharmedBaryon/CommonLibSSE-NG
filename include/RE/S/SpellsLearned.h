#pragma once

#include "RE/B/BSTEvent.h"

namespace RE
{
	struct SpellsLearned
	{
	public:
		// Carries no data. Do not add fields.
		struct Event
		{
		};
		static_assert(sizeof(Event) == 0x1);

		static BSTEventSource<Event>* GetEventSource();
		static void                   SendEvent();
	};
}
