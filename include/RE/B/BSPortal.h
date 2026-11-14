#pragma once

#include "RE/B/BSOcclusionPlane.h"

namespace RE
{
	class BSMultiBoundRoom;
	class BSPortalSharedNode;

	class BSPortal : public BSOcclusionPlane
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPortal;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSPortal;
		inline static constexpr auto VTABLE = VTABLE_BSPortal;

		~BSPortal() override;  // 00

		// override (BSOcclusionPlane)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17

		// members
		BSMultiBoundRoom*             entranceRoom;      // 118
		BSMultiBoundRoom*             exitRoom;          // 120
		NiPointer<BSPortalSharedNode> portalSharedNode;  // 128
	};
	static_assert(sizeof(BSPortal) == 0x130);
}
