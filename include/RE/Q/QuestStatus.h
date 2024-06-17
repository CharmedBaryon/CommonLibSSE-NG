#pragma once

#include "RE/B/BSTEvent.h"

namespace RE
{
	class TESQuest;

	struct QuestStatus
	{
	public:
		enum Status
		{
			kCompleted = 0,
			kStarted = 1,
			kReseted = 2
		};

		struct Event
		{
		public:
			// members
			TESQuest* quest;   // 00
			Status    status;  // 08
		};

		static BSTEventSource<Event>* GetEventSource();

	private:
		KEEP_FOR_RE()
	};
}
