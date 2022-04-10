#include "RE/E/Explosion.h"

using namespace REL;

namespace RE
{
	void Explosion::Initialize()
	{
		RelocateVirtual<decltype(&Explosion::Initialize)>(0xA2, 0xA3, this);
	}

	void Explosion::Update(float a_delta)
	{
		RelocateVirtual<decltype(&Explosion::Update)>(0xA3, 0xA4, this, a_delta);
	}

	void Explosion::FindTargets()
	{
		RelocateVirtual<decltype(&Explosion::FindTargets)>(0xA4, 0xA5, this);
	}
}
