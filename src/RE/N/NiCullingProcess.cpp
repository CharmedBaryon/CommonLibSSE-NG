#include "RE/N/NiCullingProcess.h"

namespace RE
{
	void NiCullingProcess::SetFrustum(const NiFrustum* a_frustum)
	{
		using func_t = decltype(&NiCullingProcess::SetFrustum);
		static REL::Relocation<func_t> func{ RELOCATION_ID(69699, 71081) };
		func(this, a_frustum);
	}
}