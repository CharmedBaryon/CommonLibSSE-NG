#include "RE/B/BSDismemberSkinInstance.h"

namespace RE
{
	BSDismemberSkinInstance* BSDismemberSkinInstance::Create()
	{
		using func_t = decltype(&BSDismemberSkinInstance::Create);
		static REL::Relocation<func_t> func{ RELOCATION_ID(69398, 70772) };
		return func();
	}
}
