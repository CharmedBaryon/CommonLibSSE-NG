#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSingleton.h"
#include "RE/N/NiPoint2.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSLeafAnimNode;
	class BSTreeNode;
	class NiCamera;

	class BSTreeManager : public BSTSingletonSDM<BSTreeManager>
	{
	public:
		class IQueryCullingCamera
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSTreeManager__IQueryCullingCamera;
			inline static constexpr auto VTABLE = VTABLE_BSTreeManager__IQueryCullingCamera;

			virtual ~IQueryCullingCamera();  // 00

			// add
			virtual NiCamera* GetCamera() = 0;  // 01
		};
		static_assert(sizeof(IQueryCullingCamera) == 0x8);

		static BSTreeManager* GetSingleton()
		{
			REL::Relocation<BSTreeManager**> singleton{ RELOCATION_ID(514181, 400330) };
			return *singleton;
		}

		// members
		bool                                enableTrees;       // 01
		bool                                enableTreeAnims;   // 02
		bool                                forceFullDetail;   // 03
		std::uint32_t                       pad04;             // 04
		IQueryCullingCamera*                cullingCamera;     // 08
		mutable BSSpinLock                  treeLock;          // 10
		mutable BSSpinLock                  branchLock;        // 18
		BSTArray<NiPointer<BSTreeNode>>     loadedTrees;       // 20
		BSTArray<BSTreeNode*>               skinnedTrees;      // 38
		BSTArray<NiPointer<BSLeafAnimNode>> branches;          // 50
		std::uint32_t                       unk68;             // 68
		std::uint32_t                       unk6C;             // 6C
		NiPoint2                            windDirection;     // 70
		float                               windMagnitude;     // 78
		float                               treeUpdateTimer;   // 7C
		float                               midLODSwitchDist;  // 80
		std::uint32_t                       pad84;             // 84
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSTreeManager) == 0x88);
}
