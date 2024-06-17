#pragma once

#include "RE/H/hkpMeshMaterial.h"
#include "RE/M/MaterialIDs.h"

namespace RE
{
	class bhkMeshMaterial : public hkpMeshMaterial
	{
	public:
		//members
		MATERIAL_ID materialID;  // 04
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(bhkMeshMaterial) == 0x8);
}
