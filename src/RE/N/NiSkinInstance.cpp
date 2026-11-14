#include "RE/N/NiSkinInstance.h"

#include "RE/M/MemoryManager.h"

namespace RE
{
	NiSkinInstance* NiSkinInstance::Create()
	{
		auto instance = malloc_runtime<NiSkinInstance>(0x88, 0x68);
		if (instance) {
			instance->Ctor();
		}
		return instance;
	}

	NiSkinInstance* NiSkinInstance::Ctor()
	{
		using func_t = decltype(&NiSkinInstance::Ctor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(69804, 71227) };
		return func(this);
	}
}
