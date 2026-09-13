#pragma once

#include "RE/B/BSPathingCell.h"

namespace RE
{
	struct PathingCellInfo
	{
	public:
		constexpr PathingCellInfo() :
			worldSpaceID(0)
		{}

		union CellFormID
		{
			constexpr CellFormID() :
				formID(0)
			{}

			bool operator==(const CellFormID& a_rhs) const noexcept
			{
				return formID == a_rhs.formID && coordinates == a_rhs.coordinates;
			}

			FormID formID;
			CellID coordinates;
		};

		bool operator==(const PathingCellInfo& a_rhs) const noexcept
		{
			return worldSpaceID == a_rhs.worldSpaceID && cellID == a_rhs.cellID;
		}

		// members
		FormID     worldSpaceID;
		CellFormID cellID;
	};
	static_assert(sizeof(PathingCellInfo) == 0x8);

	class PathingCell : public BSPathingCell
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingCell;
		inline static constexpr auto VTABLE = VTABLE_PathingCell;

		~PathingCell() override;  // 00

		// override (BSPathingCell)
		std::uint32_t GetType() const override;                                             // 01 - "PathingCell"
		void          Write(const BSPathingStreamWrite& a_stream) override;                 // 02
		void          Read(const BSPathingStreamRead& a_stream) override;                   // 03
		void          FixupNumericID(BSPathingNumericIDVisitor& a_visitor) override;        // 04
		void          GetSpace(BSTSmartPointer<BSPathingSpace>& a_out) override;            // 05
		bhkWorld*     GetBhkWorld() override;                                               // 06
		bool          QValid() const override;                                              // 07
		bool          QAttached() const override;                                           // 08
		bool          QLoaded() const override;                                             // 09
		bool          IsInSameSpace(BSTSmartPointer<BSPathingCell>* a_otherCell) override;  // 0A

		// members
		PathingCellInfo pathingCellInfo;  // 10
	};
	static_assert(sizeof(PathingCell) == 0x18);

	template <>
	struct BSCRC32_<PathingCellInfo>
	{
	public:
		[[nodiscard]] std::uint32_t operator()(const PathingCellInfo& a_info) const noexcept
		{
			return detail::GenerateCRC32(
				std::span(
					reinterpret_cast<const std::uint8_t*>(std::addressof(a_info)),
					sizeof(PathingCellInfo)));
		}
	};
}
