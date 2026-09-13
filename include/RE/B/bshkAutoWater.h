#pragma once

#include "RE/B/BGSWaterUpdateI.h"
#include "RE/H/hkTransform.h"
#include "RE/H/hkpAabbPhantom.h"

namespace RE
{
	class hkpCollidable;

	namespace BGSWaterCollisionManager
	{
		class bshkAutoWater : public hkpAabbPhantom  // 00
		{
		public:
			inline static constexpr auto RTTI = RTTI_BGSWaterCollisionManager__bshkAutoWater;
			inline static constexpr auto VTABLE = VTABLE_BGSWaterCollisionManager__bshkAutoWater;

			void GetTransform(hkTransform& a_outTransform)
			{
				using func_t = decltype(&bshkAutoWater::GetTransform);
				REL::Relocation<func_t> func{ RELOCATION_ID(31341, 32126) };
				func(this, a_outTransform);
			}

			[[nodiscard]] bool IsActive()
			{
				using func_t = decltype(&bshkAutoWater::IsActive);
				REL::Relocation<func_t> func{ RELOCATION_ID(31342, 32127) };
				return func(this);
			}

			void Update()
			{
				using func_t = decltype(&bshkAutoWater::Update);
				REL::Relocation<func_t> func{ RELOCATION_ID(31343, 32128) };
				func(this);
			}

			void AddOverlappingCollidable(hkpCollidable* a_collidable)
			{
				using func_t = decltype(&bshkAutoWater::AddOverlappingCollidable);
				REL::Relocation<func_t> func{ RELOCATION_ID(31339, 32124) };
				func(this, a_collidable);
			}

			void RemoveOverlappingCollidable(hkpCollidable* a_collidable)
			{
				using func_t = decltype(&bshkAutoWater::RemoveOverlappingCollidable);
				REL::Relocation<func_t> func{ RELOCATION_ID(31340, 32125) };
				func(this, a_collidable);
			}

			// members
			BGSWaterUpdateI updateI;  // 130
		};
		// hkpAabbPhantom's 16-byte SIMD alignment pads this struct's end; don't shrink
		// sizeof to match updateI's own end if a future refactor makes the gap look unused.
		static_assert(offsetof(bshkAutoWater, updateI) == 0x130);
		static_assert(sizeof(bshkAutoWater) == 0x180);
	}
}
