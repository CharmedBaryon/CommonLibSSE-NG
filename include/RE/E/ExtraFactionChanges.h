#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSTArray.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/F/FactionRank.h"

namespace RE
{
	class TESFaction;

	class ExtraFactionChanges : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraFactionChanges;
		inline static constexpr auto VTABLE = VTABLE_ExtraFactionChanges;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kFactionChanges;

		~ExtraFactionChanges() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 - { return kFactionChanges; }

		// members
		BSTArray<FACTION_RANK> factionChanges;      // 10
		TESFaction*            crimeFaction;        // 28
		bool                   removeCrimeFaction;  // 30
		std::uint8_t           pad31;               // 31
		std::uint16_t          pad32;               // 32
		std::uint32_t          pad34;               // 34
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraFactionChanges) == 0x38);
}
