#pragma once

#include "RE/B/BSParticleShaderCubeEmitter.h"

namespace RE
{
	class BSParticleShaderRainEmitter : public BSParticleShaderCubeEmitter
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSParticleShaderRainEmitter;
		inline static constexpr auto VTABLE = VTABLE_BSParticleShaderRainEmitter;

		~BSParticleShaderRainEmitter() override;  // 00
	};
	static_assert(sizeof(BSParticleShaderRainEmitter) == 0xFE0);
}
