#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/B/BSTSingleton.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSCompressedNavmeshBounds;
	class BSNavmesh;
	class BSPathingCell;
	class BSPathingDoor;

	struct BSNavmeshInfo
	{
	public:
		std::uint32_t                   navMeshID;            // 00
		NiPoint3                        approxLocation;       // 04
		BSTSmartPointer<BSPathingDoor>* connectedDoorsArray;  // 10
		std::uint32_t*                  adjacentMeshesArray;  // 18
		std::uint16_t                   connectedDoorCount;   // 20
		std::uint16_t                   adjacentMeshCount;    // 22
		float                           preferredPercent;     // 24
		BSNavmesh*                      navMesh;              // 28
		BSCompressedNavmeshBounds*      bounds;               // 30
		BSTSmartPointer<BSPathingCell>  pathingCell;          // 38
		std::uint16_t                   preferredStartIndex;  // 40
		std::uint8_t                    uiFlags;              // 42
	};
	static_assert(sizeof(BSNavmeshInfo) == 0x48);

	class BSNavmeshInfoMap : public BSTSingletonExplicit<BSNavmeshInfoMap>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSNavmeshInfoMap;
		inline static constexpr auto VTABLE = VTABLE_BSNavmeshInfoMap;

		struct IVisitor
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSNavmeshInfoMap__IVisitor;
			inline static constexpr auto VTABLE = VTABLE_BSNavmeshInfoMap__IVisitor;

			virtual ~IVisitor();  // 00

			// add
			virtual BSContainer::ForEachResult Visit(const BSNavmeshInfo* a_info) = 0;
		};
		static_assert(sizeof(IVisitor) == 0x8);

		virtual ~BSNavmeshInfoMap();  // 00

		// add
		virtual BSNavmeshInfo* GetNavMeshInfoFixID(std::uint32_t a_id) = 0;                                                      // 01
		virtual BSNavmeshInfo* GetNavmeshInfo(std::uint32_t a_id) = 0;                                                           // 02
		virtual void           GetAllNavMeshInfo(BSTArray<BSNavmeshInfo*>& a_results) = 0;                                       // 03
		virtual void           BuildListOfConnectedInfos(const BSNavmeshInfo* a_info, BSTArray<BSNavmeshInfo*>& a_results) = 0;  // 04
		virtual void           ForEach(IVisitor* a_visitor) = 0;                                                                 // 05
	};
	static_assert(sizeof(BSNavmeshInfoMap) == 0x8);
}
