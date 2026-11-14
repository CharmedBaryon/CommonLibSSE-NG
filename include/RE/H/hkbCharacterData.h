#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkVector4.h"

namespace RE
{
	class hkbCharacterStringData;
	class hkbFootIkDriverInfo;
	class hkbHandIkDriverInfo;
	class hkbMirroredSkeletonInfo;
	class hkbVariableInfo;
	class hkbVariableValueSet;

	// Layout ported from https://github.com/adamhynek/activeragdoll (GPL-3.0), with
	// the leading region's split and unk20/unk28/A8-AE's boundaries independently
	// confirmed via this class's own destructor (RemoveReference offsets, and
	// characterPropertyInfos/numBonesPerLod landing exactly at 0x60/0x70).
	class hkbCharacterData : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbCharacterData;
		inline static constexpr auto VTABLE = VTABLE_hkbCharacterData;

		// members
		float                             unk10;                    // 10
		float                             unk14;                    // 14
		std::uint64_t                     unk18;                    // 18
		hkRefPtr<hkReferencedObject>      unk20;                    // 20 - ref-counted ptr, concrete type not yet named
		std::uint64_t                     unk28;                    // 28
		float                             modelUpMS[4];             // 30 (hkVector4)
		float                             modelForwardMS[4];        // 40 (hkVector4)
		float                             modelRightMS[4];          // 50 (hkVector4)
		hkArray<hkbVariableInfo>          characterPropertyInfos;   // 60
		hkArray<std::int32_t>             numBonesPerLod;           // 70
		hkRefPtr<hkbVariableValueSet>     characterPropertyValues;  // 80
		hkRefPtr<hkbFootIkDriverInfo>     footIkDriverInfo;         // 88
		hkRefPtr<hkbHandIkDriverInfo>     handIkDriverInfo;         // 90
		hkRefPtr<hkbCharacterStringData>  stringData;               // 98 - identity vs. mirroredSkeletonInfo below not yet distinguished
		hkRefPtr<hkbMirroredSkeletonInfo> mirroredSkeletonInfo;     // A0 - identity vs. stringData above not yet distinguished
		float                             scale;                    // A8
		std::int16_t                      numHands;                 // AC
		std::int16_t                      numFloatSlots;            // AE
	};
	static_assert(sizeof(hkbCharacterData) == 0xB0);
}
