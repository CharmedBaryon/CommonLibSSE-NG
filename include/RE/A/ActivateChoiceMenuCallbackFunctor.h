#pragma once

#include "RE/I/IMessageBoxCallback.h"

namespace RE
{
	class ActivateChoiceMenuCallbackFunctor : public IMessageBoxCallback
	{
	public:
		inline static constexpr auto RTTI = RTTI___ActivateChoiceMenuCallbackFunctor;
		inline static constexpr auto VTABLE = VTABLE___ActivateChoiceMenuCallbackFunctor;

		~ActivateChoiceMenuCallbackFunctor() override;  // 00

		// override (IMessageBoxCallback)
		void Run(std::uint8_t a_button) override;  //01

		// members
		ObjectRefHandle unk10;  // 10
		std::uint32_t   unk14;  // 14
	};
	static_assert(sizeof(ActivateChoiceMenuCallbackFunctor) == 0x18);
}
