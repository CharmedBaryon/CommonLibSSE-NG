#pragma once

namespace RE
{
	class IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementInterface;
		inline static constexpr auto VTABLE = VTABLE_IMovementInterface;

		virtual ~IMovementInterface();

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(IMovementInterface) == 0x8);
}
