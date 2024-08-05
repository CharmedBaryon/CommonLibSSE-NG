#pragma once

#include "RE/B/BSImagespaceShader.h"

namespace RE
{
	class BSImagespaceShaderISTemporalAA : public BSImagespaceShader
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSImagespaceShaderISTemporalAA;

		~BSImagespaceShaderISTemporalAA() override;  // 00

		// override (BSImagespaceShader)

		// members
		std::uint64_t unk1A8;  // 1A8
		std::uint64_t unk1B0;  // 1B0
		std::uint64_t unk1B8;  // 1B8
	};
	static_assert(sizeof(BSImagespaceShaderISTemporalAA) == 0x1C0);
}
