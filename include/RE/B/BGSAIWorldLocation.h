#pragma once

#include "RE/I/IAIWorldLocation.h"

namespace RE
{
	class BGSAIWorldLocation : public IAIWorldLocation
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSAIWorldLocation;
		inline static constexpr auto VTABLE = VTABLE_BGSAIWorldLocation;

		~BGSAIWorldLocation() override;  // 00
	};
	static_assert(sizeof(BGSAIWorldLocation) == 0x8);
}
