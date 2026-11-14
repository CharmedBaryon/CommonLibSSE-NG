#pragma once

#include "RE/B/BSCompoundFrustum.h"
#include "RE/B/BSMultiBoundRoom.h"
#include "RE/B/BSTHashMap.h"
#include "RE/N/NiRefObject.h"
#include "RE/N/NiSmartPointer.h"
#include "REL/Relocation.h"

namespace RE
{
	class BSPortalGraph;
	class NiNode;

	class BSPortalGraphEntry : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPortalGraphEntry;
		inline static constexpr auto VTABLE = VTABLE_BSPortalGraphEntry;

		~BSPortalGraphEntry() override;  // 00

		void SetPortalGraph(BSPortalGraph* a_portalGraph);
		void AddVisibilityToMap(void* a_space, BSCompoundFrustum* a_compoundFrustum);
		void ClearVisibility();
		bool HasSharedRoomVisibility(BSPortalGraphEntry* a_second)
		{
			using func_t = bool (*)(BSPortalGraphEntry*, BSPortalGraphEntry*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(74397, 76121) };
			return func(this, a_second);
		}

		// members
		BSPortalGraph*                          portalGraph;              // 10
		BSTArray<NiPointer<BSMultiBoundRoom>>   multiBoundRoomAccumList;  // 18
		NiPointer<BSMultiBoundRoom>             multiBoundRoomRoot;       // 30
		BSTHashMap<NiNode*, BSCompoundFrustum*> visibilityMap;            // 38
		BSCompoundFrustum                       compoundFrustum;          // 68
		bool                                    visibleUnboundSpace;      // 130
		bool                                    enableAccumulation;       // 131
		std::byte                               pad132[2];                // 132
		std::uint32_t                           unk134;                   // 134
		uint32_t                                cellId;                   // 138
	};
	static_assert(sizeof(BSPortalGraphEntry) == 0x140);
}
