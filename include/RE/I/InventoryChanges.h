#pragma once

#include "RE/B/BSContainer.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSSimpleList.h"
#include "RE/F/FormTypes.h"
#include "RE/I/InventoryEntryData.h"
#include "RE/M/MemoryManager.h"
#include "RE/T/TESBoundObject.h"
#include "RE/T/TESContainer.h"
#include "RE/T/TESObjectREFR.h"

namespace RE
{
	enum class ITEM_REMOVE_REASON;
	class ExtraDataList;
	class InventoryEntryData;
	class NiPoint3;

	class InventoryChanges
	{
	public:
		enum class VisitResult : std::uint32_t
		{
			kStop = 0,
			kContinue = 1,
		};

		class IItemChangeVisitor
		{
		public:
			inline static constexpr auto RTTI = RTTI_InventoryChanges__IItemChangeVisitor;
			inline static constexpr auto VTABLE = VTABLE_InventoryChanges__IItemChangeVisitor;

			virtual ~IItemChangeVisitor() = default;  // 00

			// add
			virtual BSContainer::ForEachResult Visit(InventoryEntryData* a_entryData) = 0;                                                                                // 01
			virtual bool                       ShouldVisit([[maybe_unused]] InventoryEntryData* a_entryData, [[maybe_unused]] TESBoundObject* a_object) { return true; }  // 02
			virtual BSContainer::ForEachResult Unk_03(InventoryEntryData* a_entryData, [[maybe_unused]] void* a_arg2, bool* a_arg3)                                       // 03
			{
				*a_arg3 = true;
				return Visit(a_entryData);
			}
		};
		static_assert(sizeof(IItemChangeVisitor) == 0x8);

		InventoryChanges();
		explicit InventoryChanges(TESObjectREFR* a_ref);
		~InventoryChanges();

		void                              AddEntryData(InventoryEntryData* a_entry);
		RE::ExtraDataList*                EnchantObject(RE::TESBoundObject* a_obj, RE::ExtraDataList* a_extraList, RE::EnchantmentItem* a_enchantment, uint16_t a_charge);
		void                              GenerateLeveledListChanges();
		TESObjectARMO*                    GetArmorInSlot(std::int32_t a_slot);
		[[nodiscard]] InventoryEntryData* GetInventoryItemAt(std::int32_t a_index);
		float                             GetInventoryWeight();
		std::int16_t                      GetItemCount(TESBoundObject* a_obj);
		std::uint16_t                     GetNextUniqueID();
		std::uint32_t                     GetWornMask();
		void                              InitFromContainerExtra();
		void                              InitLeveledItems();
		void                              InitOutfitItems(BGSOutfit* a_outfit, std::uint16_t a_npcLevel);
		void                              InitScripts();
		void                              RemoveFavorite(InventoryEntryData* a_entry, ExtraDataList* a_itemList);
		ObjectRefHandle                   RemoveItem(TESObjectREFR* a_ref, TESBoundObject* a_item, std::int32_t a_count, ITEM_REMOVE_REASON a_reason, ExtraDataList* a_extraDataList, TESObjectREFR* a_moveToRef, const NiPoint3& a_dropLoc, TESObjectREFR* a_dropRef);
		void                              RemoveAllItems(TESObjectREFR* a_ref, TESObjectREFR* a_moveToRef, bool a_stealing, bool a_keepOwnership, bool a_arg6);
		void                              SendContainerChangedEvent(ExtraDataList* a_itemExtraList, TESObjectREFR* a_fromRefr, TESForm* a_item, std::int32_t a_count);
		void                              SetFavorite(InventoryEntryData* a_entry, ExtraDataList* a_itemList);
		void                              SetUniqueID(ExtraDataList* a_itemList, TESForm* a_oldForm, TESForm* a_newForm);
		void                              VisitInventory(IItemChangeVisitor& visitor);
		void                              VisitWornItems(IItemChangeVisitor& visitor);

		[[nodiscard]] std::int32_t GetCount(const TESBoundObject* a_object, std::predicate<const InventoryEntryData*> auto a_itemFilter) const
		{
			const auto   container = owner ? owner->GetContainer() : nullptr;
			std::int32_t count = container ? std::abs(container->GetObjectCount(a_object)) : 0;

			if (entryList) {
				const InventoryEntryData* objEntry = nullptr;
				for (const auto* const entry : *entryList) {
					if (entry && entry->object == a_object) {
						objEntry = entry;
						break;
					}
				}

				if (objEntry) {
					if (a_itemFilter(objEntry)) {
						count += objEntry->countDelta;
					}
				}
			}

			return count;
		}

		TES_HEAP_REDEFINE_NEW();

		// members
		BSSimpleList<InventoryEntryData*>* entryList{ nullptr };  // 00
		TESObjectREFR*                     owner{ nullptr };      // 08
		float                              totalWeight{ 0.0F };   // 10
		float                              armorWeight{ 0.0F };   // 14
		bool                               changed{ false };      // 18
		std::uint8_t                       unk19{ 0 };            // 19
		std::uint8_t                       unk1A{ 0 };            // 1A
		std::uint8_t                       unk1B{ 0 };            // 1B
		std::uint32_t                      unk1C{ 0 };            // 1C

	private:
		InventoryChanges* Ctor(TESObjectREFR* a_ref);
		void              Dtor();
	};
	static_assert(sizeof(InventoryChanges) == 0x20);
}
