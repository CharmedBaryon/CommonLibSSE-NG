#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraOpenCloseActivateRef : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraOpenCloseActivateRef;
		inline static constexpr auto VTABLE = VTABLE_ExtraOpenCloseActivateRef;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kOpenCloseActivateRef;

		~ExtraOpenCloseActivateRef() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 - { return kOpenCloseActivateRef; }

		// members
		ObjectRefHandle activateRef;  // 10
		std::uint32_t   pad14;        // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraOpenCloseActivateRef) == 0x18);
}
