#pragma once

#include "RE/I/IAIWorldLocationHandle.h"
#include "RE/I/IPackageData.h"

namespace RE
{
	class IAITarget :
		public IAIWorldLocationHandle,  // 00
		public IPackageData             // 08
	{
	public:
		inline static constexpr auto RTTI = RTTI_IAITarget;
		inline static constexpr auto VTABLE = VTABLE_IAITarget;

		~IAITarget() override;  // 00

		// add
		virtual void Unk_04(void) = 0;  // 04
		virtual void Unk_05(void) = 0;  // 05
		virtual void Unk_06(void) = 0;  // 06
		virtual void Unk_07(void) = 0;  // 07
		virtual void Unk_08(void) = 0;  // 08
		virtual void Unk_09(void) = 0;  // 09
		virtual void Unk_0A(void) = 0;  // 0A
		virtual void Unk_0B(void);      // 0B - { return 0; }
	};
	static_assert(sizeof(IAITarget) == 0x10);
}
