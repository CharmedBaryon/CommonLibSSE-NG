#pragma once

#include "RE/B/BSContainer.h"
#include "RE/B/BaseFormComponent.h"
#include "RE/C/ContainerItemExtra.h"

#include "RE/M/MemoryManager.h"

namespace RE
{
	class TESBoundObject;

	struct ContainerObject
	{
	public:
		ContainerObject();
		ContainerObject(TESBoundObject* a_obj, std::int32_t a_count);
		ContainerObject(TESBoundObject* a_obj, std::int32_t a_count, TESForm* a_owner);

		~ContainerObject() = default;

		TES_HEAP_REDEFINE_NEW();

		// members
		std::int32_t        count;      // 00 - CNTO~
		std::uint32_t       pad04;      // 04
		TESBoundObject*     obj;        // 08 - ~CNTO
		ContainerItemExtra* itemExtra;  // 10 - COED
	};
	static_assert(sizeof(ContainerObject) == 0x18);

	class TESContainer : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESContainer;
		inline static constexpr auto VTABLE = VTABLE_TESContainer;

		~TESContainer() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01 - { return; }
		void ClearDataComponent() override;                     // 02
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		inline void ForEachContainerObject(std::function<BSContainer::ForEachResult(ContainerObject&)> a_fn) const
		{
			for (std::uint32_t i = 0; i < numContainerObjects; ++i) {
				auto entry = containerObjects[i];
				if (entry) {
					if (a_fn(*entry) == BSContainer::ForEachResult::kStop) {
						break;
					}
				}
			}
		}

		std::optional<ContainerObject*> GetContainerObjectAt(std::uint32_t a_idx) const;
		std::optional<std::uint32_t>    GetContainerObjectIndex(TESBoundObject* a_object, std::int32_t a_count) const;
		bool                            AddObjectToContainer(TESBoundObject* a_object, std::int32_t a_count, TESForm* a_owner);
		bool                            AddObjectsToContainer(std::map<TESBoundObject*, std::int32_t>& a_objects, TESForm* a_owner);
		std::int32_t                    CountObjectsInContainer(TESBoundObject* a_object) const;
		bool                            RemoveObjectFromContainer(TESBoundObject* a_object, std::int32_t a_count);

		// members
		ContainerObject** containerObjects;     // 08
		std::uint32_t     numContainerObjects;  // 10
		bool              allowStolenItems;     // 14 - new in 1.6.1130

	private:
		void CopyObjectList(const std::vector<ContainerObject*>& a_copiedData);

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESContainer) == 0x18);
}
