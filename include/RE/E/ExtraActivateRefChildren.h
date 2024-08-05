#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSTList.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	struct REF_ACTIVATE_DATA;

	class ExtraActivateRefChildren : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraActivateRefChildren;
		inline static constexpr auto VTABLE = VTABLE_ExtraActivateRefChildren;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kActivateRefChildren;

		~ExtraActivateRefChildren() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 - { return kActivateRefChildren; }

		// members
		BSSimpleList<REF_ACTIVATE_DATA*> children;               // 10
		float                            activateChildrenTimer;  // 20
		std::uint32_t                    pad24;                  // 24
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraActivateRefChildren) == 0x28);
}
