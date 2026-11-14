#pragma once

#include "RE/I/IGiftMenuScriptCallback.h"

namespace RE
{
	namespace BSScript
	{
		class IVirtualMachine;
	}

	namespace SkyrimScript
	{
		class GiftMenuCallbackFunc : public IGiftMenuScriptCallback
		{
			inline static constexpr auto RTTI = RTTI_SkyrimScript__GiftMenuCallbackFunc;
			inline static constexpr auto VTABLE = VTABLE_SkyrimScript__GiftMenuCallbackFunc;

			virtual ~GiftMenuCallbackFunc();  // 00

			// override (IGiftMenuScriptCallback)
			virtual void Run(std::int32_t a_totalValueTransferred) override;  // 01

			// members
			VMStackID                  stackID;  // 10
			std::uint32_t              pad14;    // 14
			BSScript::IVirtualMachine* vm;       // 18
		};
		static_assert(sizeof(GiftMenuCallbackFunc) == 0x20);
	}
}
