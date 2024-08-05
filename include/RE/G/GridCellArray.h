#pragma once

#include "RE/G/GridArray.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class TESObjectCELL;

	class GridCellArray : public GridArray
	{
	public:
		inline static constexpr auto RTTI = RTTI_GridCellArray;
		inline static constexpr auto VTABLE = VTABLE_GridCellArray;

		~GridCellArray() override;  // 00

		// override (GridArray)
		void KillAll() override;                                                                                         // 02
		bool SetCenter(std::int32_t a_x, std::int32_t a_y) override;                                                     // 03
		void Detach(std::uint32_t a_x, std::uint32_t a_y) override;                                                      // 05
		void ClearItem(std::uint32_t a_x, std::uint32_t a_y) override;                                                   // 06
		void MoveItem(std::uint32_t a_fromX, std::uint32_t a_fromY, std::uint32_t a_toX, std::uint32_t a_toY) override;  // 07
		void SwapItem(std::uint32_t a_fromX, std::uint32_t a_fromY, std::uint32_t a_toX, std::uint32_t a_toY) override;  // 08

		[[nodiscard]] TESObjectCELL* GetCell(std::uint32_t a_x, std::uint32_t a_y) const noexcept
		{
			return (a_x < length && a_y < length) ?
			           cells[(a_x * length) + a_y] :
			           nullptr;
		};

		// members
		TESObjectCELL** cells;           // 18 - (memory allocated using 0x8 * numGrids * numGrids)
		NiPoint3        unk20;           // 20
		bool            land3DAttached;  // 2C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GridCellArray) == 0x30);
};
