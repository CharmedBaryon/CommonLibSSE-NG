#pragma once

#include "RE/H/hkbBehaviorGraphStringData.h"

namespace RE
{
	class hkbVariableInfo;
	class hkbEventInfo;
	class hkbVariableBounds;
	class hkbVariableValueSet;

	class hkbBehaviorGraphData : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbBehaviorGraphData;
		inline static constexpr auto VTABLE = VTABLE_hkbBehaviorGraphData;

		virtual ~hkbBehaviorGraphData() = default;  // 00

		// members
		hkArray<float>                       attributeDefaults;       // 10
		hkArray<hkbVariableInfo>             variableInfos;           // 20
		hkArray<hkbVariableInfo>             characterPropertyInfos;  // 30
		hkArray<hkbVariableInfo>             eventInfos;              // 40
		hkArray<hkbVariableBounds>           variableBounds;          // 50
		uint64_t                             unk60;                   // 60
		uint64_t                             unk68;                   // 68
		hkbVariableValueSet*                 variableInitialValues;   // 70
		hkRefPtr<hkbBehaviorGraphStringData> stringData;              // 78
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkbBehaviorGraphData) == 0x80);
}
