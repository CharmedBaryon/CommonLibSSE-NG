#pragma once

#include "RE/B/BSGeometry.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class NiPSysData;

	class NiParticles : public BSGeometry
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiParticles;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiParticles;
		inline static constexpr auto VTABLE = VTABLE_NiParticles;

		struct PARTICLES_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                              \
	NiPointer<NiPSysData> particleData; /*  158, VR 198*/ \
	std::uint64_t         unk160;       /*  160, VR 1A0*/

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(PARTICLES_RUNTIME_DATA) == 0x10);
		~NiParticles() override;  // 00

		// override (BSGeometry)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiParticles*  AsParticlesGeom() override;                         // 10
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19 - { BSGeometry::LinkObject(a_stream); }
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A - { return BSGeometry::RegisterStreamables(a_stream); }
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C - { return BSGeometry::IsEqual(); }

		RUNTIME_DATA_ACCESSOR_EX(PARTICLES_RUNTIME_DATA, GetParticlesRuntimeData, 0x158, 0x198);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;
#endif
	};
	STATIC_ASSERT_SIZE(NiParticles, 0x168, 0x168, 0x1A8, 0x110);
}
#undef RUNTIME_DATA_CONTENT
