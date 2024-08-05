#include "RE/N/NiSkinInstance.h"

namespace RE
{
	NiSkinInstance* NiSkinInstance::Create()
	{
		using func_t = decltype(&NiSkinInstance::Create);
		static REL::Relocation<func_t> func{ RELOCATION_ID(69804, 71227) };
		return func();
	}
}
