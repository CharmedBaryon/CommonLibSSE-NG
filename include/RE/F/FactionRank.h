#pragma once

namespace RE
{
	class TESFaction;

	struct FACTION_RANK  // SNAM
	{
	public:
		// members
		TESFaction*   faction;     // 00
		std::int8_t   rank;        // 08
		std::uint8_t  pad09{ 0 };  // 09
		std::uint16_t pad0A{ 0 };  // 0A
		std::uint32_t pad0C{ 0 };  // 0C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(FACTION_RANK) == 0x10);
}
