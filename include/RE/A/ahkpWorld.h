#pragma once

#include "RE/H/hkpWorld.h"

namespace RE
{
	class bhkWorld;

	class ahkpWorld : public hkpWorld
	{
	public:
		inline static constexpr auto RTTI = RTTI_ahkpWorld;
		inline static constexpr auto VTABLE = VTABLE_ahkpWorld;

		~ahkpWorld() override;  // 00

		// members
		bhkWorld*     userData;  // 430
		std::uint64_t unk438;    // 438
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ahkpWorld) == 0x440);
}
