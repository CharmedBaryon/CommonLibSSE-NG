#pragma once

#include "RE/B/BSTList.h"
#include "RE/E/ExtraDataList.h"
#include "RE/F/FormTypes.h"
#include "RE/M/MemoryManager.h"
#include "RE/S/SoulLevels.h"

namespace RE
{
	class ExtraDataList;
	class TESBoundObject;

	class InventoryEntryData
	{
	public:
		InventoryEntryData() noexcept = default;
		InventoryEntryData(const InventoryEntryData& a_rhs);

		InventoryEntryData(InventoryEntryData&& a_rhs) noexcept :
			object(std::exchange(a_rhs.object, nullptr)),
			extraLists(std::exchange(a_rhs.extraLists, nullptr)),
			countDelta(std::exchange(a_rhs.countDelta, 0))
		{}

		InventoryEntryData(TESBoundObject* a_object, std::int32_t a_countDelta) :
			object(a_object),
			countDelta(a_countDelta)
		{}

		~InventoryEntryData();

		InventoryEntryData& operator=(const InventoryEntryData& a_rhs);
		InventoryEntryData& operator=(InventoryEntryData&& a_rhs);

		void                                          AddExtraList(ExtraDataList* a_extra);
		bool                                          CanItemBeTaken(bool a_noEquipped, bool a_noFavourited, bool a_noQuestItem) const;
		[[nodiscard]] const char*                     GetDisplayName();
		[[nodiscard]] EnchantmentItem*                GetEnchantment() const;
		[[nodiscard]] std::optional<double>           GetEnchantmentCharge() const;
		[[nodiscard]] constexpr TESBoundObject*       GetObject() noexcept { return object; }
		[[nodiscard]] constexpr const TESBoundObject* GetObject() const noexcept { return object; }
		[[nodiscard]] TESForm*                        GetOwner();
		[[nodiscard]] SOUL_LEVEL                      GetSoulLevel() const;
		[[nodiscard]] std::int32_t                    GetValue() const;
		[[nodiscard]] float                           GetWeight() const;
		[[nodiscard]] bool                            IsEnchanted() const;
		[[nodiscard]] bool                            IsFavorited() const;
		[[nodiscard]] bool                            IsLeveled() const;
		[[nodiscard]] bool                            IsPoisoned() const;
		[[nodiscard]] bool                            IsWorn() const;
		[[nodiscard]] bool                            IsOwnedBy(Actor* a_testOwner, bool a_defaultTo = true);
		[[nodiscard]] bool                            IsOwnedBy(Actor* a_testOwner, TESForm* a_itemOwner, bool a_defaultTo = true);
		[[nodiscard]] bool                            IsQuestObject() const;
		void                                          PoisonObject(AlchemyItem* a_alchItem, std::uint32_t a_count);

		TES_HEAP_REDEFINE_NEW();

		// members
		TESBoundObject*               object{ nullptr };      // 00
		BSSimpleList<ExtraDataList*>* extraLists{ nullptr };  // 08
		std::int32_t                  countDelta{ 0 };        // 10
		std::uint32_t                 pad14{ 0 };             // 14

	private:
		[[nodiscard]] bool IsOwnedBy_Impl(Actor* a_testOwner, TESForm* a_itemOwner, bool a_defaultTo);

		template <class T>
		[[nodiscard]] bool HasExtraDataType() const
		{
			if (extraLists) {
				for (const auto& xList : *extraLists) {
					if (xList && xList->HasType<T>()) {
						return true;
					}
				}
			}

			return false;
		}

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(InventoryEntryData) == 0x18);
}
