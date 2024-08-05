#pragma once

#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkVector4.h"

namespace RE
{
	class hkbProjectStringData;

	class hkbProjectData : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbProjectData;
		inline static constexpr auto VTABLE = VTABLE_hkbProjectData;

		// members
		hkVector4                      worldUpWS;         // 10
		hkRefPtr<hkbProjectStringData> stringData;        // 20
		std::uint8_t                   defaultEventNode;  // 28 (hkEnum<hkbTransitionEffect::EventMode, hkInt8>)
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkbProjectData) == 0x30);
}
