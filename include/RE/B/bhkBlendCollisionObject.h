#pragma once

#include "RE/B/bhkCollisionObject.h"

namespace RE
{
	class bhkWorld;

	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0)
	class bhkBlendCollisionObject : public bhkCollisionObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkBlendCollisionObject;
		inline static constexpr auto Ni_RTTI = NiRTTI_bhkBlendCollisionObject;
		inline static constexpr auto VTABLE = VTABLE_bhkBlendCollisionObject;

		// members
		float         blendStrength;  // 28 - 0 strictly follows the rigid body, 1 strictly follows the node
		float         unk2C;          // 2C
		std::uint32_t motionType;     // 30
		std::uint32_t pad34;          // 34
		bhkWorld*     world;          // 38
		std::uint32_t unk40;          // 40
		std::uint32_t pad44;          // 44
	};
	static_assert(sizeof(bhkBlendCollisionObject) == 0x48);
}
