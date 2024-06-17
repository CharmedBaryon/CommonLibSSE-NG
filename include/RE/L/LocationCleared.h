#pragma once

#include "RE/B/BSTEvent.h"

namespace RE
{
	struct LocationCleared
	{
	public:
		struct Event
		{
			// empty
		};

		static BSTEventSource<Event>* GetEventSource();

	private:
		KEEP_FOR_RE()
	};
}
