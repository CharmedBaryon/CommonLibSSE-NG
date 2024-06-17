#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/Q/QuestObjectiveStates.h"

namespace RE
{
	class BGSQuestObjective;

	struct ObjectiveState
	{
	public:
		struct Event
		{
		public:
			// members
			BGSQuestObjective*    objective;  // 00
			QUEST_OBJECTIVE_STATE oldState;   // 08
			QUEST_OBJECTIVE_STATE newState;   // 0C
		};

		static BSTEventSource<Event>* GetEventSource();

	private:
		KEEP_FOR_RE()
	};
}
