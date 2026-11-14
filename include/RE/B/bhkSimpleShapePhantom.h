#pragma once

#include "RE/H/hkRefPtr.h"
#include "RE/N/NiRefObject.h"

namespace RE
{
	class hkpSimpleShapePhantom;

	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0)
	class bhkSimpleShapePhantom : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkSimpleShapePhantom;
		inline static constexpr auto VTABLE = VTABLE_bhkSimpleShapePhantom;

		// members
		hkRefPtr<hkpSimpleShapePhantom> phantom;  // 10
	};
	static_assert(sizeof(bhkSimpleShapePhantom) == 0x18);
}
