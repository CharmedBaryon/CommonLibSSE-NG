#include "RE/N/NiControllerSequence.h"

namespace RE
{
	bool NiControllerSequence::Activate(std::uint8_t a_interpIndex, bool a_maxOffset, float a_seqWeight, float a_easeInTime, NiControllerSequence* a_partnerSequence, bool a_transition)
	{
		using func_t = decltype(&NiControllerSequence::Activate);
		static REL::Relocation<func_t> func{ RELOCATION_ID(70882, 72463) };
		return func(this, a_interpIndex, a_maxOffset, a_seqWeight, a_easeInTime, a_partnerSequence, a_transition);
	}

	void NiControllerSequence::SetPhase(float a_phase, bool a_arg2)
	{
		using func_t = decltype(&NiControllerSequence::SetPhase);
		static REL::Relocation<func_t> func{ RELOCATION_ID(70860, 72439) };
		return func(this, a_phase, a_arg2);
	}
}
