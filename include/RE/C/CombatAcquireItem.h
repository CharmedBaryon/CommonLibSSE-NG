#pragma once

namespace RE
{
	class TESBoundObject;

	class CombatAcquireItem
	{
	public:
		bool IsValid() const;

		//members
		RefHandle       targetHandle;  // 00
		uint32_t        field_4;       // 04
		TESBoundObject* item;          // 08
		float           score;         // 10
		uint32_t        field_14;      // 14
	};
	static_assert(sizeof(CombatAcquireItem) == 0x18);
}
