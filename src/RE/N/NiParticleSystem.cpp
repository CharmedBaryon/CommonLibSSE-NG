#include "RE/N/NiParticleSystem.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void NiParticleSystem::UpdateSystem(float a_time)
	{
		REL::RelocateVirtual<decltype(&NiParticleSystem::UpdateSystem)>(0x38, 0x39, this, a_time);
	}

	void NiParticleSystem::Do_UpdateSystem(float a_time)
	{
		REL::RelocateVirtual<decltype(&NiParticleSystem::Do_UpdateSystem)>(0x39, 0x3A, this, a_time);
	}
#endif
}
