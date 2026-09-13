#include "RE/I/IMovementState.h"

namespace RE
{
	bool IMovementState::CanStrafe() const
	{
		using func_t = decltype(&IMovementState::CanStrafe);
		static REL::Relocation<func_t> func{ RELOCATION_ID(88498, 0) };
		return func(this);
	}
}
