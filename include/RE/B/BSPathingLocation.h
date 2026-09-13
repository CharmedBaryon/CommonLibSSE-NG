#pragma once

#include "RE/B/BSPathingCell.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	struct BSNavmeshInfo;
	class BSNavmesh;
	class FindTriangleForLocationFilter;

	class BSPathingLocation
	{
	public:
		BSPathingLocation(const NiPoint3& a_location, const BSTSmartPointer<BSPathingCell>& a_cell)
		{
			ctor(a_location, a_cell);
		}

		~BSPathingLocation() = default;

		bool ResolveToClosestNavmeshAndTriangle(FindTriangleForLocationFilter& a_filter)
		{
			using func_t = decltype(&BSPathingLocation::ResolveToClosestNavmeshAndTriangle);
			static REL::Relocation<func_t> func{ RELOCATION_ID(87985, 90369) };
			return func(this, a_filter);
		}

		bool GetNavMeshAndTriangle(BSTSmartPointer<BSNavmesh>& a_navMeshOut, std::uint16_t& a_triOut) const
		{
			using func_t = decltype(&BSPathingLocation::GetNavMeshAndTriangle);
			static REL::Relocation<func_t> func{ RELOCATION_ID(87978, 90360) };
			return func(this, a_navMeshOut, a_triOut);
		}

		// members
		NiPoint3                       location;          // 00
		BSNavmeshInfo*                 navMeshInfo;       // 10
		BSTArray<BSNavmeshInfo*>*      navMeshInfoArray;  // 18
		BSTSmartPointer<BSPathingCell> pathingCell;       // 20
		std::uint16_t                  triangle;          // 28
		std::uint8_t                   flags;             // 2A
		std::uint8_t                   clientData;        // 2B

	private:
		BSPathingLocation* ctor(const NiPoint3& a_location, const BSTSmartPointer<BSPathingCell>& a_cell)
		{
			using func_t = decltype(&BSPathingLocation::ctor);
			static REL::Relocation<func_t> func{ RELOCATION_ID(87965, 90346) };
			return func(this, a_location, a_cell);
		}
	};
	static_assert(sizeof(BSPathingLocation) == 0x30);
}
