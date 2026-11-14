#include "RE/C/Character.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void Character::Unk_128()
	{
		REL::RelocateVirtual<decltype(&Character::Unk_128)>(0x128, 0x12A, this);
	}

	void Character::Unk_129()
	{
		REL::RelocateVirtual<decltype(&Character::Unk_129)>(0x129, 0x12B, this);
	}
#endif

	void Character::SetAnimationDrivenMotion(bool a_active)
	{
		using func_t = decltype(&Character::SetAnimationDrivenMotion);
		static REL::Relocation<func_t> func{ RELOCATION_ID(36910, 37934) };
		return func(this, a_active);
	}
}
