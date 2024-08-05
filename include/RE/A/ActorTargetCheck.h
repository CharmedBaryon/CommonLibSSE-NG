#pragma once

#include "RE/P/ProcessLists.h"

namespace RE
{
	class ActorTargetCheck : public ProcessLists::GetActorsFilter
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActorTargetCheck;
		inline static constexpr auto VTABLE = VTABLE_ActorTargetCheck;

		~ActorTargetCheck() override;  // 00

		// override (GetActorsFilter)
		bool IsValid(Actor* a_actor) override;  // 01

		// members
		std::uint64_t unk08;  // 08
		std::uint64_t unk10;  // 10
		std::uint64_t unk18;  // 18
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ActorTargetCheck) == 0x20);
}
