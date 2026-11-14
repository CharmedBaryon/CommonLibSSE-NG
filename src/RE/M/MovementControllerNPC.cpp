#include "RE/M/MovementControllerNPC.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	void MovementControllerNPC::Unk_0A()
	{
		REL::RelocateVirtual<decltype(&MovementControllerNPC::Unk_0A)>(0x0A, 0x0B, this);
	}

	void MovementControllerNPC::Unk_0B()
	{
		REL::RelocateVirtual<decltype(&MovementControllerNPC::Unk_0B)>(0x0B, 0x0C, this);
	}

	void MovementControllerNPC::SetAIDriven()
	{
		REL::RelocateVirtual<decltype(&MovementControllerNPC::SetAIDriven)>(0x0C, 0x0D, this);
	}

	void MovementControllerNPC::SetControlsDriven()
	{
		REL::RelocateVirtual<decltype(&MovementControllerNPC::SetControlsDriven)>(0x0D, 0x0E, this);
	}

	bool MovementControllerNPC::GetAIDriven()
	{
		return REL::RelocateVirtual<decltype(&MovementControllerNPC::GetAIDriven)>(0x0E, 0x0F, this);
	}

	bool MovementControllerNPC::GetControlsDriven()
	{
		return REL::RelocateVirtual<decltype(&MovementControllerNPC::GetControlsDriven)>(0x0F, 0x10, this);
	}

	void MovementControllerNPC::Unk_10()
	{
		REL::RelocateVirtual<decltype(&MovementControllerNPC::Unk_10)>(0x10, 0x11, this);
	}

	void MovementControllerNPC::Unk_11()
	{
		REL::RelocateVirtual<decltype(&MovementControllerNPC::Unk_11)>(0x11, 0x12, this);
	}

	void MovementControllerNPC::Unk_12()
	{
		REL::RelocateVirtual<decltype(&MovementControllerNPC::Unk_12)>(0x12, 0x13, this);
	}

	void MovementControllerNPC::Unk_13()
	{
		REL::RelocateVirtual<decltype(&MovementControllerNPC::Unk_13)>(0x13, 0x14, this);
	}

	void MovementControllerNPC::Unk_14()
	{
		REL::RelocateVirtual<decltype(&MovementControllerNPC::Unk_14)>(0x14, 0x15, this);
	}
#endif
}
