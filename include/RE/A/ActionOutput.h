#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	class TESIdleForm;

	class ActionOutput
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActionOutput;

		// members
		BSFixedString      animEvent;        // 00
		BSFixedString      targetAnimEvent;  // 08
		int32_t            result;           // 10
		TESIdleForm*       sequence;         // 18
		const TESIdleForm* animObjIdle;      // 20
		uint32_t           sequenceIndex;    // 28
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ActionOutput) == 0x30);
}
