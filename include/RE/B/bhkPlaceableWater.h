#pragma once

#include "RE/B/BGSWaterUpdateI.h"
#include "RE/H/hkTransform.h"
#include "RE/H/hkpPhantomCallbackShape.h"

namespace RE
{
	class hkpCollidable;

	namespace BGSWaterCollisionManager
	{
		class bhkPlaceableWater : public hkpPhantomCallbackShape  // 00
		{
		public:
			inline static constexpr auto RTTI = RTTI_BGSWaterCollisionManager__bhkPlaceableWater;
			inline static constexpr auto VTABLE = VTABLE_BGSWaterCollisionManager__bhkPlaceableWater;

			void GetTransform(hkTransform& a_outTransform)
			{
				using func_t = decltype(&bhkPlaceableWater::GetTransform);
				REL::Relocation<func_t> func{ RELOCATION_ID(31316, 32100) };
				func(this, a_outTransform);
			}

			[[nodiscard]] bool IsActive()
			{
				using func_t = decltype(&bhkPlaceableWater::IsActive);
				REL::Relocation<func_t> func{ RELOCATION_ID(31317, 32101) };
				return func(this);
			}

			void Update()
			{
				using func_t = decltype(&bhkPlaceableWater::Update);
				REL::Relocation<func_t> func{ RELOCATION_ID(31319, 32103) };
				func(this);
			}

			// removes then immediately re-adds every tracked collidable
			void RefreshOverlaps()
			{
				using func_t = decltype(&bhkPlaceableWater::RefreshOverlaps);
				REL::Relocation<func_t> func{ RELOCATION_ID(31318, 32102) };
				func(this);
			}

			// calls hkpWorld::getPenetrations and forwards results into Add/RemoveOverlappingCollidable
			void CheckPenetrations()
			{
				using func_t = decltype(&bhkPlaceableWater::CheckPenetrations);
				REL::Relocation<func_t> func{ RELOCATION_ID(31309, 32093) };
				func(this);
			}

			void NotifyCollidableEntered(hkpCollidable* a_collidable)
			{
				using func_t = decltype(&bhkPlaceableWater::NotifyCollidableEntered);
				REL::Relocation<func_t> func{ RELOCATION_ID(31313, 32097) };
				func(this, a_collidable);
			}

			void NotifyCollidableExited(hkpCollidable* a_collidable)
			{
				using func_t = decltype(&bhkPlaceableWater::NotifyCollidableExited);
				REL::Relocation<func_t> func{ RELOCATION_ID(31314, 32098) };
				func(this, a_collidable);
			}

			// members
			BGSWaterUpdateI updateI;     // 20
			std::uint32_t   usageCount;  // 68
			std::uint32_t   pad6C;       // 6C
		};
		static_assert(sizeof(bhkPlaceableWater) == 0x70);
	}
}
