#pragma once

#include "RE/B/BGSAIWorldLocation.h"
#include "RE/B/BGSTypedItem.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class TESObjectCELL;
	class TESWorldSpace;

	class BGSAIWorldLocationPointRadius : public BGSTypedItem<BGSAIWorldLocationPointRadius, BGSAIWorldLocation>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSAIWorldLocationPointRadius;
		inline static constexpr auto VTABLE = VTABLE_BGSAIWorldLocationPointRadius;

		~BGSAIWorldLocationPointRadius() override;  // 00

		// members
		NiPoint3       position;         // 08
		std::uint32_t  pad14;            // 14
		TESObjectCELL* cell;             // 18
		TESWorldSpace* worldSpace;       // 20
		float          radius;           // 28
		float          facing;           // 2C
		bool           hasFacing;        // 30
		bool           isMinimumRadius;  // 31
		std::uint16_t  pad32;            // 32
		std::uint32_t  pad34;            // 34
	};
	static_assert(sizeof(BGSAIWorldLocationPointRadius) == 0x38);
}
