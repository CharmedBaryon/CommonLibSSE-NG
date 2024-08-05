#pragma once

#include "RE/N/NiParticleSystem.h"

namespace RE
{
	class NiMeshParticleSystem : public NiParticleSystem
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiMeshParticleSystem;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiMeshParticleSystem;
		inline static constexpr auto VTABLE = VTABLE_NiMeshParticleSystem;

		~NiMeshParticleSystem() override;  // 00

		// override (NiParticles)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19 - { BSGeometry::LinkObject(a_stream); }
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A - { return BSGeometry::RegisterStreamables(a_stream); }
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C - { return BSGeometry::IsEqual(); }
#ifndef SKYRIM_CROSS_VR
		void SetSelectiveUpdateFlags(bool& a_selectiveUpdate, bool a_selectiveUpdateTransforms, bool& a_rigid) override;  // 2B
		void UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;                                     // 2C
		void UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;                             // 2D
		void UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;                                // 2E
		void UpdateWorldBound() override;                                                                                 // 2F
		void UpdateWorldData(NiUpdateData* a_data) override;                                                              // 30
		void OnVisible(NiCullingProcess& a_process) override;                                                             // 34
#endif

		struct MESH_PARTICLE_SYSTEM_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                   \
	float         time;              /* 198 */ \
	bool          updateControllers; /* 19C */ \
	std::uint8_t  pad19D;            /* 19D */ \
	std::uint16_t pad19E;            /* 19E */
		};

		[[nodiscard]] inline MESH_PARTICLE_SYSTEM_RUNTIME_DATA& GetMeshParticleSystemRuntimeData() noexcept
		{
			return REL::RelocateMember<MESH_PARTICLE_SYSTEM_RUNTIME_DATA>(this, 0x198, 0x1C0);
		}

		[[nodiscard]] inline const MESH_PARTICLE_SYSTEM_RUNTIME_DATA& GetMeshParticleSystemRuntimeData() const noexcept
		{
			return REL::RelocateMember<MESH_PARTICLE_SYSTEM_RUNTIME_DATA>(this, 0x198, 0x1C0);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 198, 1C0
#endif
	private:
		KEEP_FOR_RE()
	};
}
#undef RUNTIME_DATA_CONTENT
