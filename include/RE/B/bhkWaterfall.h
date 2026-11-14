#pragma once

#include "RE/B/BGSWaterUpdateI.h"
#include "RE/H/hkTransform.h"
#include "RE/H/hkpPhantomCallbackShape.h"

namespace RE
{
	class hkpCollidable;

	namespace BGSWaterCollisionManager
	{
		// trailing size beyond hkpPhantomCallbackShape (0x20) + updateI (0x48) not independently
		// confirmed -- non-constructible until it is; only use via a pointer the engine already owns
		class bhkWaterfall : public hkpPhantomCallbackShape  // 00
		{
		public:
			bhkWaterfall() = delete;

			inline static constexpr auto RTTI = RTTI_BGSWaterCollisionManager__bhkWaterfall;
			inline static constexpr auto VTABLE = VTABLE_BGSWaterCollisionManager__bhkWaterfall;

			void GetTransform(hkTransform& a_outTransform)
			{
				using func_t = decltype(&bhkWaterfall::GetTransform);
				REL::Relocation<func_t> func{ RELOCATION_ID(19617, 20019) };
				func(this, a_outTransform);
			}

			[[nodiscard]] bool IsActive()
			{
				using func_t = decltype(&bhkWaterfall::IsActive);
				REL::Relocation<func_t> func{ RELOCATION_ID(31323, 32107) };
				return func(this);
			}

			void Update()
			{
				using func_t = decltype(&bhkWaterfall::Update);
				REL::Relocation<func_t> func{ RELOCATION_ID(31324, 32108) };
				func(this);
			}

			void AddOverlappingCollidable(hkpCollidable* a_collidable)
			{
				using func_t = decltype(&bhkWaterfall::AddOverlappingCollidable);
				REL::Relocation<func_t> func{ RELOCATION_ID(31321, 32105) };
				func(this, a_collidable);
			}

			void RemoveOverlappingCollidable(hkpCollidable* a_collidable)
			{
				using func_t = decltype(&bhkWaterfall::RemoveOverlappingCollidable);
				REL::Relocation<func_t> func{ RELOCATION_ID(31322, 32106) };
				func(this, a_collidable);
			}

			// members
			BGSWaterUpdateI updateI;  // 20
		};
	}
}
