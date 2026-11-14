#pragma once

#include "RE/B/BGSAIWorldLocation.h"
#include "RE/B/BGSTypedItem.h"
#include "RE/B/BSPointerHandle.h"

namespace RE
{
	class BGSAIWorldLocationRefRadius : public BGSTypedItem<BGSAIWorldLocationRefRadius, BGSAIWorldLocation>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSAIWorldLocationRefRadius;
		inline static constexpr auto VTABLE = VTABLE_BGSAIWorldLocationRefRadius;

		~BGSAIWorldLocationRefRadius() override;  // 00

		// members
		ObjectRefHandle ref;              // 08
		float           radius;           // 0C
		float           heightTolerance;  // 10
		float           angleTolerance;   // 14
		bool            isMinimumRadius;  // 18
		std::uint8_t    pad19;            // 19
		std::uint16_t   pad1A;            // 1A
		std::uint32_t   pad1C;            // 1C
	};
	static_assert(sizeof(BGSAIWorldLocationRefRadius) == 0x20);
}
