#pragma once

namespace RE
{
	class BSDynamicTriShape;

	// Sent by BSProceduralLightningController after it rebuilds its bolt mesh;
	// the payload is a copy of that controller's own geometry member.
	struct BSProceduralGeomEvent
	{
	public:
		// members
		BSDynamicTriShape* geometry;  // 00
	};
	static_assert(sizeof(BSProceduralGeomEvent) == 0x8);
}
