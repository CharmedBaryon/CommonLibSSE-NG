#pragma once

#include "RE/B/BSOcclusionShape.h"
#include "RE/N/NiFrustumPlanes.h"
#include "RE/N/NiPoint2.h"

namespace RE
{
	class BSMultiBoundShape;

	class BSOcclusionBox : public BSOcclusionShape
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSOcclusionBox;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSOcclusionBox;
		inline static constexpr auto VTABLE = VTABLE_BSOcclusionBox;

		~BSOcclusionBox() override;  // 00

		// override (BSOcclusionShape)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		bool          IsOcclusionPlane() const override;                  // 25
		bool          IsOcclusionBox() const override;                    // 26

		// members
		NiPoint3           size;                  // 048
		NiFrustumPlanes    frustumPlanes[2];      // 054
		NiPoint3           corners[8];            // 134
		float              unk194;                // 194
		BSMultiBoundShape* boundShape;            // 198 - AABB when the rotation is identity, else OBB
		std::uint64_t      unk1A0;                // 1A0
		std::uint32_t      unk1A8;                // 1A8
		std::int32_t       facePlaneSlots[6];     // 1AC - -1 when unused
		std::uint32_t      silhouetteIndices[8];  // 1C4
		std::uint32_t      silhouetteCount;       // 1E4
	};
	static_assert(sizeof(BSOcclusionBox) == 0x1E8);
}
