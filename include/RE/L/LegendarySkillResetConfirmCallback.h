#pragma once

#include "RE/I/IMessageBoxCallback.h"

namespace RE
{
	class LegendarySkillResetConfirmCallback : public RE::IMessageBoxCallback
	{
	public:
		inline static constexpr auto RTTI = RTTI___LegendarySkillResetConfirmCallback;
		inline static constexpr auto VTABLE = VTABLE___LegendarySkillResetConfirmCallback;

		virtual ~LegendarySkillResetConfirmCallback();  // 00

		// override (IMessageBoxCallback)
		void Run(Message a_msg) override;  // 01

		// members
		std::uint64_t  unk10;  // 10
		std::uint32_t  unk18;  // 18
		RE::ActorValue skill;  // 1C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(LegendarySkillResetConfirmCallback) == 0x20);
}
