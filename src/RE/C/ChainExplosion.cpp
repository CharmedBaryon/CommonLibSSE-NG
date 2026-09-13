#include "RE/C/ChainExplosion.h"

using namespace REL;

namespace RE
{
#ifndef SKYRIM_CROSS_VR
	void ChainExplosion::Initialize()
	{
		RelocateVirtual<decltype(&Explosion::Initialize)>(0xA2, 0xA3, this);
	}

	void ChainExplosion::Update(float a_delta)
	{
		RelocateVirtual<decltype(&Explosion::Update)>(0xA3, 0xA4, this, a_delta);
	}

	void ChainExplosion::FindTargets()
	{
		RelocateVirtual<decltype(&Explosion::FindTargets)>(0xA4, 0xA5, this);
	}
#endif
}
