#pragma once

#include "RE/B/BSTriShape.h"

namespace RE
{
	class BSDynamicTriShape : public BSTriShape
	{
	public:
		void*         pDynamicData;  // 1A0
		BSSpinLock    lock;          // 1A8
		std::uint32_t dataSize;      // 1B0
		std::uint32_t frameCount;    // 1B4
		std::uint32_t unk1B8;        // 1B8
		std::uint32_t unk1BC;        // 1BC

		BSDynamicTriShape* ctor()
		{
			using func_t = decltype(&BSDynamicTriShape::ctor);
			REL::Relocation<func_t> func{ REL::Offset(0x00C71E50) };
			return func(this);
		}
		//DEFINE_MEMBER_FN_0(ctor, BSDynamicTriShape*, 0x00C71E50);
	};
#if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(BSDynamicTriShape) == 0x1C8);
#else
	static_assert(sizeof(BSDynamicTriShape) == 0x180);
#endif
}
