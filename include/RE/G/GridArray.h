#pragma once

namespace RE
{
	class GridArray
	{
	public:
		inline static constexpr auto RTTI = RTTI_GridArray;
		inline static constexpr auto VTABLE = VTABLE_GridArray;

		virtual ~GridArray();  // 00

		// add
		virtual void DetachAll();                                                                                           // 01
		virtual void KillAll();                                                                                             // 02
		virtual bool SetCenter(std::int32_t a_x, std::int32_t a_y);                                                         // 03
		virtual void Shift(std::int32_t a_x, std::int32_t a_y);                                                             // 04
		virtual void Detach(std::uint32_t a_x, std::uint32_t a_y) = 0;                                                      // 05
		virtual void ClearItem(std::uint32_t a_x, std::uint32_t a_y) = 0;                                                   // 06
		virtual void MoveItem(std::uint32_t a_fromX, std::uint32_t a_fromY, std::uint32_t a_toX, std::uint32_t a_toY) = 0;  // 07
		virtual void SwapItem(std::uint32_t a_fromX, std::uint32_t a_fromY, std::uint32_t a_toX, std::uint32_t a_toY) = 0;  // 08

		// members
		std::uint32_t unk08;   // 08 - 1000
		std::uint32_t unk0C;   // 0C - 1000
		std::uint32_t length;  // 10 - takes value from uGridsToLoad
		std::uint32_t pad14;   // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GridArray) == 0x18);
};
