#pragma once

#include "RE/B/BSTriShape.h"

namespace RE
{
	class BSDynamicTriShape : public BSTriShape
	{
	public:
		struct DYNAMIC_TRISHAPE_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT             \
	void*         pDynamicData; /* 00 */ \
	BSSpinLock    lock;         /* 08 */ \
	std::uint32_t dataSize;     /* 10 */ \
	std::uint32_t frameCount;   /* 14 */ \
	std::uint32_t unk1B8;       /* 18 */ \
	std::uint32_t unk1BC;       /* 1C */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(DYNAMIC_TRISHAPE_RUNTIME_DATA) == 0x20);

#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		RUNTIME_DATA_CONTENT;  // 160, 1A8
#endif

		[[nodiscard]] inline DYNAMIC_TRISHAPE_RUNTIME_DATA& GetDynamicTrishapeRuntimeData() noexcept
		{
			return REL::RelocateMember<DYNAMIC_TRISHAPE_RUNTIME_DATA>(this, 0x160, 0x1A8);
		}

		[[nodiscard]] inline const DYNAMIC_TRISHAPE_RUNTIME_DATA& GetDynamicTrishapeRuntimeData() const noexcept
		{
			return REL::RelocateMember<DYNAMIC_TRISHAPE_RUNTIME_DATA>(this, 0x160, 0x1A8);
		}

		BSDynamicTriShape* ctor()
		{
			using func_t = decltype(&BSDynamicTriShape::ctor);
			REL::Relocation<func_t> func{ REL::RelocationID(69564, 70948) };
			return func(this);
		}
		//DEFINE_MEMBER_FN_0(ctor, BSDynamicTriShape*, 0x00C71E50);
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(BSDynamicTriShape) == 0x180);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(BSDynamicTriShape) == 0x1C8);
#endif
}
#undef RUNTIME_DATA_CONTENT
