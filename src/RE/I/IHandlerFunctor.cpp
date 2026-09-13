#include "RE/I/IHandlerFunctor.h"

namespace RE
{
	HandlerDictionary* HandlerDictionary::GetSingleton()
	{
		static REL::Relocation<HandlerDictionary**> singleton{ RELOCATION_ID(518086, 404607) };
		return *singleton;
	}
}
