#pragma once

#include "RE/N/NiRefObject.h"

namespace RE
{
	class BSParticleShaderProperty;
	class NiAVObject;

	class BSParticleShaderEmitter : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSParticleShaderEmitter;
		inline static constexpr auto VTABLE = VTABLE_BSParticleShaderEmitter;

		enum class EMITTER_TYPE
		{
			kGeometry = 0,
			kCollision = 1,
			kRay = 2,
			kSnow = 3,
			kRain = 4
		};

		class TextureAnimInfo
		{
		public:
			// members
			float         currentFrame;  // 00
			std::uint32_t totalFrames;   // 04
		};
		static_assert(sizeof(TextureAnimInfo) == 0x08);

		struct ParticleData
		{
		public:
			// members
			float        XPos;           // 00
			float        YPos;           // 04
			float        ZPos;           // 08
			float        age;            // 0C
			float        XVel;           // 10
			float        YVel;           // 14
			float        ZVel;           // 18
			float        lifeAdjust;     // 1C
			float        rotationStart;  // 20
			float        rotationSpeed;  // 24
			float        speedMult;      // 28
			std::uint8_t texCoordU;      // 2C
			std::uint8_t texCoordV;      // 2D
			std::uint8_t vertexX;        // 2E
			std::uint8_t vertexY;        // 2F
		};
		static_assert(sizeof(ParticleData) == 0x30);

		virtual ~BSParticleShaderEmitter();  // 00

		// add
		virtual NiAVObject* GetBoundsObject();                                              // 02
		virtual bool        Generate(bool a_arg1, NiPoint3& a_arg2, NiPoint3& a_arg3) = 0;  // 03

		// members
		BSParticleShaderProperty*                     property;          // 10
		stl::enumeration<EMITTER_TYPE, std::uint16_t> emitterType;       // 18
		std::uint16_t                                 particleCount;     // 1A
		float                                         alpha;             // 1C
		float                                         generateReminder;  // 20
		float                                         maxParticleRatio;  // 24
		TextureAnimInfo*                              textureAnims;      // 28
		ParticleData                                  instanceData[78];  // 30
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSParticleShaderEmitter) == 0xED0);
}
