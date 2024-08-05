#pragma once

#include "RE/B/BSPathingCell.h"

namespace RE
{
	class PathingCell : public BSPathingCell
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingCell;
		inline static constexpr auto VTABLE = VTABLE_PathingCell;

		~PathingCell() override;  // 00

		// override (BSPathingCell)
		std::uint32_t GetType() const override;  // 01 - "PathingCell"
		void          Unk_02(void) override;     // 02
		void          Unk_03(void) override;     // 03
		void          Unk_04(void) override;     // 04
		void          Unk_05(void) override;     // 05
		void          Unk_06(void) override;     // 06
		void          Unk_07(void) override;     // 07
		void          Unk_08(void) override;     // 08
		void          Unk_09(void) override;     // 09
		void          Unk_0A(void) override;     // 0A

		// members
		FormID unk10;   // 10
		FormID cellID;  // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(PathingCell) == 0x18);
}
