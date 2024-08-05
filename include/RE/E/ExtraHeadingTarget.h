#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraHeadingTarget : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraHeadingTarget;
		inline static constexpr auto VTABLE = VTABLE_ExtraHeadingTarget;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kHeadingTarget;

		~ExtraHeadingTarget() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kHeadingTarget; }

		// members
		ObjectRefHandle target;  // 10
		std::uint32_t   pad14;   // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraHeadingTarget) == 0x18);
}
