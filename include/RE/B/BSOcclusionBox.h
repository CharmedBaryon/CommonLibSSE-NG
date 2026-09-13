#pragma once

#include "RE/B/BSCompoundFrustum.h"
#include "RE/B/BSOcclusionShape.h"
#include "RE/N/NiPoint2.h"

namespace RE
{
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
		bool          IsOcclusionBox() const override;                    // 25

		// members
		NiPoint3          size;              // 048
		NiFrustumPlanes   frustumPlanes[2];  // 054
		NiPlane           faces[6];          // 134
		float             unk194;            // 194
		BSMultiBoundAABB* boundShape;        // 198
		uint64_t          unk1A0;            // 1A0
		uint32_t          unk1A8;            // 1A8
		uint32_t          unk1AC;            // 1AC
		uint64_t          unk1B4;            // 1B4
		uint64_t          unk1BC;            // 1BC
		uint64_t          unk1C0;            // 1C0
		uint64_t          unk1C8;            // 1C8
		uint64_t          unk1D0;            // 1D0
		uint64_t          unk1D8;            // 1D8
		uint32_t          unk1E4;            // 1E4
	};
	static_assert(sizeof(BSOcclusionBox) == 0x1E8);
}
