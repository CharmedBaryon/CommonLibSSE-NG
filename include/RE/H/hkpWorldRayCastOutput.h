#pragma once

#include "RE/H/hkpShapeRayCastOutput.h"

namespace RE
{
	class hkpCollidable;

	struct hkpWorldRayCastOutput : public hkpShapeRayCastOutput
	{
	public:
		[[nodiscard]] constexpr bool HasHit() const noexcept { return rootCollidable != nullptr; }

		constexpr void Reset() noexcept
		{
			hkpShapeRayCastOutput::Reset();
			rootCollidable = nullptr;
		}

		// members
		const hkpCollidable* rootCollidable{ nullptr };  // 50
		std::uint64_t        pad58;                      // 58
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpWorldRayCastOutput) == 0x60);
}
