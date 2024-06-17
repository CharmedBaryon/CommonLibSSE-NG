#pragma once

#include "RE/B/BSShader.h"

namespace RE
{
	class BSLightingShader : public BSShader
	{
	public:
		uint32_t unk90;                // 90
		uint32_t currentRawTechnique;  // 94
		uint64_t unk98;                // 98
		uint64_t unkA0;                // A0
		uint64_t unkA8;                // A8
		uint64_t unkB0;                // B0
		uint64_t unkB8;                // B8
		uint64_t unkC0;                // C0
		uint64_t unkC8;                // C8
		uint64_t unkD0;                // D0
		uint64_t unkD8;                // D8
		uint64_t unkE0;                // E0
		uint64_t unkE8;                // E8
		uint64_t unkF0;                // F0

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSLightingShader) == 0xF8);
}
