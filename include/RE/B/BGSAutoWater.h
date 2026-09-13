#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTSingleton.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSMultiBoundAABB;
	class NiAVObject;
	class TESObjectCELL;

	class BGSAutoWater : public BSTSingletonSDM<BGSAutoWater>
	{
	public:
		static BGSAutoWater* GetSingleton();

		void GenerateMultibounds(TESObjectCELL* a_cell);
		void GeneratePlaceableWater(TESObjectCELL* a_cell, NiAVObject* a_water);
		void GeneratePlaceableWaterForCell(TESObjectCELL* a_cell, bool a_unk);

		// members
		std::uint8_t                          pad0001;                        // 0001
		std::uint16_t                         pad0002;                        // 0002
		std::uint32_t                         pad0004;                        // 0004
		std::uint8_t                          unk0008[0x2020];                // 0008 - related to flow map
		BSTArray<NiPointer<BSMultiBoundAABB>> multiBounds;                    // 2028
		NiPointer<NiAVObject>                 defaultCellWaterObject;         // 2040
		NiPointer<NiAVObject>                 defaultCellWaterRipplesObject;  // 2048
	};
	static_assert(sizeof(BGSAutoWater) == 0x2050);
}
