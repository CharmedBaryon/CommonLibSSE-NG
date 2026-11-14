#pragma once

#include "RE/N/NiParticleSystem.h"

namespace RE
{
	class BSStripParticleSystem : public NiParticleSystem
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSStripParticleSystem;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSStripParticleSystem;
		inline static constexpr auto VTABLE = VTABLE_BSStripParticleSystem;

		~BSStripParticleSystem() override;  // 00

		// override (NiParticleSystem)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		// The following are virtual functions past the point where VR compatibility breaks.
		void OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex) override;  // 34
#endif
	};
	STATIC_ASSERT_SIZE(BSStripParticleSystem, 0x198, 0x198, 0x1D8, 0x110);
}
