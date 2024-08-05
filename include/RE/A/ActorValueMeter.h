#pragma once

#include "RE/A/ActorValues.h"
#include "RE/H/HUDMeter.h"

namespace RE
{
	class ActorValueMeter : public HUDMeter
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActorValueMeter;
		inline static constexpr auto VTABLE = VTABLE_ActorValueMeter;

		~ActorValueMeter() override;  // 00

		// override (HUDMeter)
		bool  ProcessMessage(UIMessage* a_message) override;  // 02
		float GetFillPct() override;                          // 05

		// members
		ActorValue    actorValue;  // 48
		std::uint32_t pad4C;       // 4C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ActorValueMeter) == 0x50);
}
