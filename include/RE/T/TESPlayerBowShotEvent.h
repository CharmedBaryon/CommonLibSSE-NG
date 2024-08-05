#pragma once

namespace RE
{
	struct TESPlayerBowShotEvent
	{
	public:
		// members
		FormID weapon;       // 00
		FormID ammo;         // 04
		float  shotPower;    // 08
		bool   isSunGazing;  // 09
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESPlayerBowShotEvent) == 0x10);
}
