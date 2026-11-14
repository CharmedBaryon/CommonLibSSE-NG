#pragma once

#include "RE/N/NiTriBasedGeometry.h"

namespace RE
{
	// Adds nothing over NiTriBasedGeometry; exists to allocate this type, set the real
	// vtable, and reach the inherited base fields.
	class NiTriStrips : public NiTriBasedGeometry
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiTriStrips;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiTriStrips;
		inline static constexpr auto VTABLE = VTABLE_NiTriStrips;
	};
	STATIC_ASSERT_SIZE(NiTriStrips, 0x138, 0x138, 0x160, 0x110);
}
