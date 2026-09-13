#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiRefObject.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTPointerList.h"

namespace RE
{
	class BSMultiBoundRoom;
	class BSOcclusionShape;
	class BSPortal;
	class BSPortalGraphEntry;
	class BSPortalSharedNode;
	class NiAVObject;
	class NiNode;

	class BSPortalGraph : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPortalGraph;
		inline static constexpr auto VTABLE = VTABLE_BSPortalGraph;

		template <typename T>
		struct ListEntry
		{
			ListEntry<T>* next;   // 00
			ListEntry<T>* prev;   // 08
			T*            value;  // 10
		};
		static_assert(sizeof(ListEntry<BSPortal>) == 0x18);

		template <typename T>
		struct List
		{
			ListEntry<T>* first;  // 00
			ListEntry<T>* last;   // 08
			uint32_t      count;  // 10
		};
		static_assert(sizeof(List<BSPortal>) == 0x18);

		~BSPortalGraph() override;  // 00

		// add
		bool IsCompatibleEntry(const BSPortalGraphEntry* a_entry) const;

		// members
		NiTPointerList<BSOcclusionShape>      occlusionShapes;       // 10
		NiTPointerList<BSPortal>              portals;               // 28
		BSTArray<NiPointer<BSMultiBoundRoom>> rooms;                 // 40
		BSTArray<NiPointer<NiAVObject>>       alwaysRenderChildren;  // 58
		NiPointer<BSPortalSharedNode>         portalSharedNode;      // 70
		BSTArray<NiPointer<NiAVObject>>       unk78;                 // 78
		BSTArray<NiPointer<NiAVObject>>       unk90;                 // 90
		BSTArray<NiPointer<NiNode>>           unkA8;                 // A8
		FormID                                cellID;                // C0
		std::uint32_t                         padC4;                 // C4
	};
	static_assert(sizeof(BSPortalGraph) == 0xC8);
}
