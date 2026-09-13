#pragma once

#include "RE/B/BSString.h"

namespace RE
{
	class TESForm;

	class MagicItemData
	{
	public:
		inline static constexpr auto RTTI = RTTI_MagicItemData;
		inline static constexpr auto VTABLE = VTABLE_MagicItemData;

		virtual ~MagicItemData();  // 00

		virtual const char*   GetName();        // 01
		virtual std::uint32_t GetCount();       // 02 - { return 1; }
		virtual std::uint32_t GetEquipState();  // 03
		virtual std::uint32_t GetFilterFlag();  // 04
		virtual bool          GetFavorite();    // 05
		virtual bool          GetEnabled();     // 06

		// members
		BSString effectDesc;  // 08
		TESForm* baseForm;    // 18
	};
	static_assert(sizeof(MagicItemData) == 0x20);
}
