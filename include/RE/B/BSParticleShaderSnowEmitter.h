#pragma once

#include "RE/B/BSParticleShaderCubeEmitter.h"

namespace RE
{
	class BSParticleShaderSnowEmitter : public BSParticleShaderCubeEmitter
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSParticleShaderSnowEmitter;
		inline static constexpr auto VTABLE = VTABLE_BSParticleShaderSnowEmitter;

		~BSParticleShaderSnowEmitter() override;  // 00
	};
	static_assert(sizeof(BSParticleShaderSnowEmitter) == 0xFE0);
}
