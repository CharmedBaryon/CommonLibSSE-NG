#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTList.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraAttachRefChildren : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraAttachRefChildren;
		inline static constexpr auto VTABLE = VTABLE_ExtraAttachRefChildren;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kAttachRefChildren;

		~ExtraAttachRefChildren() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 - { return kAttachRefChildren; }

		// members
		BSSimpleList<ObjectRefHandle> children;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraAttachRefChildren) == 0x20);
}
