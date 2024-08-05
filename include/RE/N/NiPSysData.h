#pragma once

#include "RE/N/NiParticlesData.h"

namespace RE
{
	class NiParticleInfo
	{
	public:
		// members
		NiPoint3      velocity;    // 00
		float         age;         // 0C
		float         lifespan;    // 10
		float         lastUpdate;  // 14
		std::uint16_t unk18;       // 18
		std::uint16_t unk1A;       // 1A
		std::uint32_t pad1C;       // 1C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(NiParticleInfo) == 0x20);

	class NiPSysData : public NiParticlesData
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysData;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysData;
		inline static constexpr auto VTABLE = VTABLE_NiPSysData;

		struct PSYS_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                            \
	NiParticleInfo* particleInfo;       /* 90, VR A8 */ \
	float*          rotationSpeeds;     /* 98, VR B0 */ \
	std::uint16_t   addedParticleCount; /* A0, VR B8 */ \
	std::uint16_t   addedParticlesBase; /* A0, VR BC */ \
	std::uint32_t   padA4;              /* A4, VR C0 */
            RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(PSYS_RUNTIME_DATA) == 0x18);

		~NiPSysData() override;  // 00

		// override (NiParticlesData)
		const NiRTTI* GetRTTI() const override;                                // 02
		void          LoadBinary(NiStream& a_stream) override;                 // 18
		void          LinkObject(NiStream& a_stream) override;                 // 19
		bool          RegisterStreamables(NiStream& a_stream) override;        // 1A
		void          SaveBinary(NiStream& a_stream) override;                 // 1B
		bool          IsEqual(NiObject* a_object) override;                    // 1C - { return false; }
		void          RemoveParticle(std::uint16_t a_particleCount) override;  // 28

		// add
		virtual std::uint16_t AddParticle();            // 2A
		virtual void          ResolveAddedParticles();  // 2B

		[[nodiscard]] inline PSYS_RUNTIME_DATA& GetPSysRuntimeData() noexcept
		{
			return REL::RelocateMember<PSYS_RUNTIME_DATA>(this, 0x90, 0xA8);
		}

		[[nodiscard]] inline const PSYS_RUNTIME_DATA& GetPSysRuntimeData() const noexcept
		{
			return REL::RelocateMember<PSYS_RUNTIME_DATA>(this, 0x90, 0xA8);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;
#endif
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(NiPSysData) == 0xA8);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(NiPSysData) == 0xA8);
#else
	static_assert(sizeof(NiPSysData) == 0x10);
#endif
}
#undef RUNTIME_DATA_CONTENT
