#pragma once

#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStringPtr.h"

namespace RE
{
	class hkLocalFrameGroup : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkLocalFrameGroup;
		inline static constexpr auto VTABLE = VTABLE_hkLocalFrameGroup;

		~hkLocalFrameGroup() override;  // 00

		// members
		hkStringPtr name;  // 10
	};
	static_assert(sizeof(hkLocalFrameGroup) == 0x18);
}
