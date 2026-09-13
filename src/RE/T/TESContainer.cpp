#include "RE/T/TESContainer.h"

#include "RE/F/FormTypes.h"
#include "RE/T/TESForm.h"

namespace RE
{
	ContainerObject::ContainerObject() :
		count(0),
		pad04(0),
		obj(nullptr),
		itemExtra()
	{}

	ContainerObject::ContainerObject(TESBoundObject* a_obj, std::int32_t a_count) :
		count(a_count),
		pad04(0),
		obj(a_obj),
		itemExtra()
	{}

	ContainerObject::ContainerObject(TESBoundObject* a_obj, std::int32_t a_count, TESForm* a_owner) :
		count(a_count),
		pad04(0),
		obj(a_obj),
		itemExtra(new ContainerItemExtra(a_owner))
	{}

	void TESContainer::CopyObjectList(const std::vector<ContainerObject*>& a_copiedData)
	{
		const auto oldData = containerObjects;

		const auto newSize = a_copiedData.size();
		const auto newData = calloc<ContainerObject*>(newSize);
		std::ranges::copy(a_copiedData, newData);

		numContainerObjects = static_cast<std::uint32_t>(newSize);
		containerObjects = newData;

		free(oldData);
	}

	bool TESContainer::AddObjectToContainer(TESBoundObject* a_object, std::int32_t a_count, TESForm* a_owner)
	{
		bool added = false;
		for (std::uint32_t i = 0; i < numContainerObjects; ++i) {
			if (const auto entry = containerObjects[i]; entry && entry->obj == a_object) {
				entry->count += a_count;
				added = true;
				break;
			}
		}
		if (!added) {
			std::vector<ContainerObject*> copiedData{ containerObjects, containerObjects + numContainerObjects };
			const auto                    newObj = new ContainerObject(a_object, a_count, a_owner);
			copiedData.push_back(newObj);
			CopyObjectList(copiedData);
			return true;
		}
		return added;
	}

	bool TESContainer::AddObjectsToContainer(std::map<TESBoundObject*, std::int32_t>& a_objects, TESForm* a_owner)
	{
		for (std::uint32_t i = 0; i < numContainerObjects; ++i) {
			if (const auto entry = containerObjects[i]; entry && entry->obj) {
				if (auto it = a_objects.find(entry->obj); it != a_objects.end()) {
					entry->count += it->second;
					a_objects.erase(it);
				}
			}
		}
		if (!a_objects.empty()) {
			std::vector<ContainerObject*> copiedData{ containerObjects, containerObjects + numContainerObjects };
			for (auto& [object, count] : a_objects) {
				const auto newObj = new ContainerObject(object, count, a_owner);
				copiedData.push_back(newObj);
			}
			CopyObjectList(copiedData);
		}
		return true;
	}

	void TESContainer::CollectUniqueInventoryObjects(BSScrapArray<ContainerObject*>& a_objects) const
	{
		using func_t = decltype(&TESContainer::CollectUniqueInventoryObjects);
		static REL::Relocation<func_t> func{ RELOCATION_ID(14390, 14543) };
		func(this, a_objects);
	}

	auto TESContainer::GetContainerObjectAt(std::uint32_t a_idx) const
		-> std::optional<ContainerObject*>
	{
		if (a_idx < numContainerObjects) {
			return std::make_optional(containerObjects[a_idx]);
		} else {
			return std::nullopt;
		}
	}

	auto TESContainer::GetContainerObjectIndex(TESBoundObject* a_object, std::int32_t a_count) const
		-> std::optional<std::uint32_t>
	{
		if (containerObjects) {
			for (std::uint32_t i = 0; i < numContainerObjects; ++i) {
				const auto entry = containerObjects[i];
				if (entry && entry->obj == a_object && entry->count == a_count) {
					return i;
				}
			}
		}
		return std::nullopt;
	}

	std::int32_t TESContainer::GetObjectCount(const TESBoundObject* a_object) const
	{
		std::int32_t count = 0;
		ForEachContainerObject([&](ContainerObject& a_contObj) {
			if (a_contObj.obj == a_object) {
				count += a_contObj.count;
			}
			return BSContainer::ForEachResult::kContinue;
		});
		return count;
	}

	bool TESContainer::RemoveObjectFromContainer(TESBoundObject* a_object, std::int32_t a_count)
	{
		if (auto index = GetContainerObjectIndex(a_object, a_count); index.has_value()) {
			std::vector<ContainerObject*> copiedData{ containerObjects, containerObjects + numContainerObjects };
			copiedData.erase(copiedData.cbegin() + *index);
			CopyObjectList(copiedData);
			return true;
		}
		return false;
	}
}
