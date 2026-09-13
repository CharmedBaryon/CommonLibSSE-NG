#pragma once

#include "RE/I/IMessageBoxCallback.h"

namespace RE
{
	namespace BSScript
	{
		class IVirtualMachine;
	}

	namespace SkyrimScript
	{
		class ScriptMessageBoxCallback : public IMessageBoxCallback
		{
		public:
			inline static constexpr auto RTTI = RTTI_SkyrimScript____ScriptMessageBoxCallback;
			inline static constexpr auto VTABLE = VTABLE_SkyrimScript____ScriptMessageBoxCallback;

			virtual ~ScriptMessageBoxCallback() override;  // 00

			// override (IMessageBoxCallback)
			virtual void Run(std::uint8_t a_button) override;  // 01

			// members
			VMStackID                  stackID;  // 10
			std::uint32_t              pad14;    // 14
			BSScript::IVirtualMachine* vm;       // 18
		};
		static_assert(sizeof(ScriptMessageBoxCallback) == 0x20);
	}
}
