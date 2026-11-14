#pragma once

#include "RE/B/BGSBipedObjectForm.h"
#include "RE/I/InventoryChanges.h"

namespace RE
{
	using BipedObjectSlot = BIPED_MODEL::BipedObjectSlot;

	class GetWornMaskVisitor : public InventoryChanges::IItemChangeVisitor
	{
	public:
		GetWornMaskVisitor(Actor* a_actor) :
			actor{ a_actor } {}

		BSContainer::ForEachResult Visit(InventoryEntryData* a_entryData) override;  // 01

		// members
		stl::enumeration<BipedObjectSlot, std::uint32_t> slotMask;
		std::uint32_t                                    pad0C;
		// add
		Actor* actor;
	};
	static_assert(offsetof(GetWornMaskVisitor, actor) == 0x10);
}
