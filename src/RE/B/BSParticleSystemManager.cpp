#include "RE/B/BSParticleSystemManager.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void BSParticleSystemManager::AttachChild(NiAVObject* a_child, bool a_firstAvail)
	{
		REL::RelocateVirtual<decltype(&BSParticleSystemManager::AttachChild)>(0x35, 0x36, this, a_child, a_firstAvail);
	}

	void BSParticleSystemManager::DetachChild1(NiAVObject* a_child, NiPointer<NiAVObject>& a_childOut)
	{
		REL::RelocateVirtual<decltype(&BSParticleSystemManager::DetachChild1)>(0x37, 0x38, this, a_child, a_childOut);
	}

	void BSParticleSystemManager::DetachChild2(NiAVObject* a_child)
	{
		REL::RelocateVirtual<decltype(&BSParticleSystemManager::DetachChild2)>(0x38, 0x39, this, a_child);
	}

	void BSParticleSystemManager::DetachChildAt1(std::uint32_t a_idx, NiPointer<NiAVObject>& a_childOut)
	{
		REL::RelocateVirtual<decltype(&BSParticleSystemManager::DetachChildAt1)>(0x39, 0x3A, this, a_idx, a_childOut);
	}

	void BSParticleSystemManager::DetachChildAt2(std::uint32_t a_idx)
	{
		REL::RelocateVirtual<decltype(&BSParticleSystemManager::DetachChildAt2)>(0x3A, 0x3B, this, a_idx);
	}

	void BSParticleSystemManager::SetAt2(std::uint32_t a_idx, NiAVObject* a_child)
	{
		REL::RelocateVirtual<decltype(&BSParticleSystemManager::SetAt2)>(0x3C, 0x3D, this, a_idx, a_child);
	}
#endif

	bool BSParticleSystemManager::IsValidMasterParticleSystem(std::uint32_t a_index)
	{
		using func_t = decltype(&BSParticleSystemManager::IsValidMasterParticleSystem);
		static REL::Relocation<func_t> func{ RELOCATION_ID(74857, 76605) };
		return func(this, a_index);
	}

	BSMasterParticleSystem* BSParticleSystemManager::GetMasterParticleSystemAt(std::uint32_t a_index)
	{
		using func_t = decltype(&BSParticleSystemManager::GetMasterParticleSystemAt);
		static REL::Relocation<func_t> func{ RELOCATION_ID(74860, 76608) };
		return func(this, a_index);
	}
}
