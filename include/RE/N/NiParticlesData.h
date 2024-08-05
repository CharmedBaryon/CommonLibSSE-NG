#pragma once

#include "RE/N/NiBound.h"
#include "RE/N/NiObject.h"

namespace RE
{
	class NiParticlesData : public NiObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiParticlesData;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiParticlesData;
		inline static constexpr auto VTABLE = VTABLE_NiParticlesData;

		struct PARTICLES_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                               \
	bool          hasRotations;           /* 10, VR 28 */                  \
	std::uint8_t  unk11;                  /* 11, VR 29 */                  \
	std::uint16_t maxNumVertices;         /* 12, VR 2A */                  \
	NiBound       bound;                  /* 14, VR 2C */                  \
	std::uint32_t pad24;                  /* 24, VR 3C */                  \
	NiQuaternion* rotations;              /* 28, VR 40 */                  \
	NiPoint3*     positions;              /* 30, VR 48 */                  \
	NiColorA*     color;                  /* 38, VR 50 */                  \
	float*        radii;                  /* 40, VR 58 */                  \
	float*        sizes;                  /* 48, VR 60 */                  \
	float*        rotationAngles;         /* 50, VR 68 */                  \
	NiPoint3*     rotationAxes;           /* 58, VR 70 */                  \
	NiColorA*     subtextureOffsets;      /* 60, VR 78 */                  \
	std::uint32_t subTextureOffsetsCount; /* 68, VR 80 - max 256 */        \
	float         aspectRatio;            /* 6C, VR 84 */                  \
	float         speedToAspectAspect2;   /* 70, VR 88 */                  \
	float         speedToAspectAspect1;   /* 74, VR 8C */                  \
	float         speedToAspectSpeed2;    /* 78, VR 90 */                  \
	std::uint16_t numVertices;            /* 7C, VR 94 */                  \
	std::uint16_t pad7E;                  /* 7E, VR 96 */                  \
	std::uint8_t* textureIndices;         /* 80, VR 98 */                  \
	std::uint8_t  unk88;                  /* 88, VR A0 - aspect flags?  */ \
	std::uint8_t  unk89;                  /* 89, VR A1 */                  \
	std::uint16_t pad8A;                  /* 8A, VR A2 */                  \
	std::uint32_t pad8C;                  /* 8C, VR A4 */
			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(PARTICLES_RUNTIME_DATA) == 0x80);

		~NiParticlesData() override;  // 00

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;                          // 02
		void          LoadBinary(NiStream& a_stream) override;           // 18
		void          LinkObject(NiStream& a_stream) override;           // 19
		bool          RegisterStreamables(NiStream& a_stream) override;  // 1A
		void          SaveBinary(NiStream& a_stream) override;           // 1B
		bool          IsEqual(NiObject* a_object) override;              // 1C - { return false; }

		// add
		virtual void          SetActiveVertexCount(std::uint16_t a_vertexCount);  // 25
		virtual std::uint16_t GetActiveVertexCount();                             // 26
		virtual void          RemoveParticle(std::uint16_t a_particleCount);      // 28
		virtual void          CalculateNormals();                                 // 29 - { return; }

		[[nodiscard]] inline PARTICLES_RUNTIME_DATA& GetParticlesRuntimeData() noexcept
		{
			return REL::RelocateMember<PARTICLES_RUNTIME_DATA>(this, 0x10, 0x28);
		}

		[[nodiscard]] inline const PARTICLES_RUNTIME_DATA& GetParticlesRuntimeData() const noexcept
		{
			return REL::RelocateMember<PARTICLES_RUNTIME_DATA>(this, 0x10, 0x28);
		}
		// members

#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;
#endif
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(NiParticlesData) == 0x90);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(NiParticlesData) == 0x90);
#else
	static_assert(sizeof(NiParticlesData) == 0x10);
#endif
}
#undef RUNTIME_DATA_CONTENT
