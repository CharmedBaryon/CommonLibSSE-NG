#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStringPtr.h"
#include "RE/H/hkbBehaviorGraphStringData.h"
#include "RE/H/hkbVariableInfo.h"
#include "RE/H/hkbVariableValueSet.h"

namespace RE
{

	struct hkbEventInfo
	{
	public:
		constexpr hkbEventInfo() :
			m_flags(Flags(0)) {}

		/// Whether or not this event should be treated as a sync point.
		bool isSyncPoint() { return (m_flags.get() & FLAG_SYNC_POINT) != 0; }

		/// Whether or not this event should be raised by clip generators.
		bool isSilent() { return (m_flags.get() & FLAG_SILENT) != 0; }

		/// Definitions of flags that influence the behavior of events.
		enum Flags
		{
			/// Whether or not clip generators should raise the event.
			FLAG_SILENT = 0x1,

			/// Whether or not the sync point will be
			FLAG_SYNC_POINT = 0x2,
		};

		/// The flags that influence the behavior of events.
		stl::enumeration<Flags, std::uint32_t> m_flags;
	};
	static_assert(sizeof(hkbEventInfo) == 0x4);

	class hkbBehaviorGraphData : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbBehaviorGraphData;
		inline static constexpr auto VTABLE = VTABLE_hkbBehaviorGraphData;

		virtual ~hkbBehaviorGraphData() = default;  // 00

		bool HasEventString(hkStringPtr a_name);
		bool HasVariableString(hkStringPtr a_name);

		int AddBoolVariable(hkStringPtr a_name, bool a_value);
		int AddIntVariable(hkStringPtr a_name, std::int32_t a_value);
		int AddFloatVariable(hkStringPtr a_name, float a_value);
		int AddEvent(hkStringPtr a_name);

		// members
		hkArray<float>                       attributeDefaults;       // 10
		hkArray<hkbVariableInfo>             variableInfos;           // 20
		hkArray<hkbVariableInfo>             characterPropertyInfos;  // 30
		hkArray<hkbEventInfo>                eventInfos;              // 40
		hkArray<hkbVariableBounds>           variableBounds;          // 50
		uint64_t                             unk60;                   // 60
		uint64_t                             unk68;                   // 68
		hkbVariableValueSet*                 variableInitialValues;   // 70
		hkRefPtr<hkbBehaviorGraphStringData> stringData;              // 78
	};
	static_assert(sizeof(hkbBehaviorGraphData) == 0x80);

}
