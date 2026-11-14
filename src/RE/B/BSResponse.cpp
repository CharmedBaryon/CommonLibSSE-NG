#include "RE/B/BSResponse.h"

namespace RE
{
	ResponseDictionary* ResponseDictionary::GetSingleton()
	{
		static REL::Relocation<ResponseDictionary**> singleton{ RELOCATION_ID(517372, 403902) };
		return *singleton;
	}
}
