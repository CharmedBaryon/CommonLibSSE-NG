#pragma once

#include "RE/H/hkArray.h"

namespace RE
{
	class bhkWorld;
	class hkpRigidBody;

	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0)
	class BGSFootIkRaycastInterfaceDB
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSFootIkRaycastInterfaceDB;
		inline static constexpr auto VTABLE = VTABLE_BGSFootIkRaycastInterfaceDB;

		struct CachedRaycastData
		{
		public:
			// members
			void*         vtbl;         // 00
			std::uint32_t handle;       // 08
			std::uint32_t pad0C;        // 0C
			std::uint64_t unk10;        // 10
			hkpRigidBody* rigidBody;    // 18
			bhkWorld*     world;        // 20
			std::uint32_t unk28;        // 28
			std::uint32_t unk2C;        // 2C
			bool          isSupported;  // 30
		};
		static_assert(offsetof(CachedRaycastData, isSupported) == 0x30);

		// members
		void*                      vtbl;         // 00
		std::uint8_t               unk08[0x38];  // 08
		hkArray<CachedRaycastData> raycastData;  // 40
	};
	static_assert(offsetof(BGSFootIkRaycastInterfaceDB, raycastData) == 0x40);
}
