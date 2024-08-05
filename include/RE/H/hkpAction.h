#pragma once

#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkpAction : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpAction;
		inline static constexpr auto VTABLE = VTABLE_hkpAction;

		virtual ~hkpAction() override;  // 00

		// add
		virtual void       ApplyAction(const hkStepInfo& a_stepInfo) = 0;                                                         // 03
		virtual void       GetEntities(hkArray<hkpEntity*>& a_entitiesOut) = 0;                                                   // 04
		virtual void       GetPhantoms(hkArray<hkpPhantom*>& a_phantomsOut);                                                      // 05
		virtual void       EntityRemovedCallback(hkpEntity* a_entity) = 0;                                                        // 06
		virtual hkpAction* Clone(const hkArray<hkpEntity*>& a_newEntities, const hkArray<hkpPhantom*>& a_newPhantoms) const = 0;  // 07

		// members
		hkpWorld*            world;     // 10
		hkpSimulationIsland* island;    // 18
		std::uint64_t        userData;  // 20
		hkStringPtr          name;      // 28
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpAction) == 0x30);
}
