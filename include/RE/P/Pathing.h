#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTTuple.h"
#include "RE/P/PathingCell.h"

namespace RE
{
	class BSNavmesh;
	class BSPathingLocation;
	struct BSPathingSolution;
	struct CellAttachDetachEvent;
	struct IMovementPlayIdleResult;
	struct MovementArbitrationVectorAdd;
	struct MovementArbitrationAverageFloat;
	struct MovementArbitrationMaxWeightPoint;
	struct MovementArbitrationMaxWeightParameters;
	struct MovementMessageBlocked;

	class BSPathingCellManager : public BSTSingletonExplicit<BSPathingCellManager>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathingCellManager;
		inline static constexpr auto VTABLE = VTABLE_BSPathingCellManager;

		// add
		virtual float GetExteriorCellWidth() const = 0;                                                                                                                                                // 00
		virtual bool  GetPathingCell(const NiPoint3& a_location, const BSTSmartPointer<BSPathingCell>& a_hintCell, BSTSmartPointer<BSPathingCell>& a_cellOut) = 0;                                     // 01
		virtual bool  IsCloseTo(const NiPoint3& a_loc1, const BSTSmartPointer<BSPathingCell>& a_cell1, const NiPoint3& a_loc2, const BSTSmartPointer<BSPathingCell>& a_cell2, float a_tolerance) = 0;  // 02
		virtual void  FindPotentialNavmeshesForLocation1(BSPathingLocation& a_location, float a_radius, BSScrapArray<BSTSmartPointer<BSNavmesh>>& a_navMeshesOut) = 0;                                 // 03
		virtual void  FindPotentialNavmeshesForLocation2(BSPathingLocation& a_location, float a_radius, BSTArray<BSTSmartPointer<BSNavmesh>>& a_navMeshesOut) = 0;                                     // 04
		virtual void  FindConnectedNavmeshesForLocation3(BSPathingLocation& a_location, float a_radius, BSScrapArray<const BSNavmeshInfo*>& a_navMeshesOut) = 0;                                       // 05
		virtual void  FindConnectedNavmeshesForLocation4(BSPathingLocation& a_location, float a_radius, BSTArray<const BSNavmeshInfo*>& a_navMeshesOut) = 0;                                           // 06
		virtual void  FindConnectedNavmeshesForLocation5(BSPathingLocation& a_location, float a_radius, BSScrapArray<BSTSmartPointer<BSNavmesh>>& a_navMeshesOut) = 0;                                 // 07
		virtual void  FindConnectedNavmeshesForLocation6(BSPathingLocation& a_location, float a_radius, BSTArray<BSTSmartPointer<BSNavmesh>>& a_navMeshesOut) = 0;                                     // 08
		virtual float GetWaterHeight(const BSPathingLocation* a_location) const = 0;                                                                                                                   // 09

		virtual ~BSPathingCellManager();  // 0A
	};
	static_assert(sizeof(BSPathingCellManager) == 0x08);

	class MovementManager : public BSTSingletonExplicit<MovementManager>
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementManager;

		// members
		BSTSmartPointer<MovementArbitrationVectorAdd>           vectorAdd;               // 00
		BSTSmartPointer<MovementArbitrationAverageFloat>        floatAverage;            // 08
		BSTSmartPointer<MovementArbitrationMaxWeightPoint>      vectorMaxWeight;         // 10
		BSTSmartPointer<MovementArbitrationMaxWeightParameters> parametersMaxWeight;     // 18
		BSTSmartPointer<MovementMessageBlocked>                 movementBlockedMessage;  // 20
		BSTSmartPointer<IMovementPlayIdleResult>                nullPlayIdleResult;      // 28
		BSTSmartPointer<BSPathingSolution>                      emptySolution;           // 30
	};
	static_assert(sizeof(MovementManager) == 0x38);

	class Pathing :
		public BSPathing,                            // 00
		public BSPathingCellManager,                 // 18
		public BSTEventSink<CellAttachDetachEvent>,  // 20
		public BSTSingletonSDM<Pathing>,             // 28
		public MovementManager                       // 30
	{
	public:
		inline static constexpr auto RTTI = RTTI_Pathing;
		inline static constexpr auto VTABLE = VTABLE_Pathing;

		static Pathing* GetSingleton()
		{
			static REL::Relocation<Pathing**> singleton{ RELOCATION_ID(514893, 401037) };
			return *singleton;
		}

		bool GetPathingCell(const NiPoint3& a_location, TESObjectCELL* a_cell, TESWorldSpace* a_worldSpace, BSTSmartPointer<BSPathingCell>& a_cellOut)
		{
			using func_t = decltype(&Pathing::GetPathingCell);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29866, 30682) };
			return func(this, a_location, a_cell, a_worldSpace, a_cellOut);
		}

		bool FindClosestPointOnNavmesh(const BSTSmartPointer<BSPathingCell>& a_cell, const NiPoint3& a_location, NiPoint3& a_pointOut)
		{
			return FindClosestPointOnNavmesh(a_cell, a_location, defaultTriangleFilter, a_pointOut);
		}

		bool FindClosestPointOnNavmesh(const BSTSmartPointer<BSPathingCell>& a_cell, const NiPoint3& a_location, FindTriangleForLocationFilter& a_filter, NiPoint3& a_pointOut)
		{
			using func_t = bool (*)(Pathing*, const BSTSmartPointer<BSPathingCell>&, const NiPoint3&, FindTriangleForLocationFilter&, NiPoint3&);
			static REL::Relocation<func_t> func{ RELOCATION_ID(29832, 30648) };
			return func(this, a_cell, a_location, a_filter, a_pointOut);
		}

		// members
		BSSpinLock                                                      cellCacheLock;  // 68
		BSTHashMap<PathingCellInfo, BSTSmartPointer<PathingCell>>       loadedCells;    // 70
		BSTArray<BSTTuple<std::uint64_t, BSTSmartPointer<PathingCell>>> recentCells;    // A0
	};
	static_assert(sizeof(Pathing) == 0xB8);
}
