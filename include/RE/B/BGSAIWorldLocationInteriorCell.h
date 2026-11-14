#pragma once

#include "RE/B/BGSAIWorldLocation.h"
#include "RE/B/BGSTypedItem.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class TESObjectCELL;

	class BGSAIWorldLocationInteriorCell : public BGSTypedItem<BGSAIWorldLocationInteriorCell, BGSAIWorldLocation>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSAIWorldLocationInteriorCell;
		inline static constexpr auto VTABLE = VTABLE_BGSAIWorldLocationInteriorCell;

		~BGSAIWorldLocationInteriorCell() override;  // 00

		// members
		TESObjectCELL* cell;      // 08
		NiPoint3       position;  // 10
		std::uint32_t  pad1C;     // 1C
	};
	static_assert(sizeof(BGSAIWorldLocationInteriorCell) == 0x20);
}
