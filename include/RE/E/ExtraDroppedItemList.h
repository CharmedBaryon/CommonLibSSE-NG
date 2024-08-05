#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTList.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraDroppedItemList : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraDroppedItemList;
		inline static constexpr auto VTABLE = VTABLE_ExtraDroppedItemList;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kDroppedItemList;

		~ExtraDroppedItemList() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 { return kDroppedItemList; }

		// members
		BSSimpleList<ObjectRefHandle> droppedItemList;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraDroppedItemList) == 0x20);
}
