#include "RE/P/Projectile.h"

using namespace REL;

namespace RE
{
	void Projectile::Unk_A2()
	{
		RelocateVirtual<void(Projectile*)>(0xA2, 0xA3, this);
	}

	void Projectile::Unk_A3()
	{
		RelocateVirtual<void(Projectile*)>(0xA3, 0xA4, this);
	}

	void Projectile::Unk_A4()
	{
		RelocateVirtual<void(Projectile*)>(0xA4, 0xA5, this);
	}

	void Projectile::Unk_A5()
	{
		RelocateVirtual<void(Projectile*)>(0xA5, 0xA6, this);
	}

	void Projectile::Unk_A6()
	{
		RelocateVirtual<void(Projectile*)>(0xA6, 0xA7, this);
	}

	void Projectile::Unk_A7()
	{
		RelocateVirtual<void(Projectile*)>(0xA7, 0xA8, this);
	}

	void Projectile::Unk_A8()
	{
		RelocateVirtual<void(Projectile*)>(0xA8, 0xA9, this);
	}

	void Projectile::Unk_A9()
	{
		RelocateVirtual<void(Projectile*)>(0xA9, 0xAA, this);
	}

	void Projectile::Unk_AA()
	{
		RelocateVirtual<void(Projectile*)>(0xAA, 0xAB, this);
	}

	void Projectile::UpdateImpl(float a_delta)
	{
		RelocateVirtual<decltype(&Projectile::UpdateImpl)>(0xAB, 0xAC, this, a_delta);
	}

	void Projectile::Unk_AC()
	{
		RelocateVirtual<void(Projectile*)>(0xAC, 0xAD, this);
	}

	void Projectile::Unk_AD()
	{
		RelocateVirtual<void(Projectile*)>(0xAD, 0xAE, this);
	}

	void Projectile::Unk_AE()
	{
		RelocateVirtual<void(Projectile*)>(0xAE, 0xAF, this);
	}

	void Projectile::Unk_AF()
	{
		RelocateVirtual<void(Projectile*)>(0xAF, 0xB0, this);
	}

	void Projectile::Unk_B0()
	{
		RelocateVirtual<void(Projectile*)>(0xB0, 0xB1, this);
	}

	void Projectile::Unk_B1()
	{
		RelocateVirtual<void(Projectile*)>(0xB1, 0xB2, this);
	}

	void Projectile::Unk_B2()
	{
		RelocateVirtual<void(Projectile*)>(0xB2, 0xB3, this);
	}

	void Projectile::Unk_B3()
	{
		RelocateVirtual<void(Projectile*)>(0xB3, 0xB4, this);
	}

	bool Projectile::IsNotGeneratedForm() const
	{
		return RelocateVirtual<decltype(&Projectile::IsNotGeneratedForm)>(0xB4, 0xB5, this);
	}

	void Projectile::Unk_B5()
	{
		RelocateVirtual<void(Projectile*)>(0xB5, 0xB6, this);
	}

	void Projectile::Unk_B6()
	{
		RelocateVirtual<void(Projectile*)>(0xB6, 0xB7, this);
	}

	void Projectile::Unk_B7()
	{
		RelocateVirtual<void(Projectile*)>(0xB7, 0xB8, this);
	}

	void Projectile::Unk_B8()
	{
		RelocateVirtual<void(Projectile*)>(0xB8, 0xB9, this);
	}

	void Projectile::Unk_B9()
	{
		RelocateVirtual<void(Projectile*)>(0xB9, 0xBA, this);
	}

	void Projectile::Unk_BA()
	{
		RelocateVirtual<void(Projectile*)>(0xBA, 0xBB, this);
	}

	void Projectile::Unk_BB()
	{
		RelocateVirtual<void(Projectile*)>(0xBB, 0xBC, this);
	}

	void Projectile::Unk_BC()
	{
		RelocateVirtual<void(Projectile*)>(0xBC, 0xBD, this);
	}

	void Projectile::Unk_BD()
	{
		RelocateVirtual<void(Projectile*)>(0xBD, 0xBE, this);
	}

	void Projectile::Unk_BE()
	{
		RelocateVirtual<void(Projectile*)>(0xBE, 0xBF, this);
	}

	void Projectile::Unk_BF()
	{
		RelocateVirtual<void(Projectile*)>(0xBF, 0xC0, this);
	}

	void Projectile::Handle3DLoaded()
	{
		RelocateVirtual<decltype(&Projectile::Handle3DLoaded)>(0xC0, 0xC1, this);
	}

	void Projectile::Unk_C1()
	{
		RelocateVirtual<void(Projectile*)>(0xC1, 0xC2, this);
	}
}
