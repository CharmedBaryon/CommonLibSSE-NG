#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class ExtraWornLeft : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraWornLeft;
		inline static constexpr auto VTABLE = VTABLE_ExtraWornLeft;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kWornLeft;

		~ExtraWornLeft() override;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override;  // 01 - { return kWorn; }
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraWornLeft) == 0x10);
}
