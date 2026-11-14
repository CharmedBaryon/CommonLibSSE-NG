#include "RE/B/bhkCollisionFilter.h"

namespace RE
{
	void bhkCollisionFilter::SetLayerPairCollisionEnabled(COL_LAYER a_layerA, COL_LAYER a_layerB, bool a_enabled)
	{
		using func_t = decltype(&bhkCollisionFilter::SetLayerPairCollisionEnabled);
		static REL::Relocation<func_t> func{ RELOCATION_ID(76683, 78555) };
		return func(this, a_layerA, a_layerB, a_enabled);
	}

	void bhkCollisionFilter::SetLayerBitfield(COL_LAYER a_layer, std::uint64_t a_mask)
	{
		using func_t = decltype(&bhkCollisionFilter::SetLayerBitfield);
		static REL::Relocation<func_t> func{ RELOCATION_ID(76684, 78556) };
		return func(this, a_layer, a_mask);
	}
}
