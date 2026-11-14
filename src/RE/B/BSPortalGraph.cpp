#include "RE/B/BSPortalGraph.h"
#include "RE/B/BSPortalGraphEntry.h"

namespace RE
{
	bool BSPortalGraph::IsCompatibleEntry(const BSPortalGraphEntry* a_entry) const
	{
		return this == a_entry->portalGraph && cellID == a_entry->cellId;
	}

}