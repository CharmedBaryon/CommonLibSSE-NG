#include "RE/B/BeamProjectile.h"

using namespace REL;

namespace RE
{
#ifndef SKYRIM_CROSS_VR
	bool BeamProjectile::IsBeamProjectile()
	{
		return RelocateVirtual<decltype(&Projectile::IsBeamProjectile)>(0xA5, 0xA6, this);
	}

	void BeamProjectile::Process3D()
	{
		RelocateVirtual<decltype(&Projectile::Process3D)>(0xA9, 0xAA, this);
	}

	void BeamProjectile::UpdateImpl(float a_delta)
	{
		RelocateVirtual<decltype(&Projectile::UpdateImpl)>(0xAB, 0xAC, this, a_delta);
	}

	bool BeamProjectile::GetKillOnCollision()
	{
		return RelocateVirtual<decltype(&Projectile::GetKillOnCollision)>(0xB8, 0xB9, this);
	}

	void BeamProjectile::AddImpact(TESObjectREFR* a_ref, const NiPoint3& a_targetLoc, const NiPoint3& a_velocity, hkpCollidable* a_collidable, std::int32_t a_arg6, std::uint32_t a_arg7)
	{
		RelocateVirtual<decltype(&Projectile::AddImpact)>(0xBD, 0xBE, this, a_ref, a_targetLoc, a_velocity, a_collidable, a_arg6, a_arg7);
	}

	void BeamProjectile::Handle3DLoaded()
	{
		RelocateVirtual<decltype(&Projectile::Handle3DLoaded)>(0xC0, 0xC1, this);
	}

	bool BeamProjectile::ShouldUseDesiredTarget()
	{
		return RelocateVirtual<decltype(&Projectile::ShouldUseDesiredTarget)>(0xC1, 0xC2, this);
	}
#endif
}
