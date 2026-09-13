#pragma once

#include "RE/H/hkRefPtr.h"

namespace RE
{
	class hkbEventPayload;

	class hkbEventBase
	{
	public:
		enum SystemEventIDs : std::uint32_t
		{
			kNull = static_cast<std::underlying_type_t<SystemEventIDs>>(-1)
		};

		// members
		SystemEventIDs            id;       // 00
		std::uint32_t             pad04;    // 04
		hkRefPtr<hkbEventPayload> payload;  // 08
	};
	static_assert(sizeof(hkbEventBase) == 0x10);

	class hkbEventPayload : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbEventPayload;
		inline static constexpr auto VTABLE = VTABLE_hkbEventPayload;
	};
	static_assert(sizeof(hkbEventPayload) == 0x10);

}
