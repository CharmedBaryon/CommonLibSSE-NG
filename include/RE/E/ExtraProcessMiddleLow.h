#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraProcessMiddleLow : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraProcessMiddleLow;
		inline static constexpr auto VTABLE = VTABLE_ExtraProcessMiddleLow;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kProcessMiddleLow;

		~ExtraProcessMiddleLow() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 - { return kProcessMiddleLow; }

		// members
		std::uint32_t refCount;  // 10
		std::uint32_t pad14;     // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraProcessMiddleLow) == 0x18);
}
