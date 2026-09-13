#include "RE/B/BGSConstructibleObject.h"

#include "RE/G/GameSettingCollection.h"
#include "RE/I/InventoryChanges.h"
#include "RE/I/ItemRemoveReason.h"
#include "RE/P/PlayerCharacter.h"
#include "RE/T/TESFurniture.h"
#include "RE/T/TESValueForm.h"

namespace RE
{
	using namespace literals;

	bool BGSConstructibleObject::CanBeCreatedOnWorkbench(const TESFurniture* a_workbench, bool a_checkConditions) const
	{
		if (!a_workbench || !a_workbench->HasKeyword(benchKeyword)) {
			return false;
		}

		if (conditions.head && a_checkConditions) {
			const auto playerRef = PlayerCharacter::GetSingleton();
			return conditions.IsTrue(playerRef, playerRef);
		} else {
			return true;
		}
	}

	float BGSConstructibleObject::CalcSkillUse() const
	{
		const std::int32_t itemValue = createdItem ? TESValueForm::GetFormValue(createdItem) : 0;
		const float        value = itemValue > 0 ? static_cast<float>(itemValue) * data.numConstructed : 1.0f;

		return std::powf(value, "fConstructibleSkilluseExp"_gs.value_or(0.5f)) *
		           "fConstructibleSkillUseMult"_gs.value_or(1.0f) +
		       "fConstructibleSkillUseConst"_gs.value_or(0.0f);
	}

	bool BGSConstructibleObject::CreateItem() const
	{
		const auto player = PlayerCharacter::GetSingleton();
		const auto invChanges = player->GetInventoryChanges();

		const auto requiredObjects = std::span(requiredItems.containerObjects, requiredItems.numContainerObjects);

		for (const auto entry : requiredObjects) {
			const auto playerCount = invChanges->GetCount(entry->obj, [](auto item) { return !item->IsQuestObject(); });
			if (playerCount < std::abs(entry->count)) {
				return false;
			}
		}

		for (const auto entry : requiredObjects) {
			player->RemoveItem(entry->obj, std::abs(entry->count), ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
		}

		player->AddObjectToContainer(static_cast<TESBoundObject*>(createdItem), nullptr, data.numConstructed, nullptr);
		return true;
	}
}
