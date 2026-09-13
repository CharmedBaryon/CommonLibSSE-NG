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
		virtual bool                RegisterInterface(BSFixedString* a_name, IMovementInterface* a_interface) = 0;  // 01
		virtual IMovementInterface* GetInterface1(const BSFixedString& name) = 0;                                   // 02
		virtual IMovementInterface* GetInterface2(const BSFixedString& name) = 0;                                   // 03
		virtual void                Unk_04(void) = 0;                                                               // 04
	};
	static_assert(sizeof(IMovementControllerRegisterInterface) == 0x8);
}
