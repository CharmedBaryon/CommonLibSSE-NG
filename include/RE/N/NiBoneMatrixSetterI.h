#pragma once

#include "RE/N/NiSkinPartition.h"

namespace RE
{
	class NiSkinInstance;
	class NiTransform;

	class NiBoneMatrixSetterI
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiBoneMatrixSetterI;
		inline static constexpr auto VTABLE = VTABLE_NiBoneMatrixSetterI;

		virtual ~NiBoneMatrixSetterI();  // 00

		// add
		virtual void SetBoneMatrices(NiSkinInstance* a_skin, NiSkinPartition::Partition* a_partition, NiTransform* a_transform);  // 01
	};
	static_assert(sizeof(NiBoneMatrixSetterI) == 0x8);
}
