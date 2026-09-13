#include "RE/B/BSPortalGraphEntry.h"

namespace RE
{
	void BSPortalGraphEntry::SetPortalGraph(BSPortalGraph* a_portalGraph)
	{
		portalGraph = a_portalGraph;
		multiBoundRoomRoot.reset();
	}

	void BSPortalGraphEntry::AddVisibilityToMap(void* a_space, BSCompoundFrustum* a_compoundFrustum)
	{
		using func_t = decltype(&BSPortalGraphEntry::AddVisibilityToMap);
		static REL::Relocation<func_t> func{ RELOCATION_ID(74398, 76122) };
		return func(this, a_space, a_compoundFrustum);
	}

	void BSPortalGraphEntry::ClearVisibility()
	{
		using func_t = decltype(&BSPortalGraphEntry::ClearVisibility);
		static REL::Relocation<func_t> func{ RELOCATION_ID(74395, 76119) };
		return func(this);
	}
}