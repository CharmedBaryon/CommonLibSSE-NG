#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkVector4.h"
#include "RE/H/hkbCharacterControllerSetup.h"

namespace RE
{
	class hkbCharacterStringData;
	class hkbFootIkDriverInfo;
	class hkbHandIkDriverInfo;
	class hkbVariableInfo;
	class hkbVariableValueSet;

	class hkbCharacterData : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbCharacterData;
		inline static constexpr auto VTABLE = VTABLE_hkbCharacterData;

		// members
		std::uint8_t                     characterControllerSetup[24];  // 10 (hkbCharacterControllerSetup)
		float                            modelUpMS[4];                  // 28 (hkVector4)
		float                            modelForwardMS[4];             // 38 (hkVector4)
		float                            modelRightMS[4];               // 48 (hkVector4)
		hkArray<hkbVariableInfo>         characterPropertyInfos;        // 58
		hkArray<std::int32_t>            numBonesPerLod;                // 68
		hkRefPtr<hkbVariableValueSet>    characterPropertyValues;       // 78
		hkRefPtr<hkbFootIkDriverInfo>    footIkDriverInfo;              // 80
		hkRefPtr<hkbHandIkDriverInfo>    handIkDriverInfo;              // 88
		hkRefPtr<hkReferencedObject>     aiControlDriverInfo;           // 90
		hkRefPtr<hkbCharacterStringData> stringData;                    // 98
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkbCharacterData) == 0xA0);  // B0?
}
