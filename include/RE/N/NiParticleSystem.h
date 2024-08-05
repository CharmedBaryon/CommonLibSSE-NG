#pragma once

#include "RE/N/NiParticles.h"
#include "RE/N/NiTPointerList.h"

namespace RE
{
	class NiPSysModifier;

	class NiParticleSystem : public NiParticles
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiParticleSystem;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiParticleSystem;
		inline static constexpr auto VTABLE = VTABLE_NiParticleSystem;

		struct PARTICLESYSTEM_RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                   \
	NiTPointerList<NiPointer<NiPSysModifier>> modifierList;  /* 168, VR 1A8 */ \
	float                                     unk180;        /* 180, VR 1C0 */ \
	float                                     unk184;        /* 184, VR 1C4 */ \
	float                                     unk188;        /* 188, VR 1C8 */ \
	float                                     lastUpdate;    /* 18C, VR 1CC */ \
	bool                                      resetSystem;   /* 190, VR 1D0 */ \
	bool                                      dynamicBounds; /* 191, VR 1D1 */ \
	bool                                      isWorldspace;  /* 192, VR 1D2 */ \
	std::uint8_t                              pad193;        /* 193, VR 1D3 */ \
	std::uint32_t                             pad194;        /* 194, VR 1D4 */
            RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(PARTICLESYSTEM_RUNTIME_DATA) == 0x30);
		~NiParticleSystem() override;  // 00

		// override (NiParticles)
		const NiRTTI* GetRTTI() const override;                                                                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;                                                  // 17
		void          LoadBinary(NiStream& a_stream) override;                                                            // 18
		void          LinkObject(NiStream& a_stream) override;                                                            // 19 - { BSGeometry::LinkObject(a_stream); }
		bool          RegisterStreamables(NiStream& a_stream) override;                                                   // 1A - { return BSGeometry::RegisterStreamables(a_stream); }
		void          SaveBinary(NiStream& a_stream) override;                                                            // 1B
		bool          IsEqual(NiObject* a_object) override;                                                               // 1C - { return BSGeometry::IsEqual(); }
		void          ProcessClone(NiCloningProcess& a_cloning) override;                                                 // 1D
		void          SetSelectiveUpdateFlags(bool& a_selectiveUpdate, bool a_selectiveUpdateTransforms, bool& a_rigid);  // 2B
		void          UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2);                                     // 2C
		void          UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2);                             // 2D
		void          UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2);                                // 2E
		void          UpdateWorldData(NiUpdateData* a_data);                                                              // 30

		// add
		virtual void UpdateSystem(float a_time);     // 38 - { return NiParticleSystem::Do_UpdateSystem(a_time); }
		virtual void Do_UpdateSystem(float a_time);  // 39

		void AddModifier(NiPSysModifier* a_modifier)
		{
			using func_t = decltype(&NiParticleSystem::AddModifier);
			static REL::Relocation<func_t> func{ RELOCATION_ID(72799, 74499) };
			return func(this, a_modifier);
		}

		[[nodiscard]] inline PARTICLESYSTEM_RUNTIME_DATA& GetParticleSystemRuntimeData() noexcept
		{
			return REL::RelocateMember<PARTICLESYSTEM_RUNTIME_DATA>(this, 0x168, 0x1A8);
		}

		[[nodiscard]] inline const PARTICLESYSTEM_RUNTIME_DATA& GetParticleSystemRuntimeData() const noexcept
		{
			return REL::RelocateMember<PARTICLESYSTEM_RUNTIME_DATA>(this, 0x168, 0x1A8);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;
#endif
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(NiParticleSystem) == 0x198);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(NiParticleSystem) == 0x1E0);
#else
	static_assert(sizeof(NiParticleSystem) == 0x110);
#endif
}
#undef RUNTIME_DATA_CONTENT
