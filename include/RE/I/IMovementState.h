#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	class NiPoint3;

	class IMovementState : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementState;
		inline static constexpr auto VTABLE = VTABLE_IMovementState;

		~IMovementState() override;  // 00

		// add
		virtual void  Unk_01(void) = 0;                                 // 01
		virtual void  Unk_02(void) = 0;                                 // 02
		virtual void  Unk_03(void) = 0;                                 // 03
		virtual void  Unk_04(void) = 0;                                 // 04
		virtual float DoGetMovementSpeed() = 0;                         // 05
		virtual float DoGetRotationSpeed() = 0;                         // 06
		virtual void  Unk_07(void) = 0;                                 // 07
		virtual void  Unk_08(void) = 0;                                 // 08
		virtual void  DoGetMovementRotation(NiPoint3& a_rotation) = 0;  // 09
		virtual void  Unk_0A(void) = 0;                                 // 0A
		virtual void  Unk_0B(void) = 0;                                 // 0B
		virtual void  Unk_0C(void) = 0;                                 // 0C
		virtual void  Unk_0D(void) = 0;                                 // 0D
		virtual void  Unk_0E(void) = 0;                                 // 0E
		virtual void  Unk_0F(void) = 0;                                 // 0F
		virtual void  Unk_10(void) = 0;                                 // 10
		virtual void  Unk_11(void) = 0;                                 // 11
		virtual void  Unk_12(void) = 0;                                 // 12
		virtual void  Unk_13(void) = 0;                                 // 13
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(IMovementState) == 0x8);
}
