#pragma once

#include "RE/B/BSTArray.h"

namespace RE
{
	class bhkRigidBody;
	class hkpCollidable;
	class TESWaterForm;

	namespace BGSWaterCollisionManager
	{
		class BGSWaterUpdateI
		{
		public:
			enum Flag : std::uint32_t
			{
				kNone = 0,
				kInert = 1 << 0,
			};

			inline static constexpr auto RTTI = RTTI_BGSWaterCollisionManager__BGSWaterUpdateI;
			inline static constexpr auto VTABLE = VTABLE_BGSWaterCollisionManager__BGSWaterUpdateI;

			void Link()
			{
				using func_t = decltype(&BGSWaterUpdateI::Link);
				REL::Relocation<func_t> func{ RELOCATION_ID(31307, 32091) };
				func(this);
			}

			void Unlink()
			{
				using func_t = decltype(&BGSWaterUpdateI::Unlink);
				REL::Relocation<func_t> func{ RELOCATION_ID(31303, 32087) };
				func(this);
			}

			// a_disabled removes this water volume from collision/update processing
			void SetDisabled(bool a_disabled)
			{
				using func_t = decltype(&BGSWaterUpdateI::SetDisabled);
				REL::Relocation<func_t> func{ RELOCATION_ID(31302, 32086) };
				func(this, a_disabled);
			}

			void SetContext(void* a_context)
			{
				using func_t = decltype(&BGSWaterUpdateI::SetContext);
				REL::Relocation<func_t> func{ RELOCATION_ID(31301, 32085) };
				func(this, a_context);
			}

			void UpdateCameraInWater()
			{
				using func_t = decltype(&BGSWaterUpdateI::UpdateCameraInWater);
				REL::Relocation<func_t> func{ RELOCATION_ID(31306, 32090) };
				func(this);
			}

			bool AddOverlappingCollidable(hkpCollidable* a_collidable)
			{
				using func_t = decltype(&BGSWaterUpdateI::AddOverlappingCollidable);
				REL::Relocation<func_t> func{ RELOCATION_ID(31311, 32095) };
				return func(this, a_collidable);
			}

			bool RemoveOverlappingCollidable(hkpCollidable* a_collidable)
			{
				using func_t = decltype(&BGSWaterUpdateI::RemoveOverlappingCollidable);
				REL::Relocation<func_t> func{ RELOCATION_ID(31312, 32096) };
				return func(this, a_collidable);
			}

			// members
			void*                             vftable;        // 00
			REX::EnumSet<Flag, std::uint32_t> flags;          // 08
			std::uint32_t                     pad0C;          // 0C
			BSTArray<void*>                   trackedBodies;  // 10
			BGSWaterUpdateI*                  next;           // 28
			TESWaterForm*                     waterType;      // 30
			void*                             context;        // 38
			bhkRigidBody*                     body;           // 40
		};
		static_assert(sizeof(BGSWaterUpdateI) == 0x48);
	}
}
