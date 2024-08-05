#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	class IMovementSelectIdle : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementSelectIdle;
		inline static constexpr auto VTABLE = VTABLE_IMovementSelectIdle;

		~IMovementSelectIdle() override;  // 00

		// add
		virtual void Unk_01(void) = 0;  // 01
		virtual void Unk_02(void) = 0;  // 02
		virtual void Unk_03(void) = 0;  // 03
		virtual void Unk_04(void) = 0;  // 04
		virtual void Unk_05(void) = 0;  // 05
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(IMovementSelectIdle) == 0x8);
}
