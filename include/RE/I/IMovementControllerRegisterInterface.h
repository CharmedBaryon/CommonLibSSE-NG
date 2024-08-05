#pragma once

namespace RE
{
	class IMovementControllerRegisterInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementControllerRegisterInterface;
		inline static constexpr auto VTABLE = VTABLE_IMovementControllerRegisterInterface;

		virtual ~IMovementControllerRegisterInterface();  // 00

		// add
		virtual void Unk_01(void) = 0;  // 01
		virtual void Unk_02(void) = 0;  // 02
		virtual void Unk_03(void) = 0;  // 03
		virtual void Unk_04(void) = 0;  // 04
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(IMovementControllerRegisterInterface) == 0x8);
}
