#pragma once

#include "RE/I/IHandlerFunctor.h"

namespace RE
{
	class VoiceSpellFireHandler : public AnimHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_VoiceSpellFireHandler;
		inline static constexpr auto VTABLE = VTABLE_VoiceSpellFireHandler;

		~VoiceSpellFireHandler() override;  // 00

		// override (IHandleFunctor)
		bool ExecuteHandler(Actor& a_actor, const BSFixedString& a_tag) override;

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(VoiceSpellFireHandler) == 0x10);
}
