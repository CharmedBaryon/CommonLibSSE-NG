#pragma once

namespace RE
{
	namespace BSScript
	{
		class IVMDebugInterface
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSScript__IVMDebugInterface;
			inline static constexpr auto VTABLE = VTABLE_BSScript__IVMDebugInterface;

			virtual ~IVMDebugInterface();  // 00

			// add
			virtual void DumpRunningStacksToLog() = 0;  // 01
		};
		static_assert(sizeof(IVMDebugInterface) == 0x8);
	}
}
