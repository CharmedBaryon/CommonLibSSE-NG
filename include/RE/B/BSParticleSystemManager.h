#pragma once

#include "RE/N/NiNode.h"

namespace RE
{
	class BSMasterParticleSystem;

	class BSParticleSystemManager : public NiNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSParticleSystemManager;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSParticleSystemManager;
		inline static constexpr auto VTABLE = VTABLE_BSParticleSystemManager;

		~BSParticleSystemManager() override;  // 00

		// override (NiNode)
		NiObject* CreateClone(NiCloningProcess& a_cloning) override;  // 17
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		void AttachChild(NiAVObject* a_child, bool a_firstAvail = false) override;             // 35
		void DetachChild1(NiAVObject* a_child, NiPointer<NiAVObject>& a_childOut) override;    // 37
		void DetachChild2(NiAVObject* a_child) override;                                       // 38
		void DetachChildAt1(std::uint32_t a_idx, NiPointer<NiAVObject>& a_childOut) override;  // 39
		void DetachChildAt2(std::uint32_t a_idx) override;                                     // 3A
		void SetAt2(std::uint32_t a_idx, NiAVObject* a_child) override;                        // 3C
#elif defined(EXCLUSIVE_SKYRIM_VR)
		void AttachChild(NiAVObject* a_child, bool a_firstAvail = false) override;             // 36
		void DetachChild1(NiAVObject* a_child, NiPointer<NiAVObject>& a_childOut) override;    // 38
		void DetachChild2(NiAVObject* a_child) override;                                       // 39
		void DetachChildAt1(std::uint32_t a_idx, NiPointer<NiAVObject>& a_childOut) override;  // 3A
		void DetachChildAt2(std::uint32_t a_idx) override;                                     // 3B
		void SetAt2(std::uint32_t a_idx, NiAVObject* a_child) override;                        // 3D
#else
		// VR shifts these slots by +1 (NiAVObject::ApplyLocalTransformToWorld is inserted ahead of
		// them); resolve the real per-runtime slot via RelocateVirtual instead of a fixed ordinal.
		void AttachChild(NiAVObject* a_child, bool a_firstAvail = false);             // SE/AE 35, VR 36
		void DetachChild1(NiAVObject* a_child, NiPointer<NiAVObject>& a_childOut);    // SE/AE 37, VR 38
		void DetachChild2(NiAVObject* a_child);                                       // SE/AE 38, VR 39
		void DetachChildAt1(std::uint32_t a_idx, NiPointer<NiAVObject>& a_childOut);  // SE/AE 39, VR 3A
		void DetachChildAt2(std::uint32_t a_idx);                                     // SE/AE 3A, VR 3B
		void SetAt2(std::uint32_t a_idx, NiAVObject* a_child);                        // SE/AE 3C, VR 3D
#endif

		// add

		// Thread-safe (mutex-guarded) registry of BSMasterParticleSystem entries.
		bool                    IsValidMasterParticleSystem(std::uint32_t a_index);
		BSMasterParticleSystem* GetMasterParticleSystemAt(std::uint32_t a_index);

	private:
		BSMasterParticleSystem** masterParticleSystems;          // 128 / 150 - BSTArray<BSMasterParticleSystem*> data
		std::uint32_t            masterParticleSystemsCapacity;  // 130 / 158
		std::uint32_t            unk134;                         // 134 / 15C - pad
		std::uint32_t            masterParticleSystemsCount;     // 138 / 160
		std::uint32_t            unk13C;                         // 13C / 164 - pad
		void*                    unk140;                         // 140 / 168 - not yet reverse engineered
	};
	STATIC_ASSERT_SIZE(BSParticleSystemManager, 0x148, 0x148, 0x170, SIZE_UNDEFINED, 0x148);
}
