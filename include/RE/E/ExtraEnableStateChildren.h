#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTList.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraEnableStateChildren : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraEnableStateChildren;
		inline static constexpr auto VTABLE = VTABLE_ExtraEnableStateChildren;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kEnableStateChildren;

		~ExtraEnableStateChildren() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 - { return kEnableStateChildren; }

		// members
		BSSimpleList<ObjectRefHandle> children;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraEnableStateChildren) == 0x20);
}
