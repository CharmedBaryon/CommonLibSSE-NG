#pragma once

#include "RE/B/BGSBipedObjectForm.h"
#include "RE/I/InventoryChanges.h"

namespace RE
{
	class GetArmorInSlotFunctor : public InventoryChanges::IItemChangeVisitor
	{
	public:
		using BipedObjectSlot = BIPED_MODEL::BipedObjectSlot;
		inline static constexpr auto RTTI = RTTI___GetArmorInSlotFunctor;

		virtual ~GetArmorInSlotFunctor() = default;  // 00

		// override (InventoryChanges::IItemChangeVisitor)
		BSContainer::ForEachResult Visit(InventoryEntryData* a_entryData) override;  // 01

		// members
		std::uint32_t                    slot;
		BSTSmartPointer<TESBoundObject>* object;
	};
	static_assert(sizeof(GetArmorInSlotFunctor) == 0x18);
}
