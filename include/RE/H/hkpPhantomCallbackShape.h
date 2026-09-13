#pragma once

#include "RE/H/hkpShape.h"

namespace RE
{
	class hkpPhantomCallbackShape : public hkpShape
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpPhantomCallbackShape;
		inline static constexpr auto VTABLE = VTABLE_hkpPhantomCallbackShape;
	};
	static_assert(sizeof(hkpPhantomCallbackShape) == 0x20);
}
