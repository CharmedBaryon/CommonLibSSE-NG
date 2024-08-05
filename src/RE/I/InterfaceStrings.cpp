#include "RE/I/InterfaceStrings.h"

namespace RE
{
	InterfaceStrings* InterfaceStrings::GetSingleton()
	{
		REL::Relocation<InterfaceStrings**> singleton{ RELOCATION_ID(514286, 400446) };
		return *singleton;
	}
}
