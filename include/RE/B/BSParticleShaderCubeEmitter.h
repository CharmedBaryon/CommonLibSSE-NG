#pragma once

#include "RE/B/BSParticleShaderEmitter.h"
#include "RE/N/NiPoint3.h"

#include "REX/W32/D3D.h"

namespace RE
{
	class BSParticleShaderCubeEmitter : public BSParticleShaderEmitter
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSParticleShaderCubeEmitter;
		inline static constexpr auto VTABLE = VTABLE_BSParticleShaderCubeEmitter;

		~BSParticleShaderCubeEmitter() override;  // 00

		// override (BSParticleShaderEmitter)
		bool Generate(bool a_arg1, NiPoint3& a_arg2, NiPoint3& a_arg3) override;  // 03 - { return false; }

		// members
		alignas(0x10) REX::W32::XMFLOAT4X4 occlusionProjection;  // ED0
		NiPoint3 cameraOffsetVector;                             // F10
		NiPoint3 offsetVector;                                   // F1C
		NiPoint3 compositeOffsetVector;                          // F28
		NiPoint3 frameVelocityVector;                            // F34
		NiPoint3 windVelocity;                                   // F40
		NiPoint3 gravityVelocity;                                // F4C
		float    rotation;                                       // F58
		float    rotationVelocity;                               // F5C
		float    cubeSize;                                       // F60
		float    density;                                        // F64
		NiPoint3 instanceOffsets[10];                            // F68
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSParticleShaderCubeEmitter) == 0xFE0);
}
